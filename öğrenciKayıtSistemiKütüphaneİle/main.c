 #include <stdio.h>
#include <stdlib.h>
#include <string.h>     
#include "ogrenci.h" 
 
int main() {
    int kapasite = 2; // Baslangic kapasitesi kucuk olsun ki artisi gorelim
    int mevcut_adet = 0;
    int temp_id;

    Ogrenci *liste = ogrenci_listesi_olustur(kapasite);
    if (liste == NULL) return 1;

    printf("Ogrenci kayit sistemine hos geldiniz.\n");
    printf("(Cikmak icin ID kismina 0 giriniz)\n");

    while (1) {
        printf("\nOgrenci ID: ");
        scanf("%d", &temp_id);

        if (temp_id == 0) break; // Kullanıcı 0 girerse döngüden çık

        // KAPASITE KONTROLU: Liste doldu mu?
        if (mevcut_adet == kapasite) {
            kapasite *= 2; // Kapasiteyi 2 katina cikar
            Ogrenci *yeni_yer = ogrenci_listesini_buyut(liste, kapasite);
            if (yeni_yer != NULL) {
                liste = yeni_yer;
            }
        }

        // Veriyi listeye ekle
        liste[mevcut_adet].id = temp_id;
        
        printf("Isim: ");
        scanf("%s", liste[mevcut_adet].name);
        
        printf("Not: ");
        scanf("%f", &liste[mevcut_adet].grade);

        mevcut_adet++;
    }

    // Sonucu yazdir
    if (mevcut_adet > 0) {
        liste_yazdir(liste, mevcut_adet);
    } else {
        printf("Hic kayit yapilmadi.\n");
    }

    // Temizlik
    free(liste);
    printf("\nBellek temizlendi. Iyi gunler!\n");

    return 0;
}

/*tempId=; alıyoruz çünkü kullancı 0 girip çıkmak isterse ve listede bol yer olup olmadığını  kontrol etmemize ve
yeni bir kayıt oluşturmamıza gerek kalmaz. break ve while döngüsü o anda sonlanır */

/*
eğer realloc ile oluşturduğumuz yeni adresi listeye atasaydık geçici yerine liste pointer'ı NULL
olurdu ve eski verileri kaybederdik==memory leak olur
yeni-yer değerini listeye atayarak  liste artık büyütülmüş adresi tutar*/

//realloc ile katlanarak büyüme var(exponential growth)
 
 /*      POİNTER ARİTMETİĞİ İLE EKRANA BASTIRMA 
 // (liste + i) zaten bir adrestir, başına & koymaya gerek yoktur
 (liste + i)->id dediğimizde, o adresteki değere ulaşmış oluruz. scanf ise o değerin kendisini değil,
  o değerin saklandığı kutucuğun adresini ister. Bu yüzden başına & koyarız.
        
        printf("ID: ");
        scanf("%d", &((liste + i)->id)); 
        
        printf("Isim: ");
        scanf("%s", (liste + i)->name); // Dizi olduğu için zaten adres
        
        printf("Not: ");
        scanf("%f", &((liste + i)->grade));
    }
  
    //(liste + i) bir adrestir ama o tüm öğrenci bloğunun adresidir.


 */
 

          //TEK ÖĞRENCİ İÇİN
/*int main(){
    int temp_id;
    char temp_name[50];
    float temp_grade;

     Ogrenci *ogr1 = NULL;//kütüphaneden dönecek pointer 
    printf("lütfen id ,name ve grade değerlerini girniz.\n");
    
    if(scanf("%d %s %f", &temp_id, temp_name, &temp_grade) !=3 ){
        printf("hatali veya eksik giris yaptiniz.\n");
        return 1;
    }

    // KÜTÜPHANE FONKSİYONUNU ÇAĞIRMA
    // Kullanıcıdan aldığımız verileri kütüphaneye gönderiyoruz.
    // Kütüphane bizim yerimize malloc yapacak ve verileri içine yazacak.
    ogr1 = ogrenci_olustur(temp_id, temp_name, temp_grade);

    if (ogr1 == NULL) {
        printf("Bellek ayirma hatasi olustu!\n");
        return 1;
    }

    printf("\n--- Kayit Basarili ---\n");
    bilgileri_yazdir(ogr1);

    free(ogr1);
    printf("Bellek temizlendi, program kapatiliyor.\n");
    return 0;
}*/
