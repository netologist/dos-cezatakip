#include "/ozgan/programs/h/genel.h"

int renkli = 24;  /* Rengarenk fonksiyonunda men i‡indir */
char far *vp = (char far*) 0xb8000000; /* vp de§iŸkeni ekrann adresini tutar */
int ekran_x;
int ekran_y;

void rengarenk(int satir, int kolon, char *string, int uzunluk, int renk)
{
	int tektek = 0, string_toplam = 0;      /* renkli global bir de§iŸkendir */
	char *temp;

	string_toplam = strlen(string);

	temp = (char *) malloc(3 * string_toplam);
	if (!temp) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}

	string_toplam = strlen(string);

	if (renkli >= uzunluk) {
		strcpy(temp, &string[renkli - uzunluk]);
		temp[uzunluk - tektek] = '\0';
		doldur(satir, kolon, ' ', (uzunluk+1), renk);
		harfler(satir, kolon, temp, renk);
		tektek++; renkli++;
		if (renkli > ((uzunluk * 3) + (string_toplam - (2 * uzunluk)))) {
			renkli = 0;
			tektek = 0;
		}
	free(temp);
	return;
	}
	strncpy(temp, string, renkli);
	temp[renkli] = '\0';
	harfler(satir, kolon + (uzunluk - renkli), temp, renk);
	++renkli;
	free(temp);
}

void cift(int satir, int kolon, char *string, int renk)
{
	char *temp1, *temp2, *temp3;
	int sag = 0, sol = 0, i = 0, orta = 0;
	int uzunluk;

	uzunluk = strlen(string);
	orta = strlen(string) / 2;
	sag = orta;
	sol = strlen(string) - sag;
	temp1 = (char *) malloc(sol + 1);
	temp2 = (char *) malloc(sol + 1);
	temp3 = (char *) malloc(sol + 1);

	if (!(temp1 || temp2 || temp3)) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	strncpy(temp2, string, sag);
	strcpy(temp1, &string[sag]);
	temp1[sol] = '\0';
	temp2[sag] = '\0';

	if (sol != sag)
	orta++;

	for (i = 0; i < orta; i++) {
		strncpy(temp3, temp1, i);
		temp3[i] = '\0';
		sol--; sag--;
		delay(5);
		harfler(satir, kolon, &temp2[sol], renk);
		harfler(satir, (kolon + uzunluk) - i, temp3, renk);
	}
	strncpy(temp3, temp1, i);
	temp3[i] = '\0';
	harfler(satir, (kolon + uzunluk) - i, temp3, renk);
	free(temp1);
	free(temp2);
	free(temp3);
	return;
}

void cikis(void)
{
	int i;
	char *cikis_kontrol = "0";

	if (cikis_kontrol[0] == '0') {
		cikis_kontrol[0] = '1';
		if (!msj_kutu(NULL, SORU_CIKMAK, SORU)) {
			cikis_kontrol[0] = '0';
			goto SON;
		}
	}
	else
		goto SON;
	git_xy(0, 0);
	for (i = 0; i < 12; i++) {
		doldur(0+i, 0, ' ', 80, SIYAH_ | BEYAZ);
		doldur(24-i, 0, ' ', 80, SIYAH_ | BEYAZ);
		delay(20);
	}
	doldur(12, 0, 'Ä', 80, SIYAH_ | A_BEYAZ);
	cift(12, 0, "                                                                                ", SIYAH_ | BEYAZ);
	exit(1);
SON:
}

void dikey_cubuk(int satir, int kolon, int boy, int renk1, int renk2)
{
	int i;

	for (i = 0; i < boy-1; i++)
		harf((satir+1)+i, kolon, '±', renk1);

	harf(satir, kolon, '\x18', renk2);
	harf(satir+boy, kolon, '\x19', renk2);
	harf(satir+1, kolon, '\xfe', renk2);
}
/*
void yatay_cubuk(int satir, int kolon, int boy, int alan)
{
	// Kod Yazlacak
}*/

void ice_pen(int satir, int kolon, int boy, int en)
{
	int i;

	ince_cerceve(satir, kolon, boy, en, BEYAZ_ | A_BEYAZ);
	for (i = 0; i < boy; i++) {
		harf((satir+1)+i, kolon, '³', BEYAZ_ | SIYAH);
		doldur((satir+1)+i, kolon+1, ' ', en-1, BEYAZ_);
	}
	doldur(satir, kolon, 'Ä', en, BEYAZ_ | SIYAH);
	harf(satir, kolon, 'Ú', BEYAZ_ | SIYAH);
	harf((satir+boy)+1, kolon, 'À', BEYAZ_ | SIYAH);
}

void disa_pen(int satir, int kolon, int boy, int en)
{
	int i;

	ince_cerceve(satir, kolon, boy, en, BEYAZ_ | SIYAH);
	for (i = 0; i < boy; i++) {
		harf((satir+1)+i, kolon, '³', BEYAZ_ | A_BEYAZ);
		doldur((satir+1)+i, kolon+1, ' ', en-1, BEYAZ_);
	}
	doldur(satir, kolon, 'Ä', en, BEYAZ_ | A_BEYAZ);
	harf(satir, kolon, 'Ú', BEYAZ_ | A_BEYAZ);
	harf((satir+boy)+1, kolon, 'À', BEYAZ_ | A_BEYAZ);
}

char *basamakla(const char *adres)
{
	int i, k = 1, sayi, isaret = 0;
	char temp[80], *p, temp2[80];
	char ters[80];
	char tr[10];

	if (adres[0] == '-') {
		isaret = 1;
		strcpy(ters, &adres[1]);
		temp2[0] = '-';
	}
	else
		strcpy(ters, adres);

	memset(temp, 0, 80);
	strrev(ters);

	if ((p = strchr(ters, '.')) == NULL)
		p = ters;
	else
		++p;

	sayi = (p - ters) - isaret;

	for (i = 0, k = 1; k <= sayi ; i++, k++)
		tr[i] = p[-k];
	tr[i] = NULL;

	for (i = 0, k = 0; i < strlen(p); i++, k++) {
		temp[k] = p[i];
		if (i == 2 || i == 5 || i == 8) {
			if (p[i+1] != NULL) {
				k++; temp[k] = ',';
			}
			else
				k++;
		}
	}
	strrev(temp);
	strcpy(&temp2[isaret], temp);
	strcat(temp, tr);
	return temp2;
}

void harfler(int satir, int kolon, char *str, int renk)
{
	char far *scrp = vp;
	int k;

	scrp += satir * 160 + kolon * 2;
	for (k = 0; str[k] != '\0'; str++) {
		*scrp++ = str[k];
		*scrp++ = renk;
	}
}

void harf(int satir, int kolon, char karakter, int renk)
{
	char far *scrp = vp;
	int k;

	scrp += satir * 160 + kolon * 2;
	*scrp++ = karakter;
	*scrp = renk;
}

void doldur(int satir, int kolon, char karakter, int kac_tane, int renk)
{
	int k;
	char far *scrp = vp;

	scrp += satir * 160 + kolon * 2;
	for (k = 0; k < kac_tane; k++) {
		*scrp++ = karakter;
		*scrp++ = renk;
	}
}

void golgele(int satir, int kolon, int boy, int en, int renk)
{
	int i;

	for (i = 0; i < boy; i++)
		golge(satir + i, kolon, en, renk);
}
void golge(int kolon, int satir, int kac_tane, int renk)
{
	int k;
	char far *scrp = vp;

	scrp += kolon * 160 + satir * 2;
	for (k = 0; k < kac_tane; k++) {
		scrp++;
		*scrp++ = renk;
	}
}

void git_xy(int satir, int kolon)
{
	union REGS regs;

	regs.h.ah = 2;
	regs.h.bh = 0;
	regs.h.dh = satir;
	regs.h.dl = kolon;
	int86(0x10, &regs, &regs);
}

void ince_cerceve(int satir, int kolon, int menu_boyu, int menu_eni, int renk)
{
	int j;

	harf(satir, kolon, 'Ú',  renk);
	harf(satir, kolon + menu_eni, '¿', renk);
	harf(satir + menu_boyu + 1, kolon, 'À', renk);
	harf(satir + menu_boyu + 1, kolon + menu_eni, 'Ù', renk);

	for (j = 1; j != menu_eni; j++) {
		harf(satir , kolon + j, 'Ä', renk);
		harf(satir + menu_boyu + 1, kolon + j, 'Ä', renk);
	}
	for (j = 1; j != menu_boyu + 1; j++) {
		harf(satir + j, kolon, '³', renk);
		harf(satir + j, kolon + menu_eni, '³', renk);
	}
}

void kalin_cerceve(int satir, int kolon, int menu_boyu, int menu_eni, int renk)
{
	int j;

	harf(satir, kolon, 'É',  renk);
	harf(satir, kolon + menu_eni, '»', renk);
	harf(satir + menu_boyu + 1, kolon, 'È', renk);
	harf(satir + menu_boyu + 1, kolon + menu_eni, '¼', renk);

	for (j = 1; j != menu_eni; j++) {
		harf(satir , kolon + j, 'Í', renk);
		harf(satir + menu_boyu + 1, kolon + j, 'Í', renk);
	}
	for (j = 1; j != menu_boyu + 1; j++) {
		harf(satir + j, kolon, 'º', renk);
		harf(satir + j, kolon + menu_eni, 'º', renk);
	}
}

