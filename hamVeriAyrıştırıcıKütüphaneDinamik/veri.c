#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 #include "veri.h"

Ogrenci* metni_ogrenciye_cevir(const char *ham_veri){
    Ogrenci * ayrilan = (Ogrenci*)malloc(sizeof(Ogrenci));
    if (ayrilan  == NULL) return NULL;

//ıd en baştan başla ,ilk - dur
    ayrilan ->id = atoi(ham_veri);

 // 2. TİRELERİN KONUMU
    char *ilk_tire = strchr(ham_veri, '-');
    char *son_tire = strrchr(ham_veri, '-');

    if (ilk_tire == son_tire || ilk_tire == NULL) {
        printf("Hata: Gecersiz format!\n");
        return ayrilan;
    }

    //  En sondaki tireden sonrasını al.
    ayrilan->avg = atof(son_tire + 1);

    //   İSİM VE BÖLÜM (Orta Kısım)
    
    char *ikinci_tire = strchr(ilk_tire + 1, '-');
    if (ikinci_tire && ikinci_tire < son_tire) {
        // İsim: ilk_tire ile ikinci_tire arası
        int  name_len = ikinci_tire - (ilk_tire + 1);
        strncpy(ayrilan->name_lastname, ilk_tire + 1,  name_len);
        ayrilan->name_lastname[ name_len] = '\0';

        // Bölüm: ikinci_tire ile son_tire arası (Aradaki tüm tireler bölüme dahil olur)
        int department_len = son_tire - (ikinci_tire + 1);
        strncpy(ayrilan->department, ikinci_tire + 1, department_len);
        ayrilan->department[department_len] = '\0';
    }

  return ayrilan ;  
 }
/*iki pointerı birbirinde çıkardığımızda  aralarındaki karakter sayisini buluruz.bu strncpy için gereken uzunluğu verir*/

