#include "/ozgan/programs/h/genel.h"
#include "src/ceza.h"
HESAP_DATA *hesap_data;

void hesap_goruntusu(void)
{
	tablo_yerlestir(8, 17, Data_Hesap, (char *) dataci, tablo, &baslik);
}

void hesapla(void)
{
	int n;
	char *p;

	p = (char *) malloc(4000 * 2);
	if (p == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	gettext(1, 2, 76, 23, p);

	for (n = 0; n < 12; n++)
		doldur(8+n, 20, '∞', 44, SIYAH_ | BEYAZ);

	for (n = 0; n < 12; n++)
		doldur(7+n, 18, ' ', 44, BEYAZ_ | A_BEYAZ);
	kalin_cerceve(7, 19, 10, 41, BEYAZ_ | A_BEYAZ);
	doldur(8, 21, ' ', 38, KAHVE_);
	harfler(8, 35, " Hesaplama ", KAHVE_ | A_BEYAZ);
	disa_pen(9, 21, 2, 37);
	cift_renk(10, 23, "Hesap Tarihi [ &O&c&a&k& & &  \x1f] Yçl", BEYAZ_ | SIYAH, BEYAZ_ | A_BEYAZ);
	harfler(11, 23, "    Ana Para", BEYAZ_ | SIYAH);
	disa_pen(13, 21, 3, 37);
	harfler(14, 23, "Hesaplanan Oran", BEYAZ_ | SIYAH);
	harfler(15, 23, "    Faiz Tutarç", BEYAZ_ | SIYAH);
	harfler(16, 23, "   Borá Toplamç", BEYAZ_ | SIYAH);
	cift_renk(24, 12, " &F&2 Hesapla  &F&3 Sil  &F&4 Yeni  &F&5 Liste  &F&6 Dosya", BEYAZ_ | SIYAH, BEYAZ_ | KIRMIZI);
	hesap_form();
	puttext(1, 2, 76, 23, p);
	doldur(24, 12, ' ', 48, BEYAZ_);
	free(p);
	menu();
}

void hesap_form(void)
{
	TABLO_BILGI baslik2 = {7, 102, Form_HESAP, 0};
	TABLO_FORM tablo2[] = {{Data_Hesap, KAPALI_MENU, 2, 20, 9, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, KMenu_CEZA_AYLARI, SONRA},
						   {Data_Hesap, YAZI, 2, 36, 4, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Hesap, YAZI, 3, 25, 10, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Indeks_Bilgisi, YOK},
						   {Data_Hesap, SAYI, 3, 25, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Indeks_Bilgisi, SONRA},
						   {Data_Hesap, SAYI, 6, 21, 19, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Hesap, SAYI, 7, 21, 19, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Hesap, SAYI, 8, 21, 19, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK}
						  };

	tabloyarat("bin/hesap.tbl", &baslik2, tablo2);
	tablo = (TABLO_FORM *) tabloyukle("bin/hesap.tbl", &baslik);
	dataci = (char *) malloc(baslik.data_uzunlugu);
	if (dataci == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	memset(dataci, 0, baslik.data_uzunlugu);
	hesap_data = (HESAP_DATA *) dataci;
	tablo_oynatici(8, 17, Data_Hesap, (char *) dataci, tablo, &baslik);
	git_xy(0, 0);
	kayit_adresi = 0;
	baslik.referans = 0;
	free(dataci);
}

void referans_yap(void)
{
	char temp[5];

	memset(temp, 0, 5);
	strcpy(hesap_data->Referans, hesap_data->Yil);
	strcat(hesap_data->Referans, "-");
	if ((strlen(hesap_data->Ay) == 1) && hesap_data->Ay[0] != '9') {
		temp[0] = '0';
		temp[1] = hesap_data->Ay[0] + 1;
	}
	else if (hesap_data->Ay[0] == '9') {
		temp[0] = '1';
		temp[1] = '0';
	}
	else {
		temp[0] = hesap_data->Ay[0];
		temp[1] = hesap_data->Ay[1] + 1;
	}
	strcat(hesap_data->Referans, temp);
}

int oran_bul(char *referans, char *oran)
{
	int i;
	DOSYA handle;
	long adres;

	strcpy(handle.ana_dosya, "yeni.dat");
	strcpy(handle.indeks_dosya, "yeni.ind");
	strcpy(handle.yol, "data/");

	dosya_ac(&handle);
	adres = handle.indeks_baslik->ilk_kayit;
	for (i = 0; i < handle.ana_baslik->toplam_kayit; i++) {
		detay_oku(&handle, adres, DATA_AL);
		yeni_data = (YENI_DATA *) handle.ana_detay->data;
		yeni_indeks = (YENI_INDEKS *) handle.indeks_detay->data;
		adres = handle.indeks_detay->sonraki;

		if (strcmp(referans, yeni_indeks->Referans) == 0) {
			strcpy(oran, yeni_data->Oran_Tutucu);
			i = 0;
			goto SON;
		}
	}
	msj_kutu(NULL, "Tarih kayçtlç deßil", HATA);
	i = 1;
SON:
	dosya_kapa(&handle);
	return i;
}

void islemleri_yap(void)
{
	char gecici[30];
	char yuzde[30];
	char bt[30];
	char ap[30];
	char ft[30];
	char oran[30];

	memset(gecici, 0, 30);
	memset(yuzde, 0, 30);
	memset(bt, 0, 30);
	memset(ap, 0, 30);
	memset(ft, 0, 30);
	memset(oran, 0, 30);

	strcpy(yuzde, "100");
	strcpy(ap, hesap_data->Ana_Para);
	strcpy(oran, hesap_data->Oran);
	strcpy(ft, hesap_data->Faiz_Tutari);

	bolme(ap, yuzde, gecici);
	carpma(gecici, oran, ft);
	toplama(ft, ap, bt);

	strcpy(hesap_data->Ana_Para, ap);
	strcpy(hesap_data->Oran, oran);
	strcpy(hesap_data->Faiz_Tutari, ft);
	strcpy(hesap_data->Borc_Toplami, bt);
}

void hesap_yeni_dosya(void)
{
	DOSYA handle;

	handle.tablo = tablo;
	handle.baslik = baslik;

	strcpy(handle.ana_dosya, "hesap.dat");
	strcpy(handle.indeks_dosya, "hesap.ind");
	strcpy(handle.yol, "data/");

	if (msj_kutu(NULL, "Yeni dosya oluüturulsun mu?", SORU) == EVET) {
		dosya_yarat(&handle);
		f4_tusu(baslik.referans);
	}
}

void hesap_kayit(void)
{
	DOSYA handle;

	handle.tablo = tablo;
	handle.baslik = baslik;
	strcpy(handle.ana_dosya, "hesap.dat");
	strcpy(handle.indeks_dosya, "hesap.ind");
	strcpy(handle.yol, "data/");
	handle.data = (char *) dataci;

	if (strlen(hesap_data->Referans) == 0) {
		msj_kutu(NULL, "ônce hesap yapmalçsçnçz", UYARI);
		goto SON;
	}
	if (kayit_adresi == 0) {
		kayit_adresi = dosya_kayit(&handle);
		if (kayit_adresi == 0)
			msj_kutu(NULL, UYARI_KAYIT_MEVCUT, UYARI);
		else {
			mesaj_goster_kac("Kayçt_Eklendi");
			indeks_bilgisi(tablo, &baslik, INDEKS_KAPA);
		}
	}
	else {
		dosya_ac(&handle);
		detay_oku(&handle, kayit_adresi, DATA_ALMA);
		memcpy(handle.ana_detay->data, dataci, baslik.data_uzunlugu);
		indeks_uzunlugu(&handle, handle.indeks_detay->data);
		eski_kayit(&handle, kayit_adresi);
		dosya_kapa(&handle);
		mesaj_goster_kac("Deßiütirildi !..");
	}
SON:
}

void hesap_kayit_sil(void)
{
	DOSYA handle;

	handle.tablo = tablo;
	handle.baslik = baslik;
	strcpy(handle.ana_dosya, "hesap.dat");
	strcpy(handle.indeks_dosya, "hesap.ind");
	strcpy(handle.yol, "data/");
	handle.data = (char *) dataci;

	if (kayit_adresi != 0) {
		if (msj_kutu(NULL, SORU_KAYDI_SILMEK, SORU) == EVET) {
			dosya_ac(&handle);
			data_sil(&handle, kayit_adresi);
			dosya_kapa(&handle);
			f4_tusu(baslik.referans);
			mesaj_goster_kac("Kayçt Silindi...");
		}
	}
	else
		mesaj_goster_kac("Kayçt etmediniz...");
}

void hesap_liste_formu(int satir, int kolon)
{
	int i;

	golgele(satir+1, kolon+1, 15, 29, SIYAH_ | BEYAZ);
	for (i = 0; i < 15; i++) {
		doldur(satir+i, kolon-1, ' ', 29, CYAN_);
		doldur(satir+i, kolon+1, ' ', 26, BEYAZ_);
	}
	kalin_cerceve(satir, kolon, 13, 26, CYAN_ | A_BEYAZ);
	doldur(satir+1, kolon+1, ' ', 21, KAHVE_);
	cift_renk(satir+1, kolon+2, "  Tarih   &≥  Ana Para   ", KAHVE_ | A_BEYAZ, KAHVE_ | BEYAZ);
	harfler(satir, kolon+6, " Hesaplananlar ", CYAN_ | A_BEYAZ);
}

void hesap_liste(void)
{
	char bellek[3500];
	long eski_kayit_adresi = kayit_adresi;
	DOSYA handle;

	handle.data = (char *) dataci;
	handle.tablo = tablo;
	handle.baslik = baslik;
	strcpy(handle.ana_dosya, "hesap.dat");
	strcpy(handle.indeks_dosya, "hesap.ind");
	strcpy(handle.yol, "data/");

	git_xy(0, 0);
	gettext(4, 4, 40, 20, bellek);
	hesap_liste_formu(3, 4);
	dosya_ac(&handle);
	kayit_adresi = liste_kutusu(5, 5, 0, 12, 26, BEYAZ_ | SIYAH, SIYAH_ | A_BEYAZ, &handle);
	puttext(4, 4, 40, 20, bellek);
	if (kayit_adresi == -2) {
		msj_kutu(NULL, UYARI_LISTE_BOS, UYARI);
		kayit_adresi = eski_kayit_adresi;
	}
	else if (kayit_adresi == -1)
		kayit_adresi = eski_kayit_adresi;
	else {
		kayit_adresi = indeks_gezgini(&handle, kayit_adresi);
		detay_oku(&handle, kayit_adresi, DATA_AL);
		memcpy(dataci, handle.ana_detay->data, handle.ana_baslik->bir_datanin_uzunlugu);
		indeks_bilgisi(tablo, &baslik, INDEKS_KAPA);
	}
	hesap_goruntusu();
	uyari_gonder(0);
	dosya_kapa(&handle);
}