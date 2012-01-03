#include "/ozgan/programs/h/genel.h"
void menu_pen_ac(MENU *menu)
{
	 int i;

	 if (menu->Cerceve == AKTIF) {
		ince_cerceve(menu->BaslangicSatiri,
			menu->BaslangicKolonu,
			menu->BitisSatiri - menu->BaslangicSatiri,
			menu->BitisKolonu - menu->BaslangicKolonu + 1,
			menu->AktifNormal);
		menu->BaslangicSatiri++;
		menu->BitisKolonu++;
		menu->BitisSatiri++;
		menu->BaslangicKolonu++;
		for (i = 0; i < (menu->BitisSatiri - menu->BaslangicSatiri) + 2; i++) {
			harf(menu->BaslangicSatiri - 1 + i,
				menu->BaslangicKolonu - 2,
				' ',
				menu->AktifNormal);
			harf(menu->BaslangicSatiri - 1 + i,
				menu->BitisKolonu,
				' ',
				menu->AktifNormal);
		}
	}
	for (i = 0; i < (menu->BitisSatiri - menu->BaslangicSatiri); i++)
		doldur(menu->BaslangicSatiri + i,
			menu->BaslangicKolonu,
			' ',
			menu->BitisKolonu - menu->BaslangicKolonu-1,
			menu->AktifNormal);
}

void menu_pen_kapa(MENU *menu)
{
	 if (menu->Cerceve == AKTIF) {
		menu->BaslangicSatiri--;
		menu->BitisKolonu--;
		menu->BitisSatiri--;
		menu->BaslangicKolonu--;
	}
}

int yatay_menu_yeri(MENU *menu, int sayac)
{
	int i, yer_toplami = 0;
	char *gecici_dizi;

	gecici_dizi = malloc(MAKSIMUM_ALAN);
	if (gecici_dizi == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}

	for (i = 0; i < menu->MenuElemanSayisi; i++) {
		if (i == sayac) {
			free(gecici_dizi);
			return yer_toplami;
		}
		dizi_yapici(menu, i, gecici_dizi);
		yer_toplami += (strlen(gecici_dizi)-1);
	}
	free(gecici_dizi);
	return yer_toplami;
}

int yatay_menu(MENU *menu, char *data)
{
	int i, sayac = 0, ch2, k2;
	char *ch, *gecici_dizi;

	sayac = atoi(data);
	gecici_dizi = malloc(MAKSIMUM_ALAN);
	if (gecici_dizi == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
	}

	menu_pen_ac(menu);

	for (;;) {
		/* Bu kçsçm bir kez menuyu yazar */
		for (i = 0; i < menu->MenuElemanSayisi; i++)
			if (menu->MenuDurumDizisi[i] == '0')
				menu_yazar(menu, yatay_menu_yeri(menu, i), i, menu->AktifNormal,  menu->AktifNormalTus);
			else
				menu_yazar(menu, yatay_menu_yeri(menu, i), i, menu->PasifNormal,  menu->PasifNormal);

		/* Bu kçsçm ise ok tuülarçyla yapçlan hareketi gîsterir. */
		if (menu->MenuDurumDizisi[sayac] == '0')
			menu_yazar(menu, yatay_menu_yeri(menu, sayac), sayac, menu->AktifSecili,  menu->AktifSeciliTus);
		else
			menu_yazar(menu, yatay_menu_yeri(menu, sayac), sayac, menu->PasifSecili,  menu->PasifSecili);

		ch2 = islem();
		i = strchr(menu->VurguTuslari, toupper(ch2)) - menu->VurguTuslari;
		if (i >= 0 && i < menu->MenuElemanSayisi)
			sayac = i;

		switch (ch2) {
			case LEFT: sayac--; break;
			case RIGHT: sayac++; break;
			case ESC: free(gecici_dizi);
					  menu_pen_kapa(menu);
					  return ESC;
			case KP_ENTER:
			case ENTER: free(gecici_dizi);
						menu_pen_kapa(menu);
						itoa(sayac, data, 10);
						return ch2;
		}
		if (sayac >= menu->MenuElemanSayisi)
			sayac = 0;
		if (sayac <= -1)
			sayac = menu->MenuElemanSayisi - 1;
	}
}

void menu_yazar(MENU *menu, int yer_sayaci, int eleman_sayaci, int renk, int renktus)
{
	char *gecici_dizi;

	gecici_dizi = malloc(MAKSIMUM_ALAN);
	if (gecici_dizi == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
	}
	dizi_yapici(menu, eleman_sayaci, gecici_dizi);
	switch (menu->Menu) {
		case DIKEY:	cift_renk(menu->BaslangicSatiri + yer_sayaci,
						menu->BaslangicKolonu,
						gecici_dizi,
						renk,
						renktus); break;
		case YATAY: cift_renk(menu->BaslangicSatiri,
						menu->BaslangicKolonu + yer_sayaci + 1,
						gecici_dizi,
						renk,
						renktus); break;
		case KAPALI: cift_renk(menu->BaslangicSatiri + yer_sayaci,
						menu->BaslangicKolonu,
						gecici_dizi,
						renk,
						renktus); break;
	}
	free(gecici_dizi);
}

int kapali_menu_cerceve(MENU *menu, int sayac)
{
	char *gecici_dizi;

	gecici_dizi = malloc(MAKSIMUM_ALAN);
	if (gecici_dizi == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
	}

	dizi_yapici(menu, sayac, gecici_dizi);
	harfler(menu->BaslangicSatiri,
		menu->BaslangicKolonu-1,
		"[", menu->AktifNormal);

	cift_renk(menu->BaslangicSatiri,
		menu->BaslangicKolonu,
		gecici_dizi,
		menu->AktifSecili,
		menu->AktifSecili);

	ekran_x = menu->BaslangicSatiri;
	ekran_y = menu->BitisKolonu;
	git_xy(menu->BaslangicSatiri, menu->BitisKolonu);
	harfler(menu->BaslangicSatiri,
		menu->BitisKolonu,
		"\x1f]", menu->AktifNormal);
	return sayac;
}

int kapali_menu(MENU *menu, char *data)
{
	int ch;

	kapali_menu_cerceve(menu, atoi(data));
	for (;;) {
		ch = islem();
		if (uyarici != -1)
			ch = ENTER;
		switch (ch) {
			case KP_DOWN:
			case DOWN: kapali_menu_cerceve(menu, kapali_menu_hareket(menu, data));
			case KP_UP:
			case UP:
			case F7:
			case ESC:
			case KP_ENTER:
			case ENTER: goto CIK;
		}
	}
CIK:
	return ch;
}

int kapali_menu_hareket(MENU *menu, char *data)
{
	int i, sayac = 0, ch2, k = 0,
	Ilk = (menu->BitisSatiri - menu->BaslangicSatiri);
	char *ch;
	sayac = atoi(data);

		if (sayac >= Ilk) {
			k = (sayac - Ilk) + 1;
			sayac = Ilk-1;
		}

	for (;;) {
		/* Bu kçsçm bir kez menuyu yazar */
		for (i = 0; i < Ilk; i++)
			menu_yazar(menu, i, i+k, menu->AktifNormalTus, menu->AktifNormalTus);

		/* Bu kçsçm ise ok tuülarçyla yapçlan hareketi gîsterir. */
		menu_yazar(menu, sayac, sayac+k, menu->AktifSecili, menu->AktifSecili);

		ch2 = islem();
		if (uyarici != -1)
			ch2 = ENTER;

		i = strchr(menu->VurguTuslari, toupper(ch2)) - menu->VurguTuslari;
		if (i >= 0 && i < menu->MenuElemanSayisi)
			sayac = i;

		switch (ch2) {
			case UP: sayac--; break;
			case DOWN: sayac++; break;
			case LEFT: break;
			case RIGHT: break;
			case KP_ENTER:
			case ENTER: itoa(sayac + k, data, 10);
						return sayac + k;
		}

		if (sayac >= Ilk) {
			sayac = Ilk-1; k++;
			if (k >= menu->MenuElemanSayisi - Ilk + 1)
				k = menu->MenuElemanSayisi - Ilk;
		}
		if (sayac <= -1)  {
			sayac = 0;
			k--;
			if (k == -1)
				k = 0;
		}
	}
}

int dikey_menu(MENU *menu, char *data)
{
	int i, sayac = 0, ch2;
	char *ch;

	sayac = atoi(data);
	menu_pen_ac(menu);
	for (;;) {
// Bu kçsçm bir kez menuyu yazar
		for (i = 0; i < menu->MenuElemanSayisi; i++)
			if (menu->MenuDurumDizisi[i] == '0')
				menu_yazar(menu, i, i, menu->AktifNormal, menu->AktifNormalTus);
			else
				menu_yazar(menu, i, i, menu->PasifNormal, menu->PasifNormal);

// Bu kçsçm ise ok tuülarçyla yapçlan hareketi gîsterir.
		if (menu->MenuDurumDizisi[sayac] == '0')
			menu_yazar(menu, sayac, sayac, menu->AktifSecili, menu->AktifSeciliTus);
		else
			menu_yazar(menu, sayac, sayac, menu->PasifSecili, menu->PasifSecili);

		ch2 = islem();
		i = strchr(menu->VurguTuslari, toupper(ch2)) - menu->VurguTuslari;
		if (i >= 0 && i < menu->MenuElemanSayisi)
			sayac = i;

		switch (ch2) {
			case UP: sayac--; break;
			case DOWN: sayac++; break;
			case ESC: menu_pen_kapa(menu); return ESC;
			case LEFT:
			case RIGHT:
			case KP_ENTER:
			case ENTER:
				menu_pen_kapa(menu);
				itoa(sayac, data, 10);
				if (menu->MenuDurumDizisi[sayac] == '0')
					return ch2;
				break;
		}

		if (sayac >= menu->MenuElemanSayisi)
			sayac = 0;
		if (sayac <= -1)
			sayac = menu->MenuElemanSayisi - 1;
	}
}

char *dizi_yapici(MENU *menu, int sayac, char *aktarim)
{
	int GeciciDiziUzunlugu = (int) ((menu->BitisKolonu - menu->BaslangicKolonu) - 2);
	int BilgiDeposu, j;
	char *newadress, *oldadress;

	if (sayac >= menu->MenuElemanSayisi)
		return NULL;

	newadress = strchr(menu->MenuDizisi, '+') + 1;
	for (j = 0; j <= sayac; j++) {
		oldadress = newadress;
		newadress = strchr(newadress, '+') + 1;
	}
	BilgiDeposu = (int) (newadress - oldadress) - 1;
	switch (menu->Menu) {
		case YATAY: memset(aktarim, ' ', BilgiDeposu + 3);
					aktarim[BilgiDeposu+2] = NULL;
					break;
		case DIKEY: memset(aktarim, ' ', GeciciDiziUzunlugu+2);
					aktarim[GeciciDiziUzunlugu+2] = NULL;
					break;
		case KAPALI: memset(aktarim, ' ', GeciciDiziUzunlugu+3);
					 aktarim[GeciciDiziUzunlugu+2] = NULL;
					 break;
	}
	strncpy(&aktarim[1], oldadress, BilgiDeposu);
	return aktarim;
}

int menu_cagir(MENU *menu, char *data)
{
	int i = 0, SatirUzunlugu, KolonUzunlugu, BaslangicKolonu,
		BaslangicSatiri, BitisKolonu, BitisSatiri, EkranTutucu;

	SatirUzunlugu = menu->BitisSatiri - menu->BaslangicSatiri + 3;
	KolonUzunlugu = menu->BitisKolonu - menu->BaslangicKolonu + 3;

	BaslangicKolonu = menu->BaslangicKolonu;
	BaslangicSatiri	= menu->BaslangicSatiri + 2;
	BitisKolonu = menu->BitisKolonu;
	BitisSatiri	= menu->BitisSatiri;

	menu->EkranTutucu = (char *) malloc(SatirUzunlugu * 2 * KolonUzunlugu);
	if (menu->EkranTutucu == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}

	if (menu->Menu == DIKEY) {
		BaslangicSatiri -= 2;
		BitisSatiri += 2;
		BitisKolonu += 2;
	}

	gettext(BaslangicKolonu,
		BaslangicSatiri,
		BitisKolonu,
		BitisSatiri,
		menu->EkranTutucu);

	if (data[0] == 0)
		data[0] = '0';
	switch(menu->Menu) {
		case YATAY: i = yatay_menu(menu, data); break;
		case DIKEY: i = dikey_menu(menu, data); break;
		case KAPALI: i = kapali_menu(menu, data); break;
	}
	puttext(BaslangicKolonu,
		BaslangicSatiri,
		BitisKolonu,
		BitisSatiri,
		menu->EkranTutucu);

	free(menu->EkranTutucu);
	return i;
}

int menuyarat(char *dosya_adi, MENU *menu)
{
	FILE *fp;
	char ch;
	int sayac, islem;

	fp = dosya_kontrol(dosya_adi) ? fopen(dosya_adi, "rb+") : fopen(dosya_adi, "wb");
	if (fp == NULL) {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	fwrite("~~~~", 1, 4, fp); // Baülangçá òüareti
	fwrite(menu, 2, 14, fp);
	for (islem = 0, sayac = 0; sayac < (menu->MenuElemanSayisi + 1); islem++) {
		if ((ch = menu->MenuDizisi[islem]) == '+')
			sayac++;
		fputc(ch, fp);
	}
	for (sayac = 0; sayac < (menu->MenuElemanSayisi); sayac++) {
		ch = menu->MenuDurumDizisi[sayac];
		fputc(ch, fp);
	}
	for (sayac = 0; sayac < (menu->MenuElemanSayisi); sayac++) {
		ch = menu->VurguTuslari[sayac];
		fputc(ch, fp);
	}
	fclose(fp);
	return 0;
}

int menuyukle(char *dosya_adi, int n, MENU *menu)
{
	FILE *fp;
	char kilit[5];
	int islem, sayac;

	if ((fp = fopen(dosya_adi, "rb")) == NULL) {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}
	fseek(fp, 0, SEEK_SET);

	for (islem = 0; islem < n;) {
		if (getc(fp) == '~') {
			fseek(fp, -1, SEEK_CUR);
			fread(kilit, 1, 4, fp); kilit[4] = NULL;
			if (!strcmp(kilit, "~~~~"))
				islem++;
			else
				fseek(fp, -3, SEEK_CUR);
		}
	}

	fread(menu, 2, 14, fp);
	for (islem = 0, sayac = 0; sayac < (menu->MenuElemanSayisi + 1); islem++) {
		menu->MenuDizisi[islem] = fgetc(fp);
		menu->MenuDizisi[islem+1] = '\0';
		if (menu->MenuDizisi[islem] == '+')
				sayac++;
	}
	for (sayac = 0; sayac < (menu->MenuElemanSayisi); sayac++) {
		menu->MenuDurumDizisi[sayac] = fgetc(fp);
		menu->MenuDurumDizisi[sayac+1] = '\0';
	}
	for (sayac = 0; sayac < (menu->MenuElemanSayisi); sayac++) {
		menu->VurguTuslari[sayac] = fgetc(fp);
		menu->VurguTuslari[sayac+1] = '\0';
	}
	fclose(fp);
	return 0;
}

void mib_al(MENU *menu)      // menu icin bellek al
{
	menu->MenuDizisi = malloc(185);
	menu->MenuDurumDizisi = malloc(20);
	menu->VurguTuslari = malloc(20);
}

void mib_ver(MENU *menu)   // menu icin bellek ver
{
	free(menu->MenuDizisi);
	free(menu->MenuDurumDizisi);
	free(menu->VurguTuslari);
}


#if 0
void main(void)
{
	int i;

	char *data = "0";
	MENU menu; /*= { BEYAZ_ | SIYAH,
				  BEYAZ_ | SIYAH,
				  BEYAZ_ | A_BEYAZ,
				  YESIL_ | KIRMIZI,
				  BEYAZ_ | GRI,
				  SIYAH_ | GRI,
				  PASIF,
				  KAPALI,
				  5,
				  1000,
				  10,
				  12,
				  12,
				  23,
				  "+Lira+Dolar+Mark+Äek+Senet+",
				  "00000",
				  " "
				};
//	menuyarat("bin/menulist.mnu", &menu);//*/
	pencere.derecesi = ORTA_DUZEY;
	mib_al(&menu);
	menuyukle("bin/menulist.mnu", 16, &menu);
	menu_cagir(&menu, data);
	mib_ver(&menu);
}
#endif