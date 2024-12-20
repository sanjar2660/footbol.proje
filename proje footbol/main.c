#include <stdio.h>
#include <string.h>

// Oyuncu bilgilerini tutan struct
typedef struct {
    char ad[1000];
    char soyad[1000];
    int macSayisi;
    int hataliPas;
    int isabetliPas;
} Oyuncu;

#define MAX_FUTBOLCU 20


// Ekleme fonksiyonu
void ekle(Oyuncu oyuncular[], int *oyuncuSayisi, char *ad, char *soyad, int hataliPas, int isabetliPas) {
    for (int i = 0; i < *oyuncuSayisi; i++) {
        if (strcmp(oyuncular[i].ad, ad) == 0 && strcmp(oyuncular[i].soyad, soyad) == 0) {
            // Oyuncu mevcut, bilgileri güncelleme
            oyuncular[i].macSayisi++;
            oyuncular[i].hataliPas += hataliPas;
            oyuncular[i].isabetliPas += isabetliPas;

            return;
        }
    }
    // Yeni oyuncu ekleme yeri
    if (*oyuncuSayisi < MAX_FUTBOLCU) {
        strcpy(oyuncular[*oyuncuSayisi].ad, ad);
        strcpy(oyuncular[*oyuncuSayisi].soyad, soyad);
        oyuncular[*oyuncuSayisi].macSayisi =1;
        oyuncular[*oyuncuSayisi].hataliPas = hataliPas;
        oyuncular[*oyuncuSayisi].isabetliPas = isabetliPas;
        printf("Eklendi: %s %s - Mac Sayisi: 1\n", ad, soyad);
        (*oyuncuSayisi)++;
    } else {
        printf("Oyuncu sayisi sinirina ulasildi! %s %s eklenemedi.\n", ad, soyad);
    }
}

// Yazdırma fonksiyonu
void yazdir(Oyuncu oyuncular[], int oyuncuSayisi, const char *dosyaAdi) {
    FILE *dosya = fopen(dosyaAdi, "w");
    if (!dosya) {
        printf("%s dosyasi acilamadi!\n", dosyaAdi);
        return;
    }

    for (int i = 0; i < oyuncuSayisi; i++) {
        fprintf(dosya, "%s %s %d %d %d\n",
                oyuncular[i].ad,
                oyuncular[i].soyad,
                oyuncular[i].macSayisi,
                oyuncular[i].hataliPas,
                oyuncular[i].isabetliPas);
    }

    fclose(dosya);
}

int main() {
    Oyuncu oyuncular[MAX_FUTBOLCU];
    int oyuncuSayisi = 0;

    FILE *girdiDosyasi = fopen("paslar.txt", "r");
    if (!girdiDosyasi) {
        printf("paslar.txt dosyasi acilamadi!\n");
        return 1;
    }

    char ad[50], soyad[50];
    int hataliPas, isabetliPas;

    // Dosyadan okuyarak oyuncuları ekleyen yer
    while (fscanf(girdiDosyasi, "%s %s %d %d", ad, soyad, &hataliPas, &isabetliPas) == 4) {
        ekle(oyuncular, &oyuncuSayisi, ad, soyad, hataliPas, isabetliPas);
    }

    fclose(girdiDosyasi);

    // Sonuçları toplam.txt dosyasına yazdıran yer
    yazdir(oyuncular, oyuncuSayisi, "toplam.txt");

    printf("Sonuclar toplam.txt dosyasina yazdirildi.\n");

    return 0;
}