#include "/ozgan/programs/h/genel.h"
#include "src/ceza.h"

void rapor(void)
{
	int n;
	char *p;

	p = (char *) malloc(4000 * 2);
	if (p == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	gettext(1, 2, 80, 24, p);
	for (n = 0; n < 22; n++)
		doldur(1+n, 0, ' ', 79, BEYAZ_ | A_BEYAZ);
	doldur(2, 2, ' ', 76, KAHVE_);
	harfler(2, 31, " KiŸiye ™zel Rapor ", KAHVE_ | A_BEYAZ);
	kalin_cerceve(1, 0, 21, 79, BEYAZ_ | A_BEYAZ);
	disa_pen(3, 2, 4, 75);
	harfler(4, 4, "šnvan                                V.D                V.N             ", BEYAZ_ | SIYAH);
	harfler(5, 4, "Toplam Faiz Oran (binde)            Taksit Says", BEYAZ_ | SIYAH);
	doldur(6, 3, 'Ä', 74, BEYAZ_ | GRI);
	harfler(7, 4, "Vadeli Bor‡ Toplam                   Aylk Bor‡ Tutar ", BEYAZ_ | SIYAH);
	disa_pen(9, 2, 12, 75);
	cift_renk(10, 4, "    Tarih    &³  Oran  &³    Ana Para    &³  Faiz  Tutar  &³  Toplam Bor‡  ", KAHVE_ | A_BEYAZ, KAHVE_ | BEYAZ);
	doldur(20, 3, 'Í', 74, BEYAZ_ | GRI);
	for (n = 0; n < 11; n++) {
		harf(11+n, 17, '³', BEYAZ_ | GRI);
		harf(11+n, 26, '³', BEYAZ_ | GRI);
		harf(11+n, 43, '³', BEYAZ_ | GRI);
		harf(11+n, 60, '³', BEYAZ_ | GRI);
	}
	cift_renk(24, 12, " &F&2 OluŸtur  &F&3 Yazc", BEYAZ_ | SIYAH, BEYAZ_ | KIRMIZI);
	tablo_form();
	puttext(1, 2, 80, 24, p);
	doldur(24, 12, ' ', 40, BEYAZ_);
	free(p);
	menu();
}

void tablo_form(void)
{
	TABLO_BILGI baslik2 = {11, sizeof(TABLO_DATA), Form_RAPOR, 0};
	TABLO_FORM tablo2[] = {{Data_Rapor, YAZI, 2, 9, 30, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, YAZI, 2, 44, 14, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, YAZI, 2, 63, 12, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, SAYI, 3, 32, 6, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, SAYI, 3, 55, 3, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, SAYI, 5, 24, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor, SAYI, 5, 60, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor, SAYI, 19, 27, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor, SAYI, 19, 44, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor, SAYI, 19, 60, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK}
						  };

	tabloyarat("bin/rapor.tbl", &baslik2, tablo2);
	tablo = (TABLO_FORM *) tabloyukle("bin/rapor.tbl", &baslik);
	dataci = (char *) malloc(baslik.data_uzunlugu);
	if (dataci == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	memset(dataci, 0, baslik.data_uzunlugu);
	tablo_data = (TABLO_DATA *) dataci;
	tablo_oynatici(2, 1, Data_Rapor, (char *) dataci, tablo, &baslik);
	git_xy(0, 0);
	kayit_adresi = 0;
	baslik.referans = 0;
	free(dataci);
}

void hesap_tablo_form(int satir, int kolon)
{
	TABLO_BILGI baslikci = {5, sizeof(HESAP_TABLO_DATA), Form_RAPOR, 0};
	TABLO_FORM tablocu[] = {{Data_Rapor, YAZI, 9, 3, 12, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, SAYI, 9, 18, 6, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, SAYI, 9, 27, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, SAYI, 9, 44, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor, SAYI, 9, 60, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA}
						  };

	memset(&hesap_tablo_data, 0, baslikci.data_uzunlugu);
	strcpy(hesap_tablo_data.Tarih, hesap_data->Referans);
	strcpy(hesap_tablo_data.Oran, hesap_data->Oran);
	strcpy(hesap_tablo_data.Ana_Para, hesap_data->Ana_Para);
	strcpy(hesap_tablo_data.Faiz_Tutari, hesap_data->Faiz_Tutari);
	strcpy(hesap_tablo_data.Toplam_Borc, hesap_data->Borc_Toplami);

	tablo_yerlestir(satir, kolon, Data_Rapor, (char *) &hesap_tablo_data, tablocu, &baslikci);
}

void ektre_topla(void)
{
	DOSYA handle;
	long adres;
	int n;
	char g_ana[50], g_faiz[50], g_toplam[50];
	char t_ana[50], t_faiz[50], t_toplam[50];

	memset(t_ana, 0, 50);
	memset(t_faiz, 0, 50);
	memset(t_toplam, 0, 50);

	strcpy(handle.ana_dosya, "hesap.dat");
	strcpy(handle.indeks_dosya, "hesap.ind");
	strcpy(handle.yol, "data/");

	handle.data = malloc(sizeof(HESAP_DATA));
	if (handle.data == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	dosya_ac(&handle);
	hesap_data = (HESAP_DATA *) handle.data;

	adres = handle.indeks_baslik->ilk_kayit;
	for (n = 0; n < handle.indeks_baslik->toplam_kayit; n++) {
		detay_oku(&handle, adres, DATA_AL);
		memcpy(handle.data, handle.ana_detay->data, handle.ana_baslik->bir_datanin_uzunlugu);
		memset(g_ana, 0, 50);
		memset(g_faiz, 0, 50);
		memset(g_toplam, 0, 50);
		strcpy(g_ana, t_ana);
		strcpy(g_faiz, t_faiz);
		strcpy(g_toplam, t_toplam);
		toplama(hesap_data->Ana_Para, g_ana, t_ana);
		toplama(hesap_data->Faiz_Tutari, g_faiz, t_faiz);
		toplama(hesap_data->Borc_Toplami, g_toplam, t_toplam);
		adres = handle.indeks_detay->sonraki;
		if (n < 9)
			hesap_tablo_form(2+n, 1);
	}
	strcpy(tablo_data->Ana_Para_Toplam, t_ana);
	strcpy(tablo_data->Faiz_Toplam, t_faiz);
	strcpy(tablo_data->Genel_Toplam, t_toplam);
	dosya_kapa(&handle);
	free(handle.data);
}

void vade_hesapla(void)
{
	char faiz_tutari[50], binde_orani[50], taksit_sayisi[50], binde[50];

	memset(faiz_tutari, 0, 50);
	memset(binde_orani, 0, 50);
	memset(binde, 0, 50);
	memset(taksit_sayisi, 0, 50);

	strcpy(binde, "1000");
	strcpy(binde_orani, tablo_data->Binde_Oran);
	bolme(tablo_data->Genel_Toplam, binde, taksit_sayisi);
	carpma(taksit_sayisi, binde_orani, faiz_tutari);
	toplama(faiz_tutari, tablo_data->Genel_Toplam, tablo_data->Toplam_Hesap);
	memset(taksit_sayisi, 0, 50);
	strcpy(taksit_sayisi, tablo_data->Taksit);
	bolme(tablo_data->Toplam_Hesap, taksit_sayisi, tablo_data->Aylik_Hesap);
}

char *tablo_liste_elemani(int satir, int kolon, char *string, DOSYA *handle, int baslangic, int uzunluk, int boy, int renk)
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
		detay_oku(handle, adres, DATA_AL);
		adres = handle->indeks_detay->sonraki;
		hesap_data = (HESAP_DATA *) handle->ana_detay->data;
		hesap_tablo_form(satir-9+boy_sayaci, kolon-3);
		string[(boy_sayaci * kontrol)] = ' ';
		strcpy(&string[(boy_sayaci * kontrol)], hesap_data->Referans);

		for (sayac = 1; sayac < kontrol; sayac++) {
			if (string[(boy_sayaci * kontrol) + sayac] == '\0')
				string[(kontrol * boy_sayaci) + sayac] = ' ';
		}
		string[(kontrol * boy_sayaci) + sayac-1] = '\0';
	}
	data_dosyasini_kapa(indeks);
	return string;
}

long tablo_liste_kutusu(int satir, int kolon, int baslangic, int boy, int en, int renk1, int renk2, DOSYA *handle)
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

	tablo_liste_elemani(satir, kolon, eleman, handle, baslangic, en, boy, renk1);
	for (;;) {
		if (yeni_baslangic != baslangic) {
			yeni_baslangic = baslangic;
			tablo_liste_elemani(satir, kolon, eleman, handle, baslangic, en, boy, renk1);
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
							mesaj_goster_kac(" Dosya BaŸ ...");
						}
						else if (bayrak == 1) {
							baslangic = 0;
							isaretli_sayac = 0;
							mesaj_goster_kac(" Dosya BaŸ ...");
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

		if (baslangic == toplam - boy + 1 && bayrak == 0) {
			baslangic = toplam - boy;
			mesaj_goster_kac(" Dosya Sonu ...");
		}
		else if (baslangic == toplam - boy + 1 && bayrak == 1) {
			baslangic = 0;
			mesaj_goster_kac(" Dosya Sonu ...");
		}

		if (baslangic == -1) {
			baslangic = 0;
			mesaj_goster_kac(" Dosya BaŸ ...");
		}
	}
}

void tablo_goruntusu(void)
{
	int i;
	memset(dataci, 0, baslik.data_uzunlugu);
	tablo_yerlestir(2, 1, Data_Rapor, (char *) dataci, tablo, &baslik);
	for (i = 0; i < 9; i++) {
		doldur(11+i, 4, ' ', 13, BEYAZ_);
		doldur(11+i, 19, ' ', 6, BEYAZ_);
		doldur(11+i, 27, ' ', 16, BEYAZ_);
		doldur(11+i, 44, ' ', 16, BEYAZ_);
		doldur(11+i, 61, ' ', 16, BEYAZ_);
	}
}

void tablo_olustur(void)
{
	DOSYA handle;

	handle.data = malloc(sizeof(HESAP_DATA));
	strcpy(handle.ana_dosya, "hesap.dat");
	strcpy(handle.indeks_dosya, "hesap.ind");
	strcpy(handle.yol, "data/");
	handle.tablo = (TABLO_FORM *) tabloyukle("bin/hesap.tbl", &handle.baslik);

	ektre_topla();
	vade_hesapla();
	tablo_yerlestir(2, 1, Data_Rapor, (char *) dataci, tablo, &baslik);

	dosya_ac(&handle);
	tablo_liste_kutusu(11, 4, 0, 9, 14, BEYAZ_ | GRI, SIYAH_ | A_BEYAZ, &handle);
	tablo_goruntusu();
	dosya_kapa(&handle);
}