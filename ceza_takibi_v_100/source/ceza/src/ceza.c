#include "/ozgan/programs/h/genel.h"
#include "src/ceza.h"
long kayit_adresi;
char *dataci;
TABLO_BILGI baslik;
TABLO_FORM *tablo;
HESAP_TABLO_DATA hesap_tablo_data;
TABLO_DATA *tablo_data;
YENI_DATA *yeni_data;
YENI_INDEKS *yeni_indeks;
void f6_tusu(int referans);
/*-----------------------------------------------------------------------*/
void mesaj_goster_kac(char *string)
{
	char *bellek;
	int alan;

	bellek = malloc(1000);
	gettext(60, 25, 80, 25, bellek);
	alan = strlen(string);

	if (alan > 20)
		strcpy(&string[18], "...");

	doldur(24, 63, ' ', 20, BEYAZ_);
	harfler(24, 63, string, BEYAZ_ | SIYAH);
	delay(350);
	puttext(60, 25, 80, 25, bellek);
	free(bellek);
}

int islem(void)
{
	int ch;

	if (renkli != -1)
		tarih();
	ch = getkb();
	switch (ch) {
		case F1 : break;
		case F2 : f2_tusu(baslik.referans); break;
		case F3 : f3_tusu(baslik.referans); break;
		case F4 : f4_tusu(baslik.referans); break;
		case F5 : f5_tusu(baslik.referans); break;
		case F6 : f6_tusu(baslik.referans); break;
		default : return ch;
	}
	return ch;
}

void kmenu_islem(char *data, TABLO_FORM *tablo, TABLO_BILGI *baslik, int sayac)
{
	switch (tablo[sayac].referans) {
		case 1:
		break;
	}
}

int menu_sec(char *veri, int satir, int kolon, int uzunluk, int eleman_referansi, char *depo_dizi)
{
	MENU menu;
	int ch;

	mib_al(&menu);

	switch (eleman_referansi) {
		case KMenu_CEZA_AYLARI: menuyukle("bin/menulist.mnu", KMenu_CEZA_AYLARI, &menu);
								menu.BaslangicSatiri = satir;
								menu.BaslangicKolonu = kolon;
								menu.BitisSatiri = satir + 2;
								menu.BitisKolonu = kolon + uzunluk;
	}
	if (depo_dizi == NULL)
		ch = menu_cagir(&menu, veri);
	else {
		if (veri[0] == 0)
			veri[0] = '0';

		dizi_yapici(&menu, (char) atoi(veri), depo_dizi);
		harfler(satir, kolon, depo_dizi, menu.AktifSecili);
	}
	mib_ver(&menu);
	return ch;
}

void tarih(void)
{
	/* Bu fonksiyon ekranda iüinizi yaptçßçnçz halde saati áalçütçran
	bir fonksiyondur. */
	int j = 0;
	struct tm *p;
	long t_old, t_new = 0, saniye;
	char temp[50];
	char *string = "Ozgan & Kiraz Operation Systems";

	while (!kbhit()) {
		t_old = time(NULL);
		p = localtime(&t_old);
		if (t_old != t_new) {
			t_old = time(NULL);
			p = localtime(&t_old);
			t_new = t_old;
			++j;
		}
		if (j == 1) {
			saniye = time(NULL);
			p = localtime(&saniye);
			sprintf(temp, "%02d/%02d/%04d - ",
			p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
			j = 0;
			rengarenk(0, 48, string, 31, BEYAZ_ | SIYAH);
		}
	}
}

void cerceve(void)
{
	int n;

	for (n = 0; n < 25; n++)
		doldur(n, 0, '∞', 80, BEYAZ_ | MAVI);
	doldur(0, 0, ' ', 80, BEYAZ_);
	doldur(24, 0, ' ', 80, BEYAZ_);
	cift(0, 1, "-  Yeni  Hesapla  Tablo  Äçkçü                     ", BEYAZ_ | SIYAH);
	cift_renk(0, 1, "&-  &Yeni  &Hesapla  &Tablo  Äç&kçü", BEYAZ_ | SIYAH, BEYAZ_ | KIRMIZI);
	cift_renk(24, 1, "&F&1 Yardçm ≥                                                 ≥  SÅrÅm v.1.01b  ", BEYAZ_ | SIYAH, BEYAZ_ | KIRMIZI);
	harfler(0, 48, "Ozgan & Kiraz Operation Systems", BEYAZ_ | SIYAH);
}

void menu(void)
{
	char *data = "000";
	int ch;
	MENU menu;

BAS:
	mib_al(&menu);
	menuyukle("bin/menulist.mnu", YMenu_ANA_MENU, &menu);
	ch = menu_cagir(&menu, data);
	mib_ver(&menu);

	if (ch != ESC)
		switch (data[0]) {
			case '0': yeni(); break;
			case '1': hesapla(); break;
			case '2': rapor(); break;
			case '3': cikis(); goto BAS;
		}
}

void hos_geldiniz(void)
{
	int n;

	for (n = 0; n < 13; n++)
		doldur(7+n, 18, ' ', 43, BEYAZ_ | A_BEYAZ);
	kalin_cerceve(7, 19, 11, 40, BEYAZ_ | A_BEYAZ);
	doldur(8, 21, ' ', 37, KAHVE_);
	harfler(8, 32, " Hoü Geldiniz! ", KAHVE_ | A_BEYAZ);
	disa_pen(9, 21, 8, 36);
	harfler(10, 24, "Ozgan & Kiraz Operation Systems", BEYAZ_ | A_BEYAZ);
	harfler(12, 32, "Faiz Hesaplayçcç", BEYAZ_ | SIYAH);
	harfler(13, 35, " v.1.01b", BEYAZ_ | SIYAH);
	harfler(15, 30, "   0533 362 35 65 ", BEYAZ_ | GRI);
	harfler(16, 30, "okos.programlari.com", BEYAZ_ | GRI);
	harfler(17, 29, "okosoft@programmer.net", BEYAZ_ | GRI);
}

void f2_tusu(int referans)
{
	DOSYA handle;

	handle.tablo = tablo;
	handle.baslik = baslik;

	switch (referans) {
		case Form_YENI:
			handle.data = (char *) dataci;
			yeni_data = (YENI_DATA *) dataci;
			strcpy(handle.ana_dosya, "yeni.dat");
			strcpy(handle.indeks_dosya, "yeni.ind");
			strcpy(handle.yol, "data/");
			yeni_kayit(&handle);
			break;
		case Form_HESAP:
			hesap_data = (HESAP_DATA *) dataci;
			referans_yap();
			if (oran_bul(hesap_data->Referans, hesap_data->Oran) == 0 && strlen(hesap_data->Ana_Para) >= 3) {
				islemleri_yap();
				hesap_kayit();
				hesap_goruntusu();
			}
			else if (strlen(hesap_data->Ana_Para) <= 3)
				msj_kutu(NULL, "Anapara oranç 100'den dÅüÅk olamaz", UYARI);
			break;
		case Form_RAPOR:
			if (handle.indeks_baslik->toplam_kayit != 0)
				tablo_olustur();
			else
				msj_kutu(NULL, "ônce hesaplama yapmalçsçnçz", UYARI);
	}
}

void f3_tusu(int referans)
{
	DOSYA handle;

	handle.tablo = tablo;
	handle.baslik = baslik;

	switch (referans) {
		case Form_YENI:
			handle.data = (char *) dataci;
			yeni_data = (YENI_DATA *) dataci;
			strcpy(handle.ana_dosya, "yeni.dat");
			strcpy(handle.indeks_dosya, "yeni.ind");
			strcpy(handle.yol, "data/");
			yeni_kayit_sil(&handle);
			f4_tusu(referans);
			break;
		case Form_HESAP:
			hesap_data = (HESAP_DATA *) dataci;
			hesap_kayit_sil(); break;
		case Form_RAPOR:
			if (msj_kutu(NULL, "Yazçcçnçzç hazçrladçnçz mç?", SORU) == EVET)
				yazici_form();
	}
}

void f4_tusu(int referans)
{
	DOSYA handle;
	handle.tablo = tablo;
	handle.baslik = baslik;

	switch (referans) {
		case Form_YENI:
			handle.data = (char *) dataci;
			yeni_data = (YENI_DATA *) dataci;
			strcpy(handle.ana_dosya, "yeni.dat");
			strcpy(handle.indeks_dosya, "yeni.ind");
			strcpy(handle.yol, "data/");
			yeni_yeni();
			break;
		case Form_HESAP:
			kayit_adresi = 0;
			memset(dataci, 0, baslik.data_uzunlugu);
			hesap_goruntusu();
			doldur(11, 35, ' ', 20, BEYAZ_);
			uyari_gonder(0);
		case Form_RAPOR: ;
	}
}

void f5_tusu(int referans)
{
	DOSYA handle;

	handle.tablo = tablo;
	handle.baslik = baslik;

	switch (referans) {
		case Form_YENI:
			handle.data = (char *) dataci;
			yeni_data = (YENI_DATA *) dataci;
			strcpy(handle.ana_dosya, "yeni.dat");
			strcpy(handle.indeks_dosya, "yeni.ind");
			strcpy(handle.yol, "data/");
			yeni_liste(&handle);
			break;
		case Form_HESAP:
			hesap_liste(); break;
		case Form_RAPOR: ;
	}
}

void f6_tusu(int referans)
{
	DOSYA handle;

	handle.tablo = tablo;
	handle.baslik = baslik;

	switch (referans) {
		case Form_YENI:
			handle.data = (char *) dataci;
			yeni_data = (YENI_DATA *) dataci;
			strcpy(handle.ana_dosya, "yeni.dat");
			strcpy(handle.indeks_dosya, "yeni.ind");
			strcpy(handle.yol, "data/");
			yeni_duzenle(&handle);
			break;
		case Form_HESAP:
			hesap_yeni_dosya(); break;
		case Form_RAPOR: ;
	}
}

void main(void)
{
	uyarici = -1;
	clrscr();
	renkli = -1;
	if (sifre_kontrol() == 1)
		program_kayit();
	else {
		hos_geldiniz();
		getch();
	}
	renkli = 31;
	git_xy(-1, 0);
	cerceve();
BAS:
	menu();
	cikis();
	goto BAS;
}