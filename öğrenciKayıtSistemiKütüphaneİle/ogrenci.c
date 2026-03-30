 #include <stdio.h>
#include <stdlib.h>
#include <string.h>    
#include "ogrenci.h"   // Kendi başlık dosyamızı dahil ettik

Ogrenci* ogrenci_listesi_olustur(int kapasite) {
    Ogrenci *liste = (Ogrenci*)malloc(kapasite * sizeof(Ogrenci));
    if (liste == NULL) return NULL;
    return liste;
}

Ogrenci* ogrenci_listesini_buyut(Ogrenci *eski_liste, int yeni_kapasite) {
    printf("\n--- Kapasite artiriliyor: %d ---\n", yeni_kapasite);
    Ogrenci *gecici = (Ogrenci*)realloc(eski_liste, yeni_kapasite * sizeof(Ogrenci));
    if (gecici == NULL) {
        printf("Hata: Bellek yetersiz!\n");
        return eski_liste; 
    }
    return gecici;
}


void liste_yazdir(Ogrenci *liste, int kapasite) {
    printf("\n--- Ogrenci Listesi ---\n");
    for (int i = 0; i <kapasite ; i++) {
        // liste[i] bir struct olduğu için nokta (.) ile erişiyoruz
        printf("[%d] ID: %d | Isim: %s | Not: %.2f\n", 
               i + 1, liste[i].id, liste[i].name, liste[i].grade);
    }
}


   //tek bir öğrenci için 
/*Ogrenci* ogrenci_olustur(int id, const char* name, float grade) {
    
    Ogrenci *yeni_ogrenci = (Ogrenci*)malloc(sizeof(Ogrenci)*n);
    
    if (yeni_ogrenci == NULL) {
        printf("bellek tahsis edilemedi\n");
        return NULL; 
    }
    
    //  Değerleri ata
    yeni_ogrenci->id = id;
    yeni_ogrenci->grade = grade;
    
    // C'de dizilere doğrudan atama yapılamaz (yeni_ogrenci->name = isim YANLIŞTIR)
    // Bunun yerine string kopyalama kullanılır:
    strcpy(yeni_ogrenci->name, name);
    
    //  Hazırlanan nesnenin adresini döndür
    return yeni_ogrenci;
}

void bilgileri_yazdir(Ogrenci *ptr) {
    if (ptr != NULL) {
        printf("ID: %d | Isim: %s | Not: %.2f\n", ptr->id, ptr->name, ptr->grade);
    }
}
*/





//const kullanma nedeni ismin değişmesini önlemek,sadece okumaya izin verir
//bu veri belleğin Read-Only bölgesindedir

/*malloc ile ilk başta yer ayırdığımızda verilerin içeriği boştur ve biz dışarıdan aldığımız değişkenleri heap te ayrılan bu adrese atamamız gerek
çünkü fonk. bittikten sonra verilerin silinmemesi gerek.
yeniOgrenci kısmı heapte ayrılan kısımdır dışarıdan gelen id buradaki id bölümüne atanır
*/