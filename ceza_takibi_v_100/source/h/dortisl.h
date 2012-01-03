/* -------------------------------------------------------------------------
						  OzganSYS Software World (c)
				  Dort òülem Fonksiyonlarç KÅtÅphanesi v.1.00
								 21 Kasçm 2000
   ------------------------------------------------------------------------- */
#ifndef _DORT_ISLEM_H_
#define _DORT_ISLEM_H_

int sayi_esitle(char *sayi1, char *sayi2);
void sayi_temizle(char *sonuc, int uzunluk);
char katsayi_bul(char *bolunen, char *bolen);
void sifir_ekle(char *sayi, int n);
int sifir_cikar(char *sayi);
int	karakter_uzunlugu(char *sayi);
char sayi_kontrol(char *sayi1, char *sayi2);
void toplama(char *sayi1, char *sayi2, char *sonuc);
void cikarma(char *buyuk, char *kucuk, char *sonuc);
void carpma(char *sayi1, char *sayi2, char *sonuc);
void carpim(char *sayi1, char *sayi2, char *sonuc);
void bolme(char *bolunen, char *bolen, char *sonuc);
void _toplama(char *sayi1, char *sayi2, char *sonuc);
void _cikarma(char *buyuk, char *kucuk, char *sonuc);
void _carpma(char *sayi1, char *sayi2, char *sonuc);
void _bolme(char *bolunen, char *bolen, char *sonuc);

#endif