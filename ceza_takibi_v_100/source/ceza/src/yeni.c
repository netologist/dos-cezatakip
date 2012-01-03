#include "/ozgan/programs/h/genel.h"
#include "src/ceza.h"
#define ACIK 5
void referans_yapici(void);
void yeni_goruntusu(int durum);
void ilerleme_cubugu(int satir, int kolon, long toplam, long kacinci, int renk);

void hesap_yap(DOSYA *handle)
{
	int sayac, kontrol, ilerleme = 0;
	FILE *fp;
	long kayit;
	char ana_oran[50], toplam_oran[50], yuzde[10];
	YENI_DATA data_yeni;
	YENI_INDEKS indeks_yeni;

	memset(toplam_oran, 0, 50);
	dosya_ac(handle);
	kontrol = handle->indeks_baslik->toplam_kayit;
	kayit = indeks_gezgini(handle, kontrol-1);
	for (sayac = kontrol-1; sayac >= 0; sayac--) {
		detay_oku(handle, kayit, DATA_AL);
		memcpy(&data_yeni, handle->ana_detay->data, handle->ana_baslik->bir_datanin_uzunlugu);
		memcpy(&indeks_yeni, handle->indeks_detay->data, handle->indeks_baslik->indeks_data_uzunlugu);
		memset(ana_oran, 0, 50);
		strcpy(ana_oran, data_yeni.Oran);
		toplama(ana_oran, toplam_oran, data_yeni.Oran_Tutucu);
		strcpy(indeks_yeni.Oran_Tutucu, data_yeni.Oran_Tutucu);
		strcpy(toplam_oran, data_yeni.Oran_Tutucu);
		memcpy(handle->ana_detay->data, &data_yeni, handle->ana_baslik->bir_datanin_uzunlugu);
		memcpy(handle->indeks_detay->data, &indeks_yeni, handle->indeks_baslik->indeks_data_uzunlugu);
		eski_kayit(handle, kayit);
		if ( (((100*(kontrol-sayac))/kontrol) % 7) == 0)
			ilerleme++;
		ilerleme_cubugu(12, 22, 34, ilerleme, BEYAZ_ | A_BEYAZ);
		sprintf(yuzde, "%02d", (100*(kontrol-sayac))/kontrol);
		harfler(11, 36, yuzde, BEYAZ_ | SIYAH);
		kayit = handle->indeks_detay->onceki;
	}
	dosya_kapa(handle);

}

char *liste_elemani(int satir, int kolon, char *string, DOSYA *handle, int baslangic, int uzunluk, int boy, int renk)
{
	int sayac, kontrol = handle->indeks_baslik->indeks_data_uzunlugu,
		boy_sayaci = 0;
	FILE *indeks, *ana;
	long adres;
	char birlesen[100];

	indeks = indeks_dosya_ac(indeks, handle, birlesen, "rb");

	if (uzunluk < kontrol)
		kontrol = uzunluk;

	adres = indeks_gezgini(handle, baslangic);
	for (boy_sayaci = 0; boy_sayaci < boy; boy_sayaci++) {
		/******* INDEKS DOSYA DETAY BòLGòSò OKUNUYOR *******/
		fseek(indeks, adres, SEEK_SET);
		fread(handle->indeks_detay, 1, sizeof(INDEKS_DETAY)-sizeof(char *), indeks);
		fread(handle->indeks_detay->data, 1, handle->indeks_baslik->indeks_data_uzunlugu, indeks);
		/*----------------AÄIKLAMA SONU-------------------*/
		adres = handle->indeks_detay->sonraki;
		memcpy(&string[(boy_sayaci * kontrol)+1], handle->indeks_detay->data, kontrol);
		string[(kontrol * boy_sayaci)] = ' ';
		for (sayac = 1; sayac < kontrol; sayac++) {
			if (string[(boy_sayaci * kontrol) + sayac] == '\0')
				string[(kontrol * boy_sayaci) + sayac] = ' ';
		}
		string[(kontrol * boy_sayaci) + sayac-1] = '\0';
		if (string[(kontrol * boy_sayaci) + sayac-2] != ' ')
			strcpy(&string[(kontrol * boy_sayaci) + sayac-5], "... ");
		harfler(satir + boy_sayaci, kolon, &string[kontrol * boy_sayaci], renk);
	}
	data_dosyasini_kapa(indeks);
	return string;
}

long liste_kutusu(int satir, int kolon, int baslangic, int boy, int en, int renk1, int renk2, DOSYA *handle)
{
	char *eleman;

	int sayac = 0, toplam = handle->indeks_baslik->toplam_kayit, isaretli_sayac = 0,
		ch = 0, bayrak = 0, yeni_baslangic = 0;

	eleman = (char *) malloc((en+5) * boy * 2);
	if (eleman == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	memset(eleman, 0, (en+5) * boy * 2);

	if (toplam == 0) {
		free(eleman);
		return -2;
	}
	else if (toplam < boy) {
		boy = toplam;
		bayrak = 1;
	}

	liste_elemani(satir, kolon, eleman, handle, baslangic, en, boy, renk1);
	for (;;) {
		if (yeni_baslangic != baslangic) {
			yeni_baslangic = baslangic;
			liste_elemani(satir, kolon, eleman, handle, baslangic, en, boy, renk1);
		}
		for (sayac = 0; sayac < boy; sayac++)
			harfler(satir + sayac, kolon, &eleman[en * sayac], renk1);
		harfler(satir + isaretli_sayac, kolon, &eleman[en * isaretli_sayac], renk2);

		ch = islem();

		switch (ch) {
			case ESC: free(eleman);
					  return -1;
			case DOWN: isaretli_sayac++;
					   if (isaretli_sayac == boy)
						   baslangic++;
					   break;
			case UP: isaretli_sayac--;
					 if (isaretli_sayac == -1)
						 baslangic--;
					 break;
			case PGDN : baslangic += boy - 1;
						if ((baslangic + isaretli_sayac) > (toplam - boy) && bayrak == 0) {
							baslangic = toplam - boy;
							isaretli_sayac = boy;
							mesaj_goster_kac(" Dosya Sonu ...");
						}
						else if ((baslangic + isaretli_sayac) > (toplam - boy) && bayrak == 1) {
							baslangic = 0;
							isaretli_sayac = boy;
							mesaj_goster_kac(" Dosya Sonu ...");
						}
						break;
			case PGUP :	baslangic -= (boy - 1);
						if ((baslangic + isaretli_sayac) <= (toplam % boy)+1 && bayrak == 0) {
							baslangic = 0;
							isaretli_sayac = 0;
							mesaj_goster_kac(" Dosya Baüç ...");
						}
						else if (bayrak == 1) {
							baslangic = 0;
							isaretli_sayac = 0;
							mesaj_goster_kac(" Dosya Baüç ...");
						}
						break;
			case KP_ENTER:
			case ENTER: free(eleman);
						return (long) isaretli_sayac + baslangic;
		}

		if (isaretli_sayac == boy)
			isaretli_sayac = boy - 1;

		if (isaretli_sayac == -1)
			isaretli_sayac = 0;

		if (baslangic == toplam - boy + 1&& bayrak == 0) {
			baslangic = toplam - boy;
			mesaj_goster_kac(" Dosya Sonu ...");
		}
		else if (baslangic == toplam - boy + 1 && bayrak == 1) {
			baslangic = 0;
			mesaj_goster_kac(" Dosya Sonu ...");
		}

		if (baslangic == -1) {
			baslangic = 0;
			mesaj_goster_kac(" Dosya Baüç ...");
		}
	}
}

void yeni(void)
{
	int n;
	char *p;

	p = (char *) malloc(4000 * 2);
	if (p == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	gettext(1, 2, 76, 23, p);

	for (n = 0; n < 7; n++)
		doldur(9+n, 20, '∞', 44, SIYAH_ | BEYAZ);

	for (n = 0; n < 7; n++)
		doldur(8+n, 18, ' ', 44, BEYAZ_ | A_BEYAZ);
	kalin_cerceve(8, 19, 5, 41, BEYAZ_ | A_BEYAZ);
	doldur(9, 21, ' ', 38, KAHVE_);
	harfler(9, 36, " Yeni ", KAHVE_ | A_BEYAZ);
	disa_pen(10, 21, 2, 37);
	cift_renk(11, 23, "Kayçt Tarihi [ &O&c&a&k    \x1f] Yçl ", BEYAZ_ | SIYAH, BEYAZ_ | A_BEYAZ);
	harfler(12, 23, "       Oranç", BEYAZ_ | SIYAH);
	cift_renk(24, 12, " &F&2 Kayçt  &F&3 Sil  &F&4 Yeni  &F&5 Liste  &F&6 DÅzenle", BEYAZ_ | SIYAH, BEYAZ_ | KIRMIZI);
	yeni_form();
	git_xy(-1, 0);
	puttext(1, 2, 76, 23, p);
	doldur(24, 12, ' ', 48, BEYAZ_);
	free(p);
	menu();
}

void ilerleme_cubugu(int satir, int kolon, long toplam, long kacinci, int renk)
{
	if (kacinci < toplam)
		harf(satir, kolon+kacinci, '±', renk);
}

void yeni_duzenle(DOSYA *handle)
{
	char bellek[2000], yuzde[10];
	int i;

	gettext(20, 11, 60, 14, bellek);
	doldur(11, 23, ' ', 34, BEYAZ_ | SIYAH);
	harfler(11, 32, "  %  0  tamalandç ", BEYAZ_ | A_BEYAZ);
	doldur(12, 23, '∞', 34, BEYAZ_ | SIYAH);
	hesap_yap(handle);
	for (i = 0; i <= 34; i++) {
		ilerleme_cubugu(12, 23, 34, i, BEYAZ_ | A_BEYAZ);
		sprintf(yuzde, "%02d", (100*i)/34);
		harfler(11, 36, yuzde, BEYAZ_ | SIYAH);
	}
	puttext(20, 11, 60, 14, bellek);
}
void yeni_form(void)
{
	TABLO_BILGI baslik2 = {5, 41, Form_YENI, 0};
	TABLO_FORM tablo2[] = {{Data_Yeni, KAPALI_MENU, 3, 20, 9, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, KMenu_CEZA_AYLARI, SONRA},
						   {Data_Yeni, YAZI, 3, 36, 4, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Yeni, SAYI, 4, 20, 3, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Yeni, YAZI, 60, 25, 10, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Indeks_Bilgisi, YOK},
						   {Data_Yeni, YAZI, 60, 25, 10, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Indeks_Bilgisi, YOK}
						  };

	tabloyarat("bin/yeni.tbl", &baslik2, tablo2);
	tablo = (TABLO_FORM *) tabloyukle("bin/yeni.tbl", &baslik);
	dataci = (char *) malloc(baslik.data_uzunlugu);
	if (dataci == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	memset(dataci, 0, baslik.data_uzunlugu);
	tablo_oynatici(8, 17, Data_Yeni, (char *) dataci, tablo, &baslik);
	kayit_adresi = 0;
	free(dataci);
	baslik.referans = 0;
}

void referans_yapici(void)
{
	char temp[5];

	memset(temp, 0, 5);
	strcpy(yeni_data->Referans, yeni_data->Yil);
	strcat(yeni_data->Referans, "-");
	if ((strlen(yeni_data->Ay) == 1) && yeni_data->Ay[0] != '9') {
		temp[0] = '0';
		temp[1] = yeni_data->Ay[0] + 1;
	}
	else if (yeni_data->Ay[0] == '9') {
		temp[0] = '1';
		temp[1] = '0';
	}
	else {
		temp[0] = yeni_data->Ay[0];
		temp[1] = yeni_data->Ay[1] + 1;
	}
	strcat(yeni_data->Referans, temp);
}

void yeni_kayit(DOSYA *handle)
{
//	dosya_yarat(handle);
	referans_yapici();
	if (kayit_adresi == 0) {
		kayit_adresi = dosya_kayit(handle);
		if (kayit_adresi == 0)
			msj_kutu(NULL, UYARI_KAYIT_MEVCUT, UYARI);
		else {
			mesaj_goster_kac("Kayçt_Tamamlandç");
			yeni_goruntusu(KAPALI);
			indeks_bilgisi(tablo, &baslik, INDEKS_KAPA);
		}
	}
	else {
		dosya_ac(handle);
		detay_oku(handle, kayit_adresi, DATA_ALMA);
		memcpy(handle->ana_detay->data, dataci, baslik.data_uzunlugu);
		indeks_uzunlugu(handle, handle->indeks_detay->data);
		eski_kayit(handle, kayit_adresi);
		dosya_kapa(handle);
		yeni_goruntusu(KAPALI);
		mesaj_goster_kac("Deßiütirildi !..");
	}
}

void yeni_kayit_sil(DOSYA *handle)
{
	if (kayit_adresi != 0) {
		if (msj_kutu(NULL, SORU_KAYDI_SILMEK, SORU) == EVET) {
			dosya_ac(handle);
			data_sil(handle, kayit_adresi);
			dosya_kapa(handle);
			mesaj_goster_kac("Kayçt Silindi...");
		}
	}
	else
		mesaj_goster_kac("Kayçt etmediniz...");
}

void liste_formu(int satir, int kolon)
{
	int i;

	golgele(satir+1, kolon+1, 16, 25, SIYAH_ | BEYAZ);
	for (i = 0; i < 16; i++) {
		doldur(satir+i, kolon-1, ' ', 25, CYAN_);
		doldur(satir+i, kolon+1, ' ', 22, BEYAZ_);
	}
	kalin_cerceve(satir, kolon, 14, 22, CYAN_ | A_BEYAZ);
	doldur(satir+1, kolon+1, ' ', 21, KAHVE_);
	cift_renk(satir+1, kolon+2, "  Tarih   &≥  Oran", KAHVE_ | A_BEYAZ, KAHVE_ | BEYAZ);
	harfler(satir, kolon+4, " Faiz Oranlarç ", CYAN_ | A_BEYAZ);
}

void yeni_goruntusu(int durum)
{
	tablo_yerlestir(8, 17, Data_Yeni, dataci, tablo, &baslik);
	if (durum == KAPALI) {
		tablo[0].islem_sirasi = YOK;
		tablo[1].islem_sirasi = YOK;
		uyari_gonder(2);
	}
	else {
		tablo[0].islem_sirasi = SONRA;
		tablo[1].islem_sirasi = SONRA;
		uyari_gonder(0);
	}
}

void yeni_yeni(void)
{
	memset(dataci, 0, baslik.data_uzunlugu);
	yeni_goruntusu(ACIK);
	kayit_adresi = 0;
}

void yeni_liste(DOSYA *handle)
{
	char bellek[3500];
	long eski_kayit_adresi = kayit_adresi;

	git_xy(0, 0);
	gettext(4, 4, 40, 20, bellek);
	liste_formu(3, 4);
	dosya_ac(handle);
	kayit_adresi = liste_kutusu(5, 5, 0, 13, 22, BEYAZ_ | SIYAH, SIYAH_ | A_BEYAZ, handle);
	puttext(4, 4, 40, 20, bellek);
	if (kayit_adresi == -2) {
		msj_kutu(NULL, UYARI_LISTE_BOS, UYARI);
		kayit_adresi = eski_kayit_adresi;
	}
	else if (kayit_adresi == -1)
		kayit_adresi = eski_kayit_adresi;
	else {
		kayit_adresi = indeks_gezgini(handle, kayit_adresi);
		detay_oku(handle, kayit_adresi, DATA_AL);
		memcpy(dataci, handle->ana_detay->data, handle->ana_baslik->bir_datanin_uzunlugu);
		yeni_goruntusu(KAPALI);
		indeks_bilgisi(tablo, &baslik, INDEKS_KAPA);
	}
	dosya_kapa(handle);
}