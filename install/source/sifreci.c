#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <string.h>

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

char *sifre_bul(char *Parola, char *Karsi_Deger)
{
	unsigned long sayi;
	int i;

	strncpy(Karsi_Deger, &Parola[4], 10);
	sayi = atol(Karsi_Deger);
	sayi *= 0.9;
	ltoa(sayi, Karsi_Deger, 16);
	strupr(Karsi_Deger);
	return Karsi_Deger;
}

void main(void)
{
	char Parola[50];
	char Anahtar[50];
	char formatci[50];

	memset(Parola, 0, 50);
	printf("Kilit no giriniz ->");
	gets(Parola);
	sifre_bul(Parola, Anahtar);
	formatla(Anahtar, formatci, "####-####");
	printf("Anahrar kelime [ %s ]\n", formatci);
}

