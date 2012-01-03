#ifndef _CEZA_H_
#define _CEZA_H_

#include "/ozgan/programs/h/genel.h"

void menu(void);
int sifre_kontrol(void);
void sifre_dosyasi_yap(void);
char *sifre_getir(char *Parola, char *Karsi_Deger);
void program_kayit(void);
void hesap_form(void);
void hesap_liste(void);
void referans_yap(void);
void hos_geldiniz(void);
void f2_tusu(int referans);
void yeni_form(void);
void f3_tusu(int referans);
void f4_tusu(int referans);
void f5_tusu(int referans);
void tablo_form(void);
void hesap_tablo_form(int satir, int kolon);

typedef struct _YENI_DATA {
	char Ay[10];
	char Yil[5];
	char Oran[4];
	char Referans[11];
	char Oran_Tutucu[11];
} YENI_DATA;

typedef struct _YENI_INDEKS {
	char Referans[11];
	char Oran_Tutucu[11];
} YENI_INDEKS;

typedef struct _HESAP_DATA {
	char Ay[10];
	char Yil[5];
	char Referans[11];
	char Ana_Para[16];
	char Oran[20];
	char Faiz_Tutari[20];
	char Borc_Toplami[20];
} HESAP_DATA;

typedef struct _TABLO_DATA {
	char Unvan[31];
	char VD[15];
	char VN[13];
	char Binde_Oran[7];
	char Taksit[4];
	char Toplam_Hesap[16];
	char Aylik_Hesap[16];
	char Ana_Para_Toplam[16];
	char Faiz_Toplam[16];
	char Genel_Toplam[16];
} TABLO_DATA;

typedef struct _HESAP_TABLO_DATA {
	char Tarih[13];
	char Oran[7];
	char Ana_Para[16];
	char Faiz_Tutari[16];
	char Toplam_Borc[16];
} HESAP_TABLO_DATA;

extern HESAP_TABLO_DATA hesap_tablo_data;
extern TABLO_DATA *tablo_data;

extern HESAP_DATA *hesap_data;
extern long kayit_adresi;
extern char *dataci;
extern TABLO_BILGI baslik;
extern TABLO_FORM *tablo;
extern YENI_DATA *yeni_data;
extern YENI_INDEKS *yeni_indeks;

#define Data_Yeni			500
#define Data_Hesap			600
#define Data_Rapor			700
#define Data_Rapor_Tablo	701
#define Data_Rapor_Sabit	702
#define Data_Rapor_Degisken	703

#define YMenu_ANA_MENU		1
#define KMenu_CEZA_AYLARI	2

#define Form_YENI	10
#define Form_HESAP	20
#define Form_RAPOR	30


#endif
