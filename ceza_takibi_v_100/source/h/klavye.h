/* -------------------------------------------------------------------------
						  OzganSYS Software World (c)
					 Klavye Fonksiyonlarç KÅtÅphanesi v.1.00
								 21 Kasçm 2000
   ------------------------------------------------------------------------- */
#ifndef _KLAVYE_H_
#define _KLAVYE_H_
/* -------------------------------------------------------------------------
								 Sabit Tançmlamalarç
   ------------------------------------------------------------------------- */

/* Klavye'deki giriüler */
#define YAZI_KRTR 	" \"*-Ç!'^+%&/()=?_ú#$´{[]}\\@|<>:.,;~1234567890QWERTYUIOP¶öASDFGHJKLûòZXCVBNMôÄqwertyuçopßÅasdfghjklüizxcvbnmîá"
#define SAYI_KRTR 	"0123456789"

/* Normal Halleri */
#define F1	0x3b00
#define F2 	0x3c00
#define F3  0x3d00
#define F4  0x3e00
#define F5  0x3f00
#define F6  0x4000
#define F7  0x4100
#define F8  0x4200
#define F9  0x4300
#define F10	0x4400

/* ALT Tusuna Basili Halleri */
#define ALT_F1	0x6800
#define ALT_F2 	0x6900
#define ALT_F3  0x6a00
#define ALT_F4  0x6b00
#define ALT_F5  0x6c00
#define ALT_F6  0x6d00
#define ALT_F7  0x6e00
#define ALT_F8  0x6f00
#define ALT_F9  0x7000
#define ALT_F10	0x7100

/* CTRL Tusuna Basili Halleri */
#define CTRL_F1	  0x5e00
#define CTRL_F2   0x5f00
#define CTRL_F3	  0x6000
#define CTRL_F4	  0x6100
#define CTRL_F5	  0x6200
#define CTRL_F6	  0x6300
#define CTRL_F7	  0x6400
#define CTRL_F8	  0x6500
#define CTRL_F9	  0x6600
#define CTRL_F10  0x6700

/* SHIFT Tusuna Basili Halleri */
#define SHIFT_F1	0x5400
#define SHIFT_F2   	0x5500
#define SHIFT_F3 	0x5600
#define SHIFT_F4 	0x5700
#define SHIFT_F5  	0x5800
#define SHIFT_F6  	0x5900
#define SHIFT_F7  	0x5a00
#define SHIFT_F8  	0x5b00
#define SHIFT_F9  	0x5c00
#define SHIFT_F10	0x5d00

/* CTRL Makrolari */
#define CTRL_A 	0x1e01
#define CTRL_B	0x3002
#define CTRL_C	0x2e03
#define CTRL_D  0x2004
#define CTRL_E  0x1205
#define CTRL_F  0x2106
#define CTRL_G  0x2207
#define CTRL_H	0x2308
#define CTRL_I  0x1709
#define CTRL_J	0x240a
#define CTRL_K  0x250b
#define CTRL_L  0x2605
#define CTRL_M  0x320d
#define CTRL_N	0x310e
#define CTRL_O	0x180f
#define CTRL_P  0x1910
#define CTRL_R  0x1312
#define CTRL_S  0x1f13
#define CTRL_T  0x1414
#define CTRL_U  0x1615
#define CTRL_V  0x2f16
#define CTRL_Y  0x1519
#define CTRL_Z  0x2c1a

/* ALT Makrolari */
#define ALT_0 	0x8100
#define ALT_1 	0x7800
#define ALT_2 	0x7900
#define ALT_3 	0x7a00
#define ALT_4 	0x7b00
#define ALT_5 	0x7c00
#define ALT_6 	0x7d00
#define ALT_7 	0x7e00
#define ALT_8 	0x7f00
#define ALT_9 	0x8000
#define ALT_A 	0x1e00
#define ALT_B	0x3000
#define ALT_C	0x2e00
#define ALT_D   0x2000
#define ALT_E   0x1200
#define ALT_F   0x2100
#define ALT_G   0x2200
#define ALT_H  	0x2300
#define ALT_I   0x1700
#define ALT_J	0x2400
#define ALT_K   0x2500
#define ALT_L   0x2600
#define ALT_M   0x3200
#define ALT_N	0x3100
#define ALT_O	0x1800
#define ALT_P   0x1900
#define ALT_R   0x1300
#define ALT_S   0x1f00
#define ALT_T   0x1400
#define ALT_U   0x1600
#define ALT_V   0x2f00
#define ALT_Y   0x1500
#define ALT_Z   0x2c00

/* Klavye`nin KeyPad (KP) Tuslari */
#define	KP_HOME	 0x4700
#define	KP_END	 0x4f00
#define	KP_INS	 0x5200
#define	KP_DEL   0x5300
#define	KP_PGUP  0x4900
#define	KP_PGDN  0x5100

#define	CTRL_KP_HOME	 0x7700
#define	CTRL_KP_END		 0x7500
#define	CTRL_KP_INS		 0x9200
#define	CTRL_KP_DEL   	 0x9300
#define	CTRL_KP_PGUP  	 0x8400
#define	CTRL_KP_PGDN  	 0x7600

#define KP_ENTER    	0xe00d
#define CTRL_KP_ENTER   0xe00a

#define	KP_LEFT  0x4b00
#define	KP_RIGHT 0x4d00
#define	KP_UP 	 0x4800
#define	KP_DOWN  0x5000

/* Hareket ve Islev Tuslari */
#define ENTER 		0x1c0d
#define CTRL_ENTER	0x1c0a

#define	HOME  0x47e0
#define	END	  0x4fe0
#define	INS	  0x52e0
#define	DEL   0x53e0
#define	PGUP  0x49e0
#define	PGDN  0x51e0

#define	CTRL_HOME	 0x77e0
#define	CTRL_END	 0x75e0
#define	CTRL_INS	 0x92e0
#define	CTRL_DEL   	 0x93e0
#define	CTRL_PGUP  	 0x84e0
#define	CTRL_PGDN  	 0x76e0

#define	LEFT  0x4be0
#define	RIGHT 0x4de0
#define	UP 	  0x48e0
#define	DOWN  0x50e0

#define TAB			0x0f09
#define SHIFT_TAB	0x0f00

#define SPACE		0x3920
#define BACKSPACE	0x0e08
#define ESC			0x011b

/* --------------------------------------------------------------------
						  Baülçk Dosyasç Sonu
   -------------------------------------------------------------------- */
#endif
