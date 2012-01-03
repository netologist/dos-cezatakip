#include "/ozgan/programs/h/genel.h"

int sayi_esitle(char *sayi1, char *sayi2)
{
	char gecici;
	int s1, s2, elde, i;

	s1 = strlen(sayi1);
	s2 = strlen(sayi2);

	if (s1 < s2) {
		elde = s2 - s1;
		strrev(sayi1);
		for (i = 0; i < elde; i++)
			sayi1[s1+i] = '0';
		sayi1[s1+i] = 0;
		strrev(sayi1);
	}
	else {
		elde = s1 - s2;
		strrev(sayi2);
		for (i = 0; i < elde; i++)
			sayi2[s2+i] = '0';
		sayi2[s2+i] = 0;
		strrev(sayi2);
	}
	return strlen(sayi2);
}

void _toplama(char *sayi1, char *sayi2, char *sonuc)
{
	int elde = 0, kontrol, i;

	sayi_esitle(sayi1, sayi2);
	strrev(sayi1);
	strrev(sayi2);

	kontrol = strlen(sayi1);
	memset(sonuc, 0, kontrol+1);
	for (i = 0; i < kontrol; i++) {
		sonuc[i] = (((sayi1[i] - '0') + (sayi2[i] - '0') + elde ) % 10) + '0';
		elde = ( (sayi1[i] - '0') + (sayi2[i] - '0') + elde ) / 10;
	}
	if (elde != 0) {
		sonuc[i] = elde + '0';
	}
	strrev(sayi1);
	strrev(sayi2);
	strrev(sonuc);
}

void sifir_ekle(char *sayi, int n)
{
	int i, uzunluk;

	uzunluk = karakter_uzunlugu(sayi);
	for (i = 0; i < n; i++)
		sayi[i+uzunluk] = '0';
}

char sayi_kontrol(char *sayi1, char *sayi2)
{
	int kontrol, i;

	sayi_esitle(sayi1, sayi2);
	kontrol = strlen(sayi1);

	for (i = 0; i < kontrol; i++)
		if (sayi1[i] > sayi2[i])
			return 1; // ilk sayi bÅyÅk
		else
			if (sayi1[i] < sayi2[i])
				return -1; // ilk sayi kÅáÅk

	return 0; // sayilar esit
}

void sayi_temizle(char *sonuc, int uzunluk)
{
	char depo[100];
	int i = 0;

	memset(depo, 0, 100);
	strcpy(depo, sonuc);

	while (depo[i] == '0')
		i++;

	if (depo[i] == '\0') {
		i--;
		depo[i] = '0';
	}
	memset(sonuc, 0, uzunluk);
	strcpy(sonuc, &depo[i]);
}

void _cikarma(char *sayi1, char *sayi2, char *sonuc)
{
	char *s1, *s2;
	int elde = 0, kontrol, i, sayi_uzunlugu;

	sayi_uzunlugu = sayi_esitle(sayi1, sayi2);
	kontrol = strlen(sayi2);
	if ((sayi_kontrol(sayi1, sayi2) > 0)) {
		s1 = sayi1; s2 = sayi2;
	}
	else {
		s1 = sayi2; s2 = sayi1;
	}
	strrev(s1);
	strrev(s2);

	memset(sonuc, 0, kontrol+1);
	for (i = 0; i < kontrol; i++) {
		if (s1[i] < s2[i]) {
			if (s1[i+1] == 0) {
				s1[i+1] = 9;
			}
			else
				s1[i+1]--;
			elde = s1[i] + 10;
			sonuc[i] = (elde - s2[i]) + '0';
		}
		else
			sonuc[i] = (s1[i] - s2[i]) + '0';
	}
	strrev(sonuc);
	strrev(s1);
	strrev(s2);
	sayi_temizle(sonuc, sayi_uzunlugu);
	sayi_temizle(s1, sayi_uzunlugu);
	sayi_temizle(s2, sayi_uzunlugu);
}

int sifir_cikar(char *sayi)
{
	int uzunluk = 0;

	strrev(sayi);
	while (sayi[uzunluk] == '0')
		uzunluk++;

	strrev(sayi);
	sayi[strlen(sayi)-uzunluk] = NULL;
	return uzunluk;
}

void carpim(char *sayi1, char *sayi2, char *sonuc)
{
	int i, sayi_uzunlugu;
	char *s1, *s2;
	char temp[100];
	long sayac;

	if ((sayi_kontrol(sayi1, sayi2) > 0)) {
		s1 = sayi1; s2 = sayi2;
	}
	else {
		s1 = sayi2; s2 = sayi1;
	}
	strcpy(temp, s1);
	sayac = atol(s2);
	for (i = 1; i < sayac; i++) {
		_toplama(temp, s1, sonuc);
		strcpy(temp, sonuc);
	}
	sonuc[strlen(sonuc)+1] = '\0';
	strrev(s2);
	switch (s2[0]) {
		case '0': if (karakter_uzunlugu(s2) <= 1) {
					  strcpy(sonuc, "0");
					  return;
				  }
				  else
					  strcpy(sonuc, "0");
				  break;
		case '1': if (karakter_uzunlugu(s2) <= 1) {
					  strcpy(sonuc, s1);
					  return;
				  }
				  else
					strcpy(sonuc, s1);
	}
	strrev(s2);
	sayi_uzunlugu = strlen(sonuc);
	sayi_temizle(sonuc, sayi_uzunlugu);
}

int	karakter_uzunlugu(char *sayi)
{
	int i = 0;

	while (sayi[i] == '0')
		i++;
	return strlen(sayi) - i;
}

void _carpma(char *sayi1, char *sayi2, char *sonuc)
{
	char temp1[100], temp2[100], temp3[100], *s1, *s2;
	int i, sayac;

	if ((sayi_kontrol(sayi1, sayi2) > 0)) {
		s1 = sayi1; s2 = sayi2;
	}
	else {
		s1 = sayi2; s2 = sayi1;
	}
	sayac = karakter_uzunlugu(s2);
	memset(temp1, 0, 100);
	memset(temp2, 0, 100);
	strcpy(temp2, "0000");
	strrev(s2);

	if (sayac == 0)
		strcpy(sonuc, "0");

	for (i = 0; i < sayac; i++) {
		temp1[0] = s2[i];
		temp1[1] = '\0';
		memset(temp3, 0, 100);
		carpim(s1, temp1, temp3);
		sifir_ekle(temp3, i);
		_toplama(temp3, temp2, sonuc);
		strcpy(temp2, sonuc);
	}
	strrev(s2);
}

void _bolme(char *bolunen, char *bolen, char *sonuc)
{
	char gecici_bolunen[100];
	char cikarma_sonucu[100];
	char carpma_sonucu[100];
	char katsayi[100];
	char yeni_bolunen[100];
	int dongu_tutucu = 0, bolen_uzunlugu,
		bolunen_uzunlugu = 0, j = 0, sayi_uzunlugu;

	bolen_uzunlugu = strlen(bolen);
	dongu_tutucu = strlen(bolunen);

	if (karakter_uzunlugu(bolen) == 0) {
		strcpy(sonuc, "0");
		goto SON;
	}

	memset(carpma_sonucu, 0, 100);
	memset(cikarma_sonucu, 0, 100);
	memset(gecici_bolunen, 0, 100);
	memset(yeni_bolunen, 0, 100);

	bolunen_uzunlugu += bolen_uzunlugu;
	dongu_tutucu -= bolunen_uzunlugu;
	strncpy(gecici_bolunen, bolunen, bolen_uzunlugu);

	while (dongu_tutucu != -1) {
		if (sayi_kontrol(gecici_bolunen, bolen) < 0) {
				sonuc[bolunen_uzunlugu-bolen_uzunlugu] = '\0';
				sonuc[bolunen_uzunlugu-bolen_uzunlugu+1] = '\0';
		}
		katsayi[0] = katsayi_bul(gecici_bolunen, bolen) + '0';
		katsayi[1] = '\0';
		sonuc[bolunen_uzunlugu-bolen_uzunlugu] = katsayi[0]; sonuc[bolunen_uzunlugu-bolen_uzunlugu+1] = '\0';
		dongu_tutucu--; bolunen_uzunlugu++;
		carpma(bolen, katsayi, carpma_sonucu);
		cikarma(gecici_bolunen, carpma_sonucu, yeni_bolunen);
		j = strlen(yeni_bolunen);
		yeni_bolunen[j] = bolunen[bolunen_uzunlugu-1]; j++;
		yeni_bolunen[j] = '\0';
		strcpy(gecici_bolunen, yeni_bolunen);
	}
SON:
	sayi_uzunlugu = strlen(sonuc);
	sayi_temizle(sonuc, sayi_uzunlugu);
}

char katsayi_bul(char *bolunen, char *bolen)
{
	int i = 0, sayi_uzunlugu;
	char temp1[100], temp2[100];
	memset(temp1, 0, 100);
	memset(temp2, 0, 100);

	sayi_uzunlugu = strlen(bolunen);
	sayi_temizle(bolunen, sayi_uzunlugu);
	if (bolunen[0] == '0')
		return 0;

	if (sayi_kontrol(bolunen, temp1) == 0)
		return 1;
	else
		do {
			i++;
			itoa(i, temp2, 10);
			carpma(bolen, temp2, temp1);
		} while (sayi_kontrol(bolunen, temp1) > 0);

		if (sayi_kontrol(bolunen, temp1) < 0)
				i--;
	return i;
}

void toplama(char *sayi1, char *sayi2, char *sonuc)
{
	int islem; // islem eßer 1 cikar degilse toplama
	int isaret; // eßer 1 ise eksi deßilse artç
	char s1[50];
	char s2[50];

	memset(s1, 0, 50);
	memset(s2, 0, 50);

	strcpy(s1, sayi1);
	strcpy(s2, sayi2);

	if (sayi1[0] == '-') {
		strcpy(s1, &sayi1[1]);
		if (sayi2[0] == '-') {
		   strcpy(s2, &sayi2[1]);
		   isaret = 1;
		   islem = 0;
		}
		else {
			islem = 1;
			if (sayi_kontrol(s2, s1) > 0)
				isaret = 0;
			else
				isaret = 1;
		}
	}
	else {
		if (sayi2[0] == '-') {
			strcpy(s2, &sayi2[1]);
			if (sayi_kontrol(s2, s1) > 0) {
				isaret = 1;
				islem = 1;
			}
			else {
				isaret = 0;
				islem = 1;
			}
		}
		else {
			isaret = 0;
			islem = 0;
		}
	}

	if (islem == 0)
		_toplama(s1, s2, sonuc);
	else
		_cikarma(s1, s2, sonuc);

	if (isaret == 1 && sonuc[0] != '0') {
		memset(s1, 0, 50);
		strcpy(s1, sonuc);
		sonuc[0] = '-';
		strcpy(&sonuc[1], s1);
	}
}

void cikarma(char *sayi1, char *sayi2, char *sonuc)
{
	int islem; // islem eßer 1 cikarma degilse toplama
	int isaret; // eßer 1 ise eksi deßilse artç
	char s1[50];
	char s2[50];

	memset(s1, 0, 50);
	memset(s2, 0, 50);

	strcpy(s1, sayi1);
	strcpy(s2, sayi2);

	if (sayi1[0] == '-') {
		strcpy(s1, &sayi1[1]);
		if (sayi2[0] == '-') {
		   strcpy(s2, &sayi2[1]);
		   islem = 1;
		   if (sayi_kontrol(s2, s1) < 0)
				isaret = 1;
			else
				isaret = 0;
		}
		else {
			isaret = 1;
			islem = 0;
		}
	}
	else {
		if (sayi2[0] == '-') {
			strcpy(s2, &sayi2[1]);
			isaret = 0;
			islem = 0;
		}
		else {
		   islem = 1;
		   if (sayi_kontrol(s2, s1) < 0)
				isaret = 0;
			else
				isaret = 1;
		}
	}

	if (islem == 0)
		_toplama(s1, s2, sonuc);
	else
		_cikarma(s1, s2, sonuc);

	if (isaret == 1 && sonuc[0] != '0') {
		memset(s1, 0, 50);
		strcpy(s1, sonuc);
		sonuc[0] = '-';
		strcpy(&sonuc[1], s1);
	}
}

void bolme(char *sayi1, char *sayi2, char *sonuc)
{
	int isaret = 0; // eßer 1 ise eksi deßilse artç
	char s1[50];
	char s2[50];

	memset(s1, 0, 50);
	memset(s2, 0, 50);

	strcpy(s1, sayi1);
	strcpy(s2, sayi2);

	if (sayi1[0] == '-') {
		strcpy(s1, &sayi1[1]);
		isaret = 1;
		if (sayi2[0] == '-') {
			strcpy(s2, &sayi2[1]);
			isaret = 0;
		}
	}
	else if (sayi2[0] == '-') {
		strcpy(s2, &sayi2[1]);
		isaret = 1;
	}

	if (isaret == 1) {
		sonuc[0] = '-';
		_bolme(s1, s2, &sonuc[1]);
	}
	else
		_bolme(s1, s2, sonuc);
}

void carpma(char *sayi1, char *sayi2, char *sonuc)
{
	int isaret = 0; // eßer 1 ise eksi deßilse artç
	char s1[50];
	char s2[50];

	memset(s1, 0, 50);
	memset(s2, 0, 50);

	strcpy(s1, sayi1);
	strcpy(s2, sayi2);

	if (sayi1[0] == '-') {
		strcpy(s1, &sayi1[1]);
		isaret = 1;
		if (sayi2[0] == '-') {
			strcpy(s2, &sayi2[1]);
			isaret = 0;
		}
	}
	else if (sayi2[0] == '-') {
		strcpy(s2, &sayi2[1]);
		isaret = 1;
	}

	if (sayi1[0] != '0' || sayi2[0] != '0')
		isaret = 0;

	if (isaret == 1) {
		sonuc[0] = '-';
		_carpma(s1, s2, &sonuc[1]);
	}
	else
		_carpma(s1, s2, sonuc);
}

#if 0
void main(void)
{
	char sayi1[100];
	char sayi2[100];
	char sonuc[100];

	memset(sayi1, 0, 100);
	memset(sayi2, 0, 100);
	memset(sonuc, 0, 100);

	strcpy(sayi1, "-20");
	strcpy(sayi2, "120");

	toplama(sayi1, sayi2, sonuc);
	doldur(10, 10, ' ', 20, SIYAH);
	harfler(10, 10, basamakla(sonuc), YESIL_ | A_BEYAZ);
	getkb();

}

#endif


