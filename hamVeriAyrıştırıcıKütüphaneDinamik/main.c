#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 #include "veri.h"
int main(){
//stack üzerinde kullanıcı girişini tutacak dizi oluşturduk
    char ham_veri[150]; 
    char ozet_metin[100];

    printf("Lutfen bilgileri giriniz (ID-Ad Soyad-Bolum-Ortalama):\n");
    fgets(ham_veri,sizeof(ham_veri),stdin);
//fgets sonundaki \n karakterini temizleriz
    ham_veri[strcspn(ham_veri, "\n")] = 0;

    Ogrenci  *ptr = metni_ogrenciye_cevir(ham_veri );
    if (ptr == NULL) {
        printf("Hata: Veri ayristirilamadi veya bellek doldu!\n");
        return 1;
    }

    strcpy(ozet_metin,ptr->name_lastname);
    strcat(ozet_metin, ",");
    strcat(ozet_metin ,ptr-> department);
    strcat(ozet_metin, " bolumu ogrencisidir.");

    printf("\n--- Ayrilan Bilgiler ---\n");
    printf("ID: %d\n", ptr->id);
    printf("Ad Soyad: %s\n", ptr-> name_lastname);
    printf("Bolum: %s\n", ptr-> department);
    printf("Ortalama: %.2f\n", ptr->avg);
    
    printf("%s\n", ozet_metin);

    free(ptr);
    printf("\nBellek temizlendi. Program sonlandiriliyor.\n");

    return 0;
}