/* -------------------------------------------------------------------------
						  OzganSYS Software World (c)
					  Data Fonksiyonlarç KÅtÅphanesi v.1.00
								 21 Kasçm 2000
   ------------------------------------------------------------------------- */
#ifndef _MENU_H_
#define _MENU_H_

/* -------------------------------------------------------------------------
								  Global Deßiükenler
   ------------------------------------------------------------------------- */
typedef int DURUM;
typedef int RENK;

typedef struct ekMENU {
	RENK AktifNormal;
	RENK AktifNormalTus;
	RENK AktifSecili;
	RENK AktifSeciliTus;
	RENK PasifNormal;
	RENK PasifSecili;
	DURUM Cerceve;
	DURUM Menu;
	int MenuElemanSayisi;
	int MenuBasvuruNo;
	int BaslangicSatiri;
	int BaslangicKolonu;
	int BitisSatiri;
	int BitisKolonu;
	char *MenuDizisi;
	char *MenuDurumDizisi;
	char *VurguTuslari;
	char *EkranTutucu;
} MENU;
/* --------------------------------------------------------------------------
								Fonksiyon Prototipleri
   -------------------------------------------------------------------------- */
void menu_pen_ac(MENU *menu);
void menu_pen_kapa(MENU *menu);
int yatay_menu_yeri(MENU *menu, int sayac);
int yatay_menu(MENU *menu, char *data);
void menu_yazar(MENU *menu, int yer_sayaci, int eleman_sayaci, int renk, int renktus);
int kapali_menu_cerceve(MENU *menu, int sayac);
int kapali_menu(MENU *menu, char *data);
int kapali_menu_hareket(MENU *menu, char *data);
int dikey_menu(MENU *menu, char *data);
char *dizi_yapici(MENU *menu, int sayac, char *aktarim);
int menu_cagir(MENU *menu, char *data);
void mib_al(MENU *menu);
void mib_ver(MENU *menu);
int menuyukle(char *dosya_adi, int n, MENU *menu);
int menuyarat(char *dosya_adi, MENU *menu);

/* -------------------------------------------------------------------------
								 Sabit Tançmlamalarç
   ------------------------------------------------------------------------- */
#define AKTIF 	0
#define PASIF	1

#define YATAY 	0
#define DIKEY	1
#define KAPALI	2

#define MAKSIMUM_ALAN	80

/* -------------------------------------------------------------------------
								  Baülçk Dosyasç Sonu
   ------------------------------------------------------------------------- */
#endif