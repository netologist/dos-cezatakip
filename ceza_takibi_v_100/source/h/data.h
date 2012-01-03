/* -------------------------------------------------------------------------
						  OzganSYS Software World (c)
					  Data Fonksiyonlarç KÅtÅphanesi v.1.00
								 21 Kasçm 2000
   ------------------------------------------------------------------------- */
#ifndef _DATA_H_
#define _DATA_H_
/* -------------------------------------------------------------------------
								  Global Deßiükenler
   ------------------------------------------------------------------------- */
extern int uyarici;
extern int insert_key; /* yazi_yaz ve sayi_yaz fonksiyonlari tarafçndan kullançlçr */

typedef struct ek_TABLOBILGI {
	int eleman_sayisi;
	int data_uzunlugu;
	int referans;
	int kontrol;
} TABLO_BILGI;

typedef struct ek_TABLOFORM {
	long tablo_adi;
	int hucre;
	int satir;
	int kolon;
	int uzunluk;
	int renk1;
	int renk2;
	long referans;
	int islem_sirasi;
} TABLO_FORM;
/* --------------------------------------------------------------------------
								Fonksiyon Prototipleri
   -------------------------------------------------------------------------- */
int format_yaz(char *string, char *format, char *tablo_ktr, int sat, int kol, int uzunluk, int renk1, int renk2);
int formatla(const char *kaynak, char *hedef, char *format);
int tarih_kontrol(char *string);
int artikyil(int yil);
int sayi_yaz(char *string, int sat, int kol, int uzunluk, int renk1, int renk2);
char *sifrele(char *string);
char *sifreac(char *string);
void tarih_al(char *tarih);
int getkb(void);
int islem(void);
int yazi_yaz(char *string, int sat, int kol, int uzunluk, int renk1, int renk2);
char kr_kontrol(int ch, char *krtr);
void ekle(char *string, int number, int ch);
void ara_sil(char *string, int number);
int cmptr(char ch1, char ch2);
int strcmptr(char *str1,  char *str2);
int uprtr(int ch);
char *struprtr(char *str);
int lwrtr(int ch);
char *strlwrtr(char *str);
void tablo_oynatici(int satir, int kolon, long tablo_adi, char *data ,TABLO_FORM *tablo, TABLO_BILGI *baslik);
void tablo_yerlestir(int satir, int kolon, long tablo_adi, char *data, TABLO_FORM *tablo, TABLO_BILGI *baslik);
void tabloyarat(char *dosya_adi, TABLO_BILGI *baslik, TABLO_FORM *tablo);
TABLO_FORM *tabloyukle(char *dosya_adi, TABLO_BILGI *baslik);
int indeks_bilgisi(TABLO_FORM *tablo, TABLO_BILGI *baslik, int kontrol);
TABLO_FORM *tabloyukle(char *dosya_adi, TABLO_BILGI *baslik);
/* -------------------------------------------------------------------------
								 Sabit Tançmlamalarç
   ------------------------------------------------------------------------- */
#define SAYI			0 // **********************************************
#define YAZI			1 //
#define FORMAT			2 //    H U C R E
#define KAPALI_MENU		3 //
#define KARE_KUTU		4 // 					 T U R U
#define YUVARLAK_KUTU	5 //
#define TARIH			6 // **********************************************

#define YOK		0 // *****************************************
#define ONCE	1 //        ò û L E M    S I R A S I
#define SONRA	2 // *****************************************

#define INDEKS_AC	0
#define INDEKS_KAPA	1

/* -------------------------------------------------------------------------
								  Baülçk Dosyasç Sonu
   ------------------------------------------------------------------------- */
#endif