#include "/ozgan/programs/h/genel.h"
#include "src/ceza.h"

void program_kayit(void)
{
	int n;
	char Parola[50], Karsi_Deger[50], gecici[50];

	uyarici = -1;
	for (n = 0; n < 16; n++)
		doldur(5+n, 18, ' ', 43, BEYAZ_ | A_BEYAZ);
	kalin_cerceve(5, 19, 14, 40, BEYAZ_ | A_BEYAZ);
	doldur(6, 21, ' ', 37, KAHVE_);
	harfler(6, 32, " HoŸ Geldiniz! ", KAHVE_ | A_BEYAZ);
	disa_pen(7, 21, 11, 36);
	harfler(8, 24, "Ozgan & Kiraz Operation Systems", BEYAZ_ | A_BEYAZ);
	harfler(10, 32, "Faiz Hesaplayc", BEYAZ_ | SIYAH);
	harfler(11, 35, " v.1.00a", BEYAZ_ | SIYAH);
	harfler(13, 30, "   0533 362 35 65 ", BEYAZ_ | GRI);
	harfler(14, 30, "okos.programlari.com", BEYAZ_ | GRI);
	harfler(15, 29, "okosoft@programmer.net", BEYAZ_ | GRI);
	doldur(16, 24, 'Ä', 31, BEYAZ_ | GRI);
	harfler(17, 23, "Kilit  ", BEYAZ_ | SIYAH);
	harfler(18, 23, "Anahtar", BEYAZ_ | SIYAH);

	sifre_getir(Parola, Karsi_Deger);
	formatla(Parola, gecici, "####-####-####-####-####");
	harfler(17, 31, gecici, BEYAZ_ | SIYAH);
	n = 0;
BAS:
	memset(gecici, ' ', 50);
	format_yaz(gecici, "####-####", "1234567890ABCDEFabcdef", 18, 31, 9, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI);
	strupr(gecici);
	if (strcmp(gecici, Karsi_Deger) != 0) {
		msj_kutu(NULL, "Hatal Parametre GiriŸi", HATA);
		if (n >= 2) {
			clrscr();
			exit(1);
		}
		else {
			n++;
			goto BAS;
		}
	}
	else
		sifre_dosyasi_yap();
}

char *sifre_getir(char *Parola, char *Karsi_Deger)
{
	time_t timer;
	unsigned long sayi;
	int i;

	for (i = 0; i < 3; i++) {
		timer = time(NULL);
		timer *= random(timer*random(timer));
		ltoa(timer, &Parola[i*8], 10);
	}
	for (i = 0; i < strlen(Parola); i++)
		if (Parola[i] == '-')
			Parola[i] = '0';

	strncpy(Karsi_Deger, &Parola[4], 10);
	sayi = atol(Karsi_Deger);
	sayi *= 0.9;
	ltoa(sayi, Karsi_Deger, 16);
	strupr(Karsi_Deger);
	return Karsi_Deger;
}

void sifre_dosyasi_yap(void)
{
	FILE *fp;
	int i;
	char alan[4096];

	if ((fp = fopen("bin/OKos.SYS", "wb")) == NULL) {
		msj_kutu("OKos.SYS", HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}
	fwrite(alan, 1, 4096, fp);
	memset(alan, 0, 4096);
	for (i = 0; i < 3; i++)
		biosdisk(2, 0x80, 0, 0, 1, 1, alan);
	fseek(fp, 492, SEEK_SET);
	fwrite(alan, 1, 512, fp);
	fclose(fp);
}

int sifre_kontrol(void)
{
	FILE *fp;
	int i;
	char alan[512], disk[512];

	if ((fp = fopen("bin/OKos.SYS", "rb")) == NULL)
		return 1;

	for (i = 0; i < 3; i++)
		biosdisk(2, 0x80, 0, 0, 1, 1, disk);
	fseek(fp, 492, SEEK_SET);
	fread(alan, 1, 512, fp);
	if (memcmp(alan, disk, 512) != 0) {
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 0;
}
