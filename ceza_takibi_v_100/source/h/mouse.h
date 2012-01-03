/* -------------------------------------------------------------------------
						  OzganSYS Software World (c)
					 Ekran Fonksiyonlarç KÅtÅphanesi v.1.00
								 21 Kasçm 2000
   ------------------------------------------------------------------------- */
#ifndef _MOUSE_H_
#define _MOUSE_H_

/* -------------------------------------------------------------------------
								  Global Deßiükenler
   ------------------------------------------------------------------------- */
typedef struct tagKONUM {
	int baslangic_satiri;
	int baslangic_kolonu;
	int son_satiri;
	int son_kolonu;
} KONUM;

/* --------------------------------------------------------------------------
								Fonksiyon Prototipleri
   -------------------------------------------------------------------------- */
void cursor_off(void);
void cursor_on(void);
int rightb_pressed(void);
int leftb_pressed(void);
void set_mouse_position(int x, int y);
void mouse_position(int *x, int *y);
void mouse_motion(char *deltax, char *deltay);
void wait_on(int button);
int kontrol(KONUM *konum, int uzunluk, int satir, int kolon);

/* -------------------------------------------------------------------------
								 Sabit Tançmlamalarç
   ------------------------------------------------------------------------- */
#define NOT_MOVED	0
#define M_RIGHT		1
#define M_LEFT		2
#define M_UP		3
#define M_DOWN		4

#define LEFTB  	 1
#define RIGHTB 	 2
#define EMPTY	-1

/* --------------------------------------------------------------------
						  Baülçk Dosyasç Sonu
   -------------------------------------------------------------------- */
#endif