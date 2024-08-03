#include <stdio.h>
#include <string.h>

#define MAX_SEPET_OGELERI 100

typedef struct {
    char isim[50];
    int fiyat;
} Product;

typedef struct {
    Product urun;
    int miktar;
} sepetitem;

void kayit() {
    char kullaniciAdi[50];
    char kullaniciSifre[50];

    printf("Kullanici Adi : ");
    scanf("%s", kullaniciAdi);
    printf("Sifre : ");
    scanf("%s", kullaniciSifre);

    FILE *kayitdosya = fopen("kullanici_bilgileri.txt", "a");
    if (kayitdosya == NULL) {
        printf(" -- Dosya Bulunamadi --");
    }

    fprintf(kayitdosya, "%s %s \n", kullaniciAdi, kullaniciSifre);
    fclose(kayitdosya);

    printf(" \n -- Kayit Basarili -- \n ");
}

int giris() {
    char kullaniciAdi[50];
    char kullaniciSifre[50];
    char kontrolad[50];
    char kontrolsifre[50];
    int kullanicidogrulama = 0;

    printf("Kullanici Adi: ");
    scanf("%s", kullaniciAdi);
    printf("Sifre: ");
    scanf("%s", kullaniciSifre);

    FILE *girisdosya = fopen("kullanici_bilgileri.txt", "r");
    if (girisdosya == NULL) {
        printf(" -- Dosya hatasi -- \n");
        return 0;
    }

    while (fscanf(girisdosya, "%s %s", kontrolad, kontrolsifre) != EOF) {
        if (strcmp(kullaniciAdi, kontrolad) == 0 && strcmp(kullaniciSifre, kontrolsifre) == 0) {
            kullanicidogrulama = 1;
            break;
        }
    }
    fclose(girisdosya);

    if (kullanicidogrulama) {
        printf(" \n -- Giris Basarili! -- \n");
        return 1;
    } else {
        printf("Kullanici Adi veya Sifre Hatali \n");
        return 0;
    }
}

int admingiris() {
    char adminadi[50];
    char adminsifre[50];

    printf("\n Admin Kullanici Adi : ");
    scanf("%s", adminadi);
    printf("Admin Sifre : ");
    scanf("%s", adminsifre);

    if (strcmp(adminadi, "admin") == 0 && strcmp(adminsifre, "admin") == 0) {
        printf(" \n --- Admin Girisi Basarili! --- \n");
        return 1;
    } else {
        printf("\n --- Admin Kullanici Adi veya Sifre Hatali ---  \n");
        return 0;
    }
}

void urunEkle(char urunadi[], int fiyat) {
    FILE *urunekle = fopen("urunler.txt", "a");
    if (urunekle == NULL) {
        printf(" \n -- Dosya hatasi -- \n");
        return;
    }

    fprintf(urunekle, "%s %d\n", urunadi, fiyat);
    fclose(urunekle);
    printf(" \n --- Urun Basariyla Eklendi! --- \n");
}

void urunKaldir(char urunadi[]) { 
    FILE *urunler = fopen("urunler.txt", "r");
    if (urunler == NULL) {
        printf(" \n -- Dosya hatasi -- \n");
    }
}
void urunleriGoster() {
    FILE *urunlistele = fopen("urunler.txt", "r");
    if (urunlistele == NULL) {
        printf("\n -- Dosya hatasi -- \n");
    }

    char urunadi[50];
    int fiyat;
    printf("\n-- Urunler Listesi --\n");
    while (fscanf(urunlistele, "%s %d", urunadi, &fiyat) != EOF) {
        printf("Urun Adi: %s, Fiyat: %d\n", urunadi, fiyat);
    }
    fclose(urunlistele);
}

void SepeteEkle(sepetitem sepet[], int *sepetSayisi) {
    FILE *sepetekle = fopen("urunler.txt", "r");
    if (sepetekle == NULL) {
        printf(" -- Dosya hatasi -- \n");
        return;
    }

    Product urun;
    int miktar;
    printf("\n-- Urunler Listesi --\n");
    while (fscanf(sepetekle, "%s %d", urun.isim, &urun.fiyat) != EOF) {
        printf("Urun Adi: %s, Fiyat: %d\n", urun.isim, urun.fiyat);
        printf("Bu urunu sepete eklemek ister misiniz? (e/h): ");
        char secim;
        scanf(" %c", &secim);

        if (secim == 'E' || secim == 'e') {
            printf("Miktar: ");
            scanf("%d", &miktar);

            int mevcut = 0;
            for (int i = 0; i < *sepetSayisi; i++) {
                if (strcmp(sepet[i].urun.isim, urun.isim) == 0) {
                    sepet[i].miktar += miktar;
                    mevcut = 1;
                    break;
                }
            }
            if (!mevcut) {
                sepet[*sepetSayisi].urun = urun;
                sepet[*sepetSayisi].miktar = miktar;
                (*sepetSayisi)++;
            }
            printf("\n --- Urun Sepete Eklendi! --- \n");
        }
    }
    fclose(sepetekle);
}