void kursor_uzunlugu(int minimum, int maksimum)
{
	union REGS regs;

	regs.h.ah = 1;
	regs.h.ch = minimum;
	regs.h.cl = maksimum;
	int86(0x10, &regs, &regs);
}

int msj_kutu(char *string, char *ref_hata, int HataTuru)
{
	int i = 5;
	char *p; /* bellek ayrmak i‡in */
	char data[5];
	MENU menu = { CYAN_ | SIYAH,
				  CYAN_ | SARI,
				  KAHVE_ | A_BEYAZ,
				  KAHVE_ | SARI,
				  BEYAZ_ | GRI,
				  SIYAH_ | GRI,
				  PASIF,
				  YATAY,
				  2,
				  0,
				  13,
				  39,
				  13,
				  55,
				  "+&Hayr+&Evet+",
				  "00",
				  "HE"
				  };

	memset(data, 0, 5);
	data[0] = '0';
	p = malloc(5 * 50 * 3);
	gettext(22, 10, 72, 15, p);
	kalin_cerceve(10, 22, 3, 48, CYAN_ | A_BEYAZ);
	for (i = 0; i < 3; i++)
		doldur(i+11, 23, ' ', 47, CYAN_);
	harfler(10, 24, " Mesaj Kutusu ", CYAN_ | A_BEYAZ);

	harfler(11, 28, ref_hata, CYAN_ | SIYAH);
	harfler(11, 28, string, CYAN_ | SIYAH);
	switch (HataTuru) {
		case HATA: harfler(11, 24, "(X)", CYAN_ | KIRMIZI);
				   cift_renk(13, 42, " &Tamam ", KAHVE_ | A_BEYAZ, KAHVE_ | SARI);
				   getch(); break;
		case UYARI: harfler(11, 24, "(!)", CYAN_ | SARI);
					cift_renk(13, 42, " &Tamam ", KAHVE_ | A_BEYAZ, KAHVE_ | SARI);
					getkb(); break;
		case SORU: harfler(11, 24, "(?)", CYAN_ | MAVI);
				   menu_cagir(&menu, data);
				   i = atoi(data);
	}
	puttext(22, 10, 72, 15, p);
	free(p);
	return i;
}

void cift_renk(int satir, int kolon, char *yazi, int renk1, int renk2)
{
	int i = 0, j = 0;

	while (yazi[i] != NULL) {
		if (yazi[i] == '&') {
			harf(satir, kolon + j, yazi[i+1], renk2);
			i+=2; j++;
		}
		else {
			harf(satir, kolon + j, yazi[i], renk1);
			i++; j++;
		}
	}
}

int dosya_kontrol(char *dosya_adi) /* yardmc fonksiyon : ekran_al ve ekran_ver */
{
	return (access(dosya_adi, 0) == 0);
}

char *dosya_vy(void) /* yardmc fonksiyon : ekran_al ve ekran_ver */
{
	int i = 0;
	char *yazi = "TempFile.000";
	char temp[5];

	while (dosya_kontrol(yazi)) {
		i++;
		sprintf(temp, "%03d", i);
		strncpy(&yazi[9], temp, 3);
	}
	return yazi;  /* Normal Ÿartlarda bu bir hatadr. Fakat stringler
		 global olarak sakland§ i‡in adresleri de§iŸmez...*/
}

char *ekran_al(int sat, int kol, int uz, int en, char *str)
{
	char k, i;
	FILE *fp;
	char far *scrp = vp;

	fp = fopen(str, "wb");

	scrp += sat * 160 + kol * 2;
	for (k = 0; k < uz; k++) {
		if (k > 0) {
			scrp = vp;
			scrp += (sat+k) * 160 + kol * 2;
		}

		for (i = 0; i < en; i++) {
			fputc(*scrp, fp); scrp++;
			fputc(*scrp, fp); scrp++;
		}
	}
	fclose(fp);
	return str;
}

void ekran_ver(int sat, int kol, int uz, int en, char *yazi)
{
	char k, i;
	FILE *fp;
	char far *scrp = vp;

	fp = fopen(yazi, "rb");

	scrp += sat * 160 + kol * 2;
	for (k = 0; k < uz; k++) {
		if (k > 0) {
			scrp = vp;
			scrp += (sat+k) * 160 + kol * 2;
		}

		for (i = 0; i < en; i++) {
			*scrp++ = fgetc(fp);
			*scrp++ = fgetc(fp);
		}
	}
	fclose(fp);
	unlink(yazi);
}

char formyarat(int satir, int kolon, int boy, int en, char *dosya_adi)
{
	char k, i;
	FILE *fp;
	char far *scrp = vp;

	fp = fopen(dosya_adi, "wb");

	scrp += satir * 160 + kolon * 2;
	for (k = 0; k < boy; k++) {
		if (k > 0) {
			scrp = vp;
			scrp += (satir+k) * 160 + kolon * 2;
		}
		for (i = 0; i < en; i++) {
			fputc(*scrp, fp); scrp++;
			fputc(*scrp, fp); scrp++;
		}
		fwrite("~~~~", 1, 4, fp); // Satr sonu oldu§unu g”sterir.
	}
	fseek(fp, -4, SEEK_CUR);
	fwrite("@~~@", 1, 4, fp);  // Formun sonu oldu§unu g”sterir.
	fclose(fp);
	return 0;
}

long filesize(FILE *stream)
{
   long curpos, length;

   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}

char *dosya_adi_ayir(char *yazi)
{
	int i = 0;
	char *dosya_adi = "             ";

	strrev(yazi);
	while ((yazi[i] != '/')) {
		dosya_adi[i] = yazi[i];
		i++;
	}
	dosya_adi[12] = NULL;
	strrev(yazi);
	return strrev(dosya_adi);
}

char formyukle(int satir, int kolon, char *dosya_adi)
{
	FILE *ds;
	char *fp;
	int i = 0;
	long dosya_uzunlugu = 0;
	char far *scrp = vp, temp[5];

	ds = fopen(dosya_adi, "rb");
	if (ds == NULL) {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}
	dosya_uzunlugu = filesize(ds);
	fp = (char *) malloc((int)dosya_uzunlugu+2);
	if (fp == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	fread(fp, 1, (int)dosya_uzunlugu, ds);

	scrp += satir * 160 + kolon * 2;
	for (i = 0;;i++) {
		switch (fp[i]) {
			case '~': strncpy(temp, &fp[i], 4); temp[4] = NULL;
					  if (!strcmp(temp, "~~~~")) {
						  i += 3;
						  satir++;
						  scrp = vp;
						  scrp += satir * 160 + kolon * 2;
					  }
					  else
						  *scrp++ = fp[i];
					  break;

			case '@': strncpy(temp, &fp[i], 4); temp[4] = NULL;
					  if (!strcmp(temp, "@~~@"))
						  kolon = 150;
					  else
						  *scrp++ = fp[i];
					  break;

			default : *scrp++ = fp[i];
					  break;
		}
		if (kolon == 150)
			goto SON;
	}
SON:
	fclose(ds);
	free(fp);
	return 0;
}

char formgolge(int satir, int kolon, char *dosya_adi)
{
	FILE *fp;
	char temp[5];
	int kolon_sayaci = kolon;

	fp = fopen(dosya_adi, "rb");
	if (fp == NULL) {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}

	for (;;) {
		switch (fgetc(fp)) {
			case '~': fseek(fp, -1, SEEK_CUR);
					  fread(temp, 1, 4, fp); temp[4] = NULL;
					  if (!strcmp(temp, "~~~~")) {
						  satir++; kolon_sayaci = kolon;
						  golge(satir+1, kolon_sayaci+2, 1, SIYAH_ | GRI);
					  }
					  else {
						  fseek(fp, -4, SEEK_CUR);
						  fgetc(fp); kolon_sayaci++;
						  golge(satir+1, kolon_sayaci+1, 1, SIYAH_ | GRI);
					  }
					  break;

			case '@': fseek(fp, -1, SEEK_CUR);
					  fread(temp, 1, 4, fp); temp[4] = '\0';
					  if (!strcmp(temp, "@~~@"))
						  kolon = 150;
					  else {
						  fseek(fp, -4, SEEK_CUR);
						  fgetc(fp); kolon_sayaci++;
						  golge(satir+1, kolon_sayaci+1, 1, SIYAH_ | GRI);
					  }
					  break;

			default : fseek(fp, -1, SEEK_CUR);
					  fread(temp, 1, 2, fp);
					  kolon_sayaci++;
					  golge(satir+1, kolon_sayaci+1, 1, SIYAH_ | GRI);
					  break;
		}
		if (kolon == 150)
			goto SON;
	}
SON:
	fclose(fp);
	return 0;
}