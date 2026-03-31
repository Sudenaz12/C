#include <stdlib.h>
#include <string.h>
 
#ifndef VERI_H
#define VERI_H

typedef struct {
    int id;
    char name_lastname[70];
    char department[50];
    float avg;
}Ogrenci;

Ogrenci* metni_ogrenciye_cevir(const char *ham_veri);

#endif 