void sepetiGosterVeSatinAl(sepetitem sepet[], int sepetSayisi, int *bakiye) {
    int toplamFiyat = 0;
    printf("\n-- Sepetiniz --\n");
    for (int i = 0; i < sepetSayisi; i++) {
        int toplamFiyatItem = sepet[i].urun.fiyat * sepet[i].miktar;
        toplamFiyat += toplamFiyatItem;
        printf("Urun Adi: %s, Miktar: %d, Fiyat: %d\n", sepet[i].urun.isim, sepet[i].miktar, toplamFiyatItem);
    }
    printf("\n Toplam Fiyat: %d\n", toplamFiyat);

    if (toplamFiyat > *bakiye) {
        printf("\n --- Yeterli Bakiye Yok! --- \n");
    } else {
        printf(" \n ---- Sepeti satin almak istiyor musunuz? (e/h) :   \n");
        char secim;
        scanf(" %c", &secim);

        if (secim == 'E' || secim == 'e') {
            *bakiye -= toplamFiyat;
            printf(" \n ---- Satis Basarili! Kalan Bakiye: %d ----\n", *bakiye);
        } else {
            printf("-Satin Alma Islemi Iptal Edildi.-\n");
        }
    }
}

void adminMenu() {
    while (1) {
        printf("\n ----- Admin Menu ----- \n");
        printf("Urun Ekle ----> (1) \n");
        printf("Urun Kaldir ----> (2) \n");
        printf("Cikis ----> (3) \n");

        int adminsecim;
        scanf("%d", &adminsecim);

        if (adminsecim == 1) {
            char urunadi[50];
            int fiyat;
            printf("Urun Adi: ");
            scanf("%s", urunadi);
            printf("Urun Fiyati: ");
            scanf("%d", &fiyat);
            urunEkle(urunadi, fiyat);
        } else if (adminsecim == 2) {

        } else if (adminsecim == 3) {
            printf("Admin Menusunden Cikis Yapildi. \n");
            break;
        } else {
            printf("Yanlis Secim. Lutfen tekrar deneyin.\n");
        }
    }
}

int main() {
    int sayi;
    int girisdegeri = 0;
    int admingirisdegeri = 0;
    int bakiye = 0;

    sepetitem sepet[MAX_SEPET_OGELERI];
    int sepetSayisi = 0;

    while (1) {
        printf(" ---- Magazaya Hos Geldiniz! ---- \n");
        printf("\n Kayit Olmak Icin --- (1) \n");
        printf("Giris Yapmak Icin --- (2) \n");
        printf("Admin Giris Yapmak Icin --- (3) \n");
        printf("Cikis Yapmak Icin --- (4) \n");

        scanf("%d", &sayi);
        if (sayi == 1) {
            kayit();
        } else if (sayi == 2) {
            girisdegeri = giris();
        } else if (sayi == 3) {
            admingirisdegeri = admingiris();
        } else if (sayi == 4) {
            printf("Cikis Yapiliyor...\n");
            break;
        } else {
            printf("-- Yanlis Bir Tuslama Yaptiniz --\n");
        }

        if (girisdegeri) {
            while (1) {
                printf("\n-- Magaza Menusune Hosgeldiniz --\n");
                printf("Urunleri Gor ve Sepete Ekle ----> (1) \n");
                printf("Sepeti Gor ve Satin Al ----> (2) \n");
                printf("Bakiye Ekle ---> (3)\n");
                printf("Cikis ----> (4) \n");

                int secim;
                scanf("%d", &secim);

                if (secim == 1) {
                    SepeteEkle(sepet, &sepetSayisi);
                } else if (secim == 2) {
                    sepetiGosterVeSatinAl(sepet, sepetSayisi, &bakiye);
                } else if (secim == 3) {
                    int eklenenBakiye;
                    printf("\n Mevcut Bakiyeniz: %d \n", bakiye);
                    printf("Bakiye Eklemek Istediginiz Tutar: ");
                    scanf("%d", &eklenenBakiye);
                    bakiye += eklenenBakiye;
                    printf("Eklenen Bakiye ile Yeni Bakiye Tutari: %d \n", bakiye);
                } else if (secim == 4) {
                    printf("Cikis Yapiliyor...\n");
                    girisdegeri = 0;
                    break;
                } else {
                    printf("Yanlis Secim! Lutfen tekrar deneyin.\n");
                }
            }
        }
        if (admingirisdegeri) {
            adminMenu();
            admingirisdegeri = 0;
        }
    }

    return 0;
}
