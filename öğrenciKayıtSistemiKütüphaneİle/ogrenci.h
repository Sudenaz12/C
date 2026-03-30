#ifndef OGRENCI_H
#define OGRENCI_H

#include <stdlib.h> //malloc için 
typedef struct {
    int id;
    char name[50];
    float grade;
}Ogrenci;

// kapasite tane öğrenci için yer ayırır ve dizinin başlangıç adresini döndürür
Ogrenci* ogrenci_listesi_olustur(int kapasite);

void liste_yazdir(Ogrenci *liste, int kapasite);

// Mevcut listeyi yeni bir boyuta (yeni_n) yeniden boyutlandirir
Ogrenci* ogrenci_listesini_buyut(Ogrenci *eski_liste, int yeni_kapasite);


         //tek bir öğrenci için
/*Ogrenci* ogrenci_olustur(int id,const char *name,float grade);

void bilgileri_yazdir(Ogrenci *ptr);*/

#endif
//oğrenci oluştur fonksiyonu dışarıdan aldığı bilgilerle bellekte yer ayırması gerek 
//bu yüzden  stdlib.h include ettik.
//malloc işlemi main de değil,kütüphane içindeki grenci_olustur fonksiyonunda yaparız(sorce files da .c uzntılı)
//çünkü;kullanıcının detayları bilmesine gerek yok,direkt fonk. çağırır ve kullannır
