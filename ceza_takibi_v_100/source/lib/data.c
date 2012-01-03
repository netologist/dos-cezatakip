#include "/ozgan/programs/h/genel.h"
int uyarici; // tablo ve yazma fonksiyonlarçna bir uyarç gînderir
			  // uyari_gonder(10); fonksiyonu bu iü iáin gîrevlidir.
int insert_key = 0; /* yazi_yaz ve sayi_yaz fonksiyonlari tarafçndan kullançlçr */

void uyari_gonder(int uyari)
{ // uyarçcç tabloda herhangi bir hÅcreye yînelmenizi saßlar
	uyarici = uyari;
}

void tarih_al(char *tarih)
{
	char depo[5];
	struct tm *p;
	long yeni_tarih;

	yeni_tarih = time(NULL);
	p = localtime(&yeni_tarih);
	sprintf(tarih, "%02d%02d%04d", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
}

int artikyil(int yil)
{
	if (!(yil % 400) || (!(yil % 4) && (yil % 100)))
		return 1;
	return 0;
}

int tarih_kontrol(char *string)
{
	int yil, ay, gun, artikyil_isaretcisi,
	son_gun[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char gecici[5];


	memset(gecici, 0, 10);
	yil = atoi(&string[4]); // YIL bulunur

	if (yil >= 1980 && yil <= 2012) {
		if (!(artikyil(yil) == NULL))
			artikyil_isaretcisi = 1;
		else
			artikyil_isaretcisi = 0;
	}
	else
		goto HATA_SON;

	strncpy(gecici, &string[2], 2);
	ay = atoi(gecici);

	if (ay > 0 && ay <= 12)
		son_gun[1] += artikyil_isaretcisi;
	else
		goto HATA_SON;

	strncpy(gecici, &string[0], 2);
	gun = atoi(gecici);

	if (!(gun > 0 && gun <= son_gun[ay - 1]))
		goto HATA_SON;

	return 1; // Problem Yok tarih doßru
HATA_SON:
	return 0; // Tarih hatalç
}

char *sifrele(char *string)
{
	int i;
	for (i = 0; i < strlen(string); i++)
		string[i] += 12;
	return string;
}

char *sifreac(char *string)
{
	int i;
	for (i = 0; i < strlen(string); i++)
		string[i] -= 12;
	return string;
}

int getkb(void)
{
	union REGS regs;

	regs.h.ah = 0x10;
	int86(0x16, &regs, &regs);
	return regs.x.ax;
}

int yazi_yaz(char *string, int sat, int kol, int uzunluk, int renk1, int renk2)
{
	int sayac = strlen(string), ch = 0;

	doldur(sat, kol, ' ', uzunluk, renk1);
	harfler(sat, kol, string, renk1);
	git_xy(sat, kol + sayac);

	for (;;) {
		ekran_x = sat; // Koordinat herkesin eriüimine aáçlçyor.
		ekran_y = kol + sayac; // Koordinat herkesin eriüimine aáçlçyor.
		ch = islem();
		if (uyarici != -1)
			ch = ENTER;

		switch (ch) {
			case KP_LEFT :
			case LEFT : sayac--;
						if (sayac < 0)
							sayac = 0;
						string[uzunluk] = NULL; goto YAZDIR;

			case KP_RIGHT :
			case RIGHT : sayac++;
						 if (sayac >= uzunluk)
							sayac = uzunluk; goto YAZDIR;

			case BACKSPACE :
				if (sayac == 0) {
					sayac--;
					string[sayac] = ' ';
					sayac = 0;
				}
				else {
					 sayac--;
					 ara_sil(string, sayac+1);
				}
				goto YAZDIR;

			case KP_DEL :
			case DEL : ara_sil(string, sayac+1); goto YAZDIR;

			case KP_INS :
			case INS :
				if (insert_key == 0) {
					kursor_uzunlugu(3, 10);
					insert_key = 1;
				}
				else {
					kursor_uzunlugu(9, 10);
					insert_key = 0;
				}
				goto YAZDIR;

			case KP_HOME :
			case HOME : sayac = 0; goto YAZDIR;

			case KP_END :
			case END : sayac = strlen(string); goto YAZDIR;

			case CTRL_KP_DEL:
			case CTRL_DEL:
					memset(string, 0, uzunluk+1);
					sayac = 0; goto YAZDIR;

			case TAB:
			case F7:
			case ESC:
			case SHIFT_TAB:
			case DOWN:
			case KP_DOWN:
			case UP:
			case KP_UP:
			case KP_ENTER :
			case ENTER : harfler(sat, kol, string, renk2); goto CIK;
		}
		if (kr_kontrol(ch, YAZI_KRTR) == NULL)
			continue;
		switch (insert_key) {
			case 0: string[sayac] = (char) ch; break;
			case 1: ekle(string, sayac, ch); break;
		}
		if (sayac >= uzunluk)
			sayac = uzunluk;
		else
			sayac++;
YAZDIR:
		string[uzunluk] = NULL;
		doldur(sat, kol, ' ', uzunluk, renk1);
		harfler(sat, kol, string, renk1);
		git_xy(sat, kol + sayac);
	}
CIK:
	string[uzunluk] = NULL;
	return ch;
}

int formatla(const char *kaynak, char *hedef, char *format)
{
	int genel_sayac = 0 , ozel_sayac = 0;

	while (format[genel_sayac] != NULL) {
		if (format[genel_sayac] == '#') {
			hedef[genel_sayac] = kaynak[ozel_sayac];
			ozel_sayac++;
		}
		else
			hedef[genel_sayac] = format[genel_sayac];
		++genel_sayac;
	}
	hedef[genel_sayac] = NULL;
	return ozel_sayac;
}

int format_yaz(char *string, char *format, char *tablo_ktr, int sat, int kol, int uzunluk, int renk1, int renk2)
{
	int sayac = 0, ch = 0, cursor = 0, sayac_uzunlugu;
	char gecici[80];

	sayac_uzunlugu = formatla(string, gecici, format);
	harfler(sat, kol, gecici, renk1);
	git_xy(sat, kol + cursor);
	for (;;) {
		ekran_x = sat; // Koordinat herkesin eriüimine aáçlçyor.
		ekran_y = kol + cursor; // Koordinat herkesin eriüimine aáçlçyor.
		ch = islem();
		if (uyarici != -1)
			ch = ENTER;

		switch (ch) {
			case KP_HOME :
			case HOME : sayac = 0; cursor = 0; goto YAZDIR;

			case KP_END :
			case END : sayac = sayac_uzunlugu; cursor = uzunluk; goto YAZDIR;

			case BACKSPACE : sayac--; cursor--;
							 string[sayac] = ' ';
							 if (sayac < 0) {
								 sayac = 0; cursor = 0;
							 }
							 if (format[sayac] != '#')
								cursor--;
							 goto YAZDIR;

			case CTRL_KP_DEL:
			case CTRL_DEL:
					memset(string, 0x20, sayac_uzunlugu);
					sayac = 0; cursor = 0; goto YAZDIR;
			case TAB:
			case F7:
			case ESC:
			case SHIFT_TAB:
			case DOWN:
			case KP_DOWN:
			case UP:
			case KP_UP:
			case KP_ENTER :
			case ENTER : goto CIK;
		}

		if (kr_kontrol(ch, tablo_ktr) == NULL)
			continue;
		else
			string[sayac] = (char) ch;

		if (cursor >= uzunluk)
			cursor = uzunluk;
		else {
			sayac++;
			cursor++;
			if (format[sayac] != '#')
				cursor++;
		}

YAZDIR:
		git_xy(sat, kol + cursor);
		sayac_uzunlugu =  formatla(string, gecici, format);
		harfler(sat, kol, gecici, renk1);
	}
CIK:
	formatla(string, gecici, format);
	harfler(sat, kol, gecici, renk2);
	string[sayac_uzunlugu] = '\0';
	return ch;
}

int sayi_yaz(char *string, int sat, int kol, int uzunluk, int renk1, int renk2)
{
	int sayac = strlen(string), ch = 0, data_siniri, gecici, kayan_nokta = 0;

	doldur(sat, kol, ' ', uzunluk, renk1);
	gecici = uzunluk - strlen(basamakla(string));
	harfler(sat, kol+gecici, basamakla(string), renk1);
	git_xy(sat, kol + uzunluk);
	data_siniri = uzunluk - (uzunluk / 4) - 1;

	for (;;) {
		ekran_x = sat; // Koordinat herkesin eriüimine aáçlçyor.
		ekran_y = kol + uzunluk; // Koordinat herkesin eriüimine aáçlçyor.
		ch = islem();
		if (uyarici != -1)
			ch = ENTER;

		switch (ch) {
			case BACKSPACE :
				if (sayac == 0) {
					string[sayac] = ' ';
					sayac = 0;
				}
				else {
					 sayac--;
					 if (string[sayac] == '.')
						kayan_nokta = 0;
					 string[sayac] = '\0';
				}
				goto YAZDIR;

			case TAB:
			case F7: // cikis
			case ESC:
			case SHIFT_TAB:
			case DOWN:
			case KP_DOWN:
			case UP:
			case KP_UP:
			case KP_ENTER :
			case ENTER : gecici = uzunluk - strlen(basamakla(string));
						 harfler(sat, kol+gecici, basamakla(string), renk2); goto CIK;

			case CTRL_KP_DEL:
			case CTRL_DEL:
					memset(string, 0, uzunluk+1);
					sayac = 0; goto YAZDIR;

			case 0x352e :
			case 0x532c : if (kayan_nokta == 0)
							  if (sayac < data_siniri) {
								  if (sayac == 0) {
									  string[sayac] = '0';
									  sayac++;
								  }
								  string[sayac] = '.';
								  sayac++;
								  kayan_nokta = 1;
							  }

						  goto YAZDIR;
		}
		if (kr_kontrol(ch, SAYI_KRTR) == NULL)
			continue;
		if (sayac > data_siniri)
			continue;
		else {
			string[sayac] = (char) ch;
			sayac++;
		}
		if (string[0] == '0')
			sayac--;
YAZDIR:
		string[uzunluk] = NULL;
		doldur(sat, kol, ' ', uzunluk, renk1);
		gecici = uzunluk - strlen(basamakla(string));
		harfler(sat, kol + gecici, basamakla(string), renk1);
		git_xy(sat, kol + uzunluk);
	}
CIK:
	string[uzunluk] = NULL;
	return ch;
}

int kare_kutu(int satir, int kolon, char *string, TABLO_FORM *tablo, int sayac)
{
	int ch, isaret = 0;

	if (string[0] == 1) {
		isaret = 1;
		harf(tablo[sayac].satir+satir, tablo[sayac].kolon+kolon, 'X', tablo[sayac].renk1);
	}
	else if (string[0] == 0) {
		isaret = 0;
		harf(tablo[sayac].satir+satir, tablo[sayac].kolon+kolon, ' ', tablo[sayac].renk1);
	}
	git_xy(tablo[sayac].satir+satir, tablo[sayac].kolon+kolon);
	for (;;) {
		ch = islem();
		switch (ch) {
			case SPACE : if (isaret == 0) {
							 isaret = 1;
							 harf(tablo[sayac].satir+satir, tablo[sayac].kolon+kolon, 'X', tablo[sayac].renk1);
						 }
						 else {
							 isaret = 0;
							 harf(tablo[sayac].satir+satir, tablo[sayac].kolon+kolon, ' ', tablo[sayac].renk1);
						 } break;
			default: string[0] = isaret;
					 return ch;
		}
	}
}

int yuvarlak_kutu(int satir, int kolon, char *string, TABLO_FORM *tablo, int sayici)
{
	int sayac = 0, ch, i;

	sayac = (int) string[0];
	for (i = 0; i < tablo[sayici].uzunluk; i++)
		harf(tablo[sayici].satir+i+satir, tablo[sayici].kolon+kolon, ' ', tablo[sayici].renk1);
	harf(tablo[sayici].satir+sayac+satir, tablo[sayici].kolon+kolon, '\x07', tablo[sayici].renk1);
	git_xy(tablo[sayici].satir+sayac+satir, tablo[sayici].kolon+kolon);

	for (;;) {
		ch = islem();
		harf(tablo[sayici].satir+sayac+satir, tablo[sayici].kolon+kolon, ' ', tablo[sayici].renk1);
		switch (ch) {
			case UP: sayac--; break;
			case DOWN: sayac++; break;
			default: harf(tablo[sayici].satir+sayac+satir, tablo[sayici].kolon+kolon, '\x07', tablo[sayici].renk1);
					 string[0] = (char) sayac;
					 return ch;
		}

		if (sayac < 0)
			sayac = 0;

		if (sayac > tablo[sayici].uzunluk-1)
			sayac = tablo[sayici].uzunluk-1;
		harf(tablo[sayici].satir+sayac+satir, tablo[sayici].kolon+kolon, '\x07', tablo[sayici].renk1);
		git_xy(tablo[sayici].satir+sayac+satir, tablo[sayici].kolon+kolon);
	}
}

char kr_kontrol(int ch, char *krtr)
{
	if (strchr(krtr, (char) ch) == NULL)
		return NULL;
	else
		return (char) ch;
}
void ekle(char *string, int number, int ch)
{
	int lenght, i;
	char temp[80];

	lenght = strlen(string);
	strcpy(temp, &string[number]);

	string[number] = (char) ch; number++;
	for (i = 0; number <= lenght; ++number, i++)
		string[number] = temp[i];
}

void ara_sil(char *string, int number)
{
	int i, lenght;
	char temp[80];

	memset(temp, 0x20, 80);
	lenght = strlen(string);
	strcpy(temp, &string[number]);

	for (i = 0; number <= lenght; number++, i++)
		string[number-1] = temp[i];
	lenght = strlen(string);
	string[lenght] = NULL;

	for (i = 0; i < lenght; i++)
		if (string[i] == NULL)
			string[i] = 0x20;
}

int cmptr(char ch1, char ch2)
{
	char alfabe[42] = "0123456789abcádefgßhçijklmnoîpqrsütuÅvwxyz";

	return strchr(alfabe, ch1) - strchr(alfabe, ch2);
//    eüitse 0'a ch1 bÅyÅkse pozitife ch1 kÅáÅkse negatife dîner.
}

int strcmptr(char *str1,  char *str2)
{
	int i = 0, sonuc = 0;
	char gecici1[80], gecici2[80];

	strcpy(gecici1, str1);
	strcpy(gecici2, str2);
	while (gecici1[i] != '\0' || gecici2[i] != '\0') {
		sonuc = cmptr(gecici1[i], gecici2[i]);
		if (sonuc)
			goto CIK;
		i++;
	}
CIK:
	return sonuc;
}

int uprtr(int ch)
{
	char *temp;

	char *dizi[2] = {"îáüißÅç", "ôÄûò¶öI"};

	temp = strchr(dizi[0], ch);
	if (temp != NULL)
		return temp[8];
	else
		return toupper(ch);
}

char *struprtr(char *str)
{
	int i = 0;

	while (str[i] != NULL) {
		str[i] = uprtr(str[i]);
		i++;
	}
	return str;
}

int lwrtr(int ch)
{
	char *temp;

	char *dizi[2] = {"ôÄûò¶öI", "îáüißÅç"};

	temp = strchr(dizi[0], ch);
	if (temp != NULL)
		return temp[8];
	else
		return tolower(ch);
}

char *strlwrtr(char *str)
{
	int i = 0;

	while (str[i] != NULL) {
		str[i] = lwrtr(str[i]);
		i++;
	}
	return str;
}

void tabloyarat(char *dosya_adi, TABLO_BILGI *baslik, TABLO_FORM *tablo)
{
	int i;
	FILE *fp;

	if ( (fp = fopen(dosya_adi, "wb+")) == NULL) {
		msj_kutu(NULL, HATA_DISKE_YAZILAMIYOR, HATA);
		exit(1);
	}
	fseek(fp, 0, SEEK_SET);
	fwrite(baslik, 1, sizeof(TABLO_BILGI), fp);
	for (i = 0; i < baslik->eleman_sayisi; i++)
		fwrite(&tablo[i], 1, sizeof(TABLO_FORM), fp);
	fclose(fp);
}

TABLO_FORM *tabloyukle(char *dosya_adi, TABLO_BILGI *baslik)
{
	int i;
	FILE *fp;
	TABLO_FORM *tablo_dak;

	if ( (fp = fopen(dosya_adi, "rb")) == NULL) {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}

	fseek(fp, 0, SEEK_SET);

	fread(baslik, 1, sizeof(TABLO_BILGI), fp);

	tablo_dak = (TABLO_FORM *) malloc( sizeof(TABLO_FORM) * baslik->eleman_sayisi );
	if (tablo_dak == '\0') {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}
	memset(tablo_dak, 0,( sizeof(TABLO_FORM) * baslik->eleman_sayisi ));
	for (i = 0; i < baslik->eleman_sayisi; i++)
		fread(&tablo_dak[i], 1, sizeof(TABLO_FORM), fp);
	fclose(fp);
	return tablo_dak;
}

void tablo_yerlestir(int satir, int kolon, long tablo_adi, char *data, TABLO_FORM *tablo, TABLO_BILGI *baslik)
{
	int i, data_yeri = 0, kolon_yeri = 0;
	char gecici_data[80];

	memset(gecici_data, 0, 80);
	for (i = 0; i < baslik->eleman_sayisi; i++) {
		if (tablo[i].tablo_adi == tablo_adi) {
			switch(tablo[i].hucre) {
				case YAZI:  doldur(satir+tablo[i].satir,
								kolon+tablo[i].kolon,
								' ', tablo[i].uzunluk,
								tablo[i].renk1);
							harfler(satir+tablo[i].satir,
								kolon+tablo[i].kolon,
								&data[data_yeri],
								tablo[i].renk2); break;
				case SAYI: kolon_yeri = tablo[i].uzunluk - strlen(basamakla(&data[data_yeri]));
						   doldur(satir+tablo[i].satir,
								kolon+tablo[i].kolon,
								' ', tablo[i].uzunluk,
								tablo[i].renk1);
						   harfler(satir+tablo[i].satir,
								kolon+tablo[i].kolon + kolon_yeri,
								basamakla(&data[data_yeri]),
								tablo[i].renk2); break;
				case YUVARLAK_KUTU:
					harf(satir+tablo[i].satir+data[data_yeri],
						kolon+tablo[i].kolon + kolon_yeri,
						'\x07',
						tablo[i].renk2); break;
				case KARE_KUTU:
					if (data[data_yeri] == 1)
						harf(satir+tablo[i].satir,
							kolon+tablo[i].kolon,
							'X',
							tablo[i].renk2);
					else
						harf(satir+tablo[i].satir,
							kolon+tablo[i].kolon,
							' ',
							tablo[i].renk2);
					break;
				case KAPALI_MENU:
					menu_sec(&data[data_yeri], tablo[i].satir+satir,
						tablo[i].kolon+kolon,
						tablo[i].uzunluk,
						tablo[i].referans,
						gecici_data);
					break;
				case TARIH:
						doldur(tablo[i].satir+satir,
							tablo[i].kolon+kolon,
							' ', tablo[i].uzunluk,
							tablo[i].renk2);
						if (strlen(&data[data_yeri]) == 0)
							tarih_al(&data[data_yeri]);
						formatla(&data[data_yeri], gecici_data, "##/##/####");
						harfler(tablo[i].satir+satir,
							tablo[i].kolon+kolon,
							gecici_data,
							tablo[i].renk2);
					break;
			}
		}
		data_yeri += tablo[i].uzunluk + 1;
	}
}

int indeks_bilgisi(TABLO_FORM *tablo, TABLO_BILGI *baslik, int kontrol)
{
	int sayac = 0;

	for (sayac = 0; sayac < baslik->eleman_sayisi; sayac++) {
		if (tablo[sayac].referans == Data_Indeks_Bilgisi) {
			if (kontrol == INDEKS_KAPA)
				tablo[sayac].islem_sirasi = YOK;
			else if (kontrol == INDEKS_AC)
				tablo[sayac].islem_sirasi = SONRA;
			return 1;
		}
	}
	return 0; // Bîyle bir bilgi yok.....
}

void tablo_oynatici(int satir, int kolon, long tablo_adi, char *data, TABLO_FORM *tablo, TABLO_BILGI *baslik)
{
	int sayac = 0, ch, depo_ch,
		data_yeri = 0,
		i, eleman_sayisi = 0, gereksiz_eleman = 0;

	uyarici = -1; // uyarici sçfçrlandç...

	for (i = 0; i < baslik->eleman_sayisi; i++) {
		if (tablo[i].tablo_adi == tablo_adi)
			eleman_sayisi++;
		else if (eleman_sayisi == 0)
			gereksiz_eleman++;
		else
			goto SON;
	}
SON:
	sayac = gereksiz_eleman;
	for (data_yeri = 0, i = 0; i <= sayac-1; i++)
		data_yeri += tablo[i].uzunluk + 1;

	tablo_yerlestir(satir, kolon, tablo_adi, data, tablo, baslik);
	for (;;) {
		if (tablo[sayac].islem_sirasi != YOK && tablo[sayac].tablo_adi == tablo_adi) {
			switch (tablo[sayac].hucre) {
				case YAZI:
					ch = yazi_yaz(&data[data_yeri], satir+tablo[sayac].satir, kolon+tablo[sayac].kolon, tablo[sayac].uzunluk, tablo[sayac].renk1, tablo[sayac].renk2);				break;
				case SAYI:
					ch = sayi_yaz(&data[data_yeri], satir+tablo[sayac].satir, kolon+tablo[sayac].kolon, tablo[sayac].uzunluk, tablo[sayac].renk1, tablo[sayac].renk2);
					break;
				case YUVARLAK_KUTU:
					ch = yuvarlak_kutu(satir, kolon, &data[data_yeri], tablo, sayac);
					break;
				case KARE_KUTU:
					ch = kare_kutu(satir, kolon, &data[data_yeri], tablo, sayac);
					break;
				case KAPALI_MENU: ch = menu_sec(&data[data_yeri], tablo[sayac].satir+satir,
									  tablo[sayac].kolon+kolon,
									  tablo[sayac].uzunluk,
									  tablo[sayac].referans,
									  NULL);
								   switch (ch) {
									  case DOWN:
									  case KP_DOWN:
									  case ENTER:
									  case KP_ENTER:
										  kmenu_islem(&data[data_yeri], tablo, baslik, sayac);
								   }
								   break;
				case TARIH:
					TEKRAR_YAP:
					harfler(satir+tablo[sayac].satir, kolon+tablo[sayac].kolon, "  /  /", tablo[sayac].renk1);
					if (strlen(&data[data_yeri]) == 0)
						tarih_al(&data[data_yeri]);
					ch = format_yaz(&data[data_yeri], "##/##/####", SAYI_KRTR, satir+tablo[sayac].satir, kolon+tablo[sayac].kolon, tablo[sayac].uzunluk, tablo[sayac].renk1, tablo[sayac].renk2);
					if (tarih_kontrol(&data[data_yeri]) == 0)
						goto TEKRAR_YAP;
			}
		}

		if (uyarici != -1) {
			sayac = uyarici; // uyarçlan deßer
			uyarici = -1;
			ch = '\0';
			for (data_yeri = 0, i = 0; i <= sayac-1; i++)
				data_yeri += tablo[i].uzunluk + 1;
		}
		switch (ch) {
			case F7:
			case ESC: goto CIK;
			case KP_ENTER:
			case ENTER:
			case KP_DOWN:
			case DOWN:
			case TAB: sayac++;
					  if (tablo[sayac].tablo_adi != tablo_adi)
						  sayac = gereksiz_eleman;
					  for (data_yeri = 0, i = 0; i <= sayac-1; i++)
						  data_yeri += tablo[i].uzunluk + 1;
					  break;
			case KP_UP:
			case UP:
			case SHIFT_TAB:	sayac--;
							if (tablo[sayac].tablo_adi != tablo_adi)
								sayac = gereksiz_eleman + eleman_sayisi - 1;
							if (tablo[sayac].islem_sirasi == YOK)
								sayac--;
							for (data_yeri = 0, i = 0; i <= sayac-1; i++)
								data_yeri += tablo[i].uzunluk + 1;
							break;
		}
	}
CIK:
}