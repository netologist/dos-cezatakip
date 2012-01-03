#include "/ozgan/programs/h/genel.h"
#include "src/ceza.h"

void degisken_ayarla(void);
void yaziciya_gonder(char *dosya_adi);
void dizayn_yukle(char *dosya_adi, char *yazdirma_alani);
void dosyala(char *dosya_adi, char *alan);
void yazici_dosyasi_yarat(char *dosya_adi);

typedef struct _YAZICI_DATA {
	char Sayfa[4];
	char Unvan[31];
	char VD[15];
	char VN[13];
	char Binde_Oran[7];
	char Taksit[4];
	char Toplam_Hesap[16];
	char Aylik_Hesap[16];
	char Devir_Ana_Para[16];
	char Devir_Faiz[16];
	char Devir_Borc_Toplami[16];
	char Toplam_Ana_Para[16];
	char Toplam_Faiz[16];
	char Toplam_Borc_Toplami[16];
	char Tarih[13];
	char Oran[7];
	char Ana_Para[16];
	char Faiz[16];
	char Borc_Toplami[16];
} YAZICI_DATA;

YAZICI_DATA yazici_data;

void tablo_yaz(int satir, int kolon, long tablo_adi, char *data, char *ana_data, TABLO_FORM *tablo, TABLO_BILGI *baslik)
{
	int i, data_yeri = 0, kolon_yeri = 0;
	char gecici_data[80];

	memset(gecici_data, 0, 80);
	for (i = 0; i < baslik->eleman_sayisi; i++) {
		if (tablo[i].tablo_adi == tablo_adi) {
			switch(tablo[i].hucre) {
				case YAZI: strncpy(&ana_data[((tablo[i].satir+satir)*82)+(tablo[i].kolon+kolon)], &data[data_yeri], strlen(&data[data_yeri]));
						   break;
				case SAYI: kolon_yeri = tablo[i].uzunluk - strlen(basamakla(&data[data_yeri]));
						   strncpy(&ana_data[((tablo[i].satir+satir)*82)+(tablo[i].kolon+kolon+kolon_yeri)], basamakla(&data[data_yeri]), strlen(basamakla(&data[data_yeri])));
						   break;
				case YUVARLAK_KUTU:
						   ana_data[((tablo[i].satir+satir)*82)+(tablo[i].kolon+kolon)] = '\x07';
						   break;
				case KARE_KUTU:
					if (data[data_yeri] == 1)
						ana_data[((tablo[i].satir+satir)*82)+(tablo[i].kolon+kolon)] = 'X';
					else
						ana_data[((tablo[i].satir+satir)*82)+(tablo[i].kolon+kolon)] = ' ';
					break;
				case TARIH:
						if (strlen(&data[data_yeri]) == 0)
							tarih_al(&data[data_yeri]);
						formatla(&data[data_yeri], gecici_data, "##/##/####");
						strncpy(&ana_data[((tablo[i].satir+satir)*82)+(tablo[i].kolon+kolon)], gecici_data, strlen(gecici_data));
					break;
			}
		}
		data_yeri += tablo[i].uzunluk + 1;
	}
}

void yazici_form(void)
{
	DOSYA handle;
	TABLO_BILGI baslik2 = {20, sizeof(YAZICI_DATA), Form_RAPOR, 0};
	TABLO_FORM tablo2[] = {{Data_Rapor_Sabit, YAZI, 2, 76, 3, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor_Sabit, YAZI, 5, 10, 30, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor_Sabit, YAZI, 5, 46, 14, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor_Sabit, YAZI, 5, 66, 12, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor_Sabit, YAZI, 6, 30, 6, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor_Sabit, SAYI, 6, 56, 3, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, SONRA},
						   {Data_Rapor_Sabit, SAYI, 8, 24, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Sabit, SAYI, 8, 60, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Sabit, SAYI, 13, 28, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Sabit, SAYI, 13, 45, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Sabit, SAYI, 13, 63, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Sabit, SAYI, 58, 28, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Sabit, SAYI, 58, 45, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Sabit, SAYI, 58, 63, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Degisken, YAZI, 15, 7, 12, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Degisken, SAYI, 15, 19, 6, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Degisken, SAYI, 15, 28, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Degisken, SAYI, 15, 45, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK},
						   {Data_Rapor_Degisken, SAYI, 15, 63, 15, BEYAZ_ | A_BEYAZ, BEYAZ_ | GRI, Data_Bos_Referans, YOK}
						  };

	tabloyarat("bin/ceza.prn", &baslik2, tablo2);
	handle.tablo = (TABLO_FORM *) tabloyukle("bin/ceza.prn", &handle.baslik);
	memset(&yazici_data, 0, sizeof(yazici_data));
	memcpy(yazici_data.Unvan, dataci, sizeof(TABLO_DATA));
	yazici_dosyasi_yarat("temp/$0145165.tmp");
	degisken_ayarla();
	yaziciya_gonder("temp/$0145165.tmp");
}

void yaziciya_gonder(char *dosya_adi)
{
	FILE *afp;
	int sayfa_no, i;
	char alan[9840];

	if ((afp = _fsopen(dosya_adi, "rb", SH_DENYNO)) == NULL) {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}

	sayfa_no = atoi(yazici_data.Sayfa);
	for (i = 0; i < sayfa_no; i++) {
		sprintf(alan, " %d. Sayfa", i+1);
		mesaj_goster_kac(alan);
		fseek(afp, i*4920, SEEK_SET);
		fread(alan, 1, 4920, afp);
		fwrite(alan, 1, 4920, stdprn);
	}
	fclose(afp);
}

void sayfa_ayari(char *alan, int sayfa_no)
{
	/*   Dizayn dosyasi yukleniyor */
	dizayn_yukle("bin/ceza.dzn", alan);
	/*-----------------------------*/
	/* Sayfa No ayarlançyor*/
	sprintf(yazici_data.Sayfa, "%03d", sayfa_no);
	/*---------------------*/
	/* Devir Kçsmç ayarlançyor */
	strcpy(yazici_data.Devir_Ana_Para, yazici_data.Toplam_Ana_Para);
	strcpy(yazici_data.Devir_Faiz, yazici_data.Toplam_Faiz);
	strcpy(yazici_data.Devir_Borc_Toplami, yazici_data.Toplam_Borc_Toplami);
	/*-------------------------*/
}

void degisken_ayarla(void)
{
	DOSYA handle, yazici;
	long adres;
	FILE *p;
	int n, sayfa_no = 0;
	char gecici[20];
	char alan[4920];

	handle.data = malloc(sizeof(HESAP_DATA));
	if (handle.data == NULL) {
		msj_kutu(NULL, HATA_BELLEK_YETERSIZ, HATA);
		exit(1);
	}
	strcpy(handle.ana_dosya, "hesap.dat");
	strcpy(handle.indeks_dosya, "hesap.ind");
	strcpy(handle.yol, "data/");

	sayfa_ayari(alan, (sayfa_no/42)+1);
	yazici.tablo = (TABLO_FORM *) tabloyukle("bin/ceza.prn", &yazici.baslik);
	dosya_ac(&handle);
	hesap_data = (HESAP_DATA *) handle.data;
	adres = handle.indeks_baslik->ilk_kayit;
	for (n = 0; n < handle.indeks_baslik->toplam_kayit; n++) {
		detay_oku(&handle, adres, DATA_AL);
		memcpy(handle.data, handle.ana_detay->data, handle.ana_baslik->bir_datanin_uzunlugu);
		hesap_data = (HESAP_DATA *) handle.data;
		/* Sayfa Toplamç Ayarlançyor */
		memset(gecici, 0, 20);
		strcpy(gecici, yazici_data.Toplam_Ana_Para);
		toplama(hesap_data->Ana_Para, gecici, yazici_data.Toplam_Ana_Para);
		memset(gecici, 0, 20);
		strcpy(gecici, yazici_data.Toplam_Faiz);
		toplama(hesap_data->Faiz_Tutari, gecici, yazici_data.Toplam_Faiz);
		memset(gecici, 0, 20);
		strcpy(gecici, yazici_data.Toplam_Borc_Toplami);
		toplama(hesap_data->Borc_Toplami, gecici, yazici_data.Toplam_Borc_Toplami);
		/*-------------------------*/
		/* Detay Ayarlançyor */
		strcpy(yazici_data.Tarih, hesap_data->Referans);
		strcpy(yazici_data.Oran, hesap_data->Oran);
		strcpy(yazici_data.Ana_Para, hesap_data->Ana_Para);
		strcpy(yazici_data.Faiz, hesap_data->Faiz_Tutari);
		strcpy(yazici_data.Borc_Toplami, hesap_data->Borc_Toplami);
		/*-----------------*/
		tablo_yaz(n-sayfa_no-1, -1, Data_Rapor_Degisken, (char *) &yazici_data, alan, yazici.tablo, &yazici.baslik);
		adres = handle.indeks_detay->sonraki;
		if (((n+1) % 42) == 0) {
			sayfa_no += 42;
			tablo_yaz(-1, -1, Data_Rapor_Sabit, (char *) &yazici_data, alan, yazici.tablo, &yazici.baslik);
			dosyala("temp/$0145165.tmp", alan);
			sayfa_ayari(alan, (sayfa_no/42)+1);
		}
	}
	tablo_yaz(-1, -1, Data_Rapor_Sabit, (char *) &yazici_data, alan, yazici.tablo, &yazici.baslik);
	dosyala("temp/$0145165.tmp", alan);
	free(handle.data);
	dosya_kapa(&handle);
}
void yazici_dosyasi_yarat(char *dosya_adi)
{
	FILE *fp;

	if ((fp = _fsopen(dosya_adi, "wb", SH_DENYNO)) == NULL) {
		msj_kutu(NULL, "Disk kayçt hatasç", HATA);
		exit(1);
	}
	fclose(fp);
}

void dosyala(char *dosya_adi, char *alan)
{
	FILE *fp;

	if ((fp = _fsopen(dosya_adi, "rb+", SH_DENYNO)) == NULL) {
		msj_kutu(NULL, "Disk kayçt hatasç", HATA);
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	fwrite(alan, 1, 4920, fp);
	fclose(fp);
}

void dizayn_yukle(char *dosya_adi, char *yazdirma_alani)
{
	FILE *fp;

	if ((fp = _fsopen(dosya_adi, "rb", SH_DENYNO)) == NULL) {
		msj_kutu(dosya_adi_ayir(dosya_adi), HATA_DOSYA_BULUNAMADI, HATA);
		exit(1);
	}
	fseek(fp, 0, SEEK_SET);
	fread(yazdirma_alani, 1, 4920, fp);
	fclose(fp);
}
