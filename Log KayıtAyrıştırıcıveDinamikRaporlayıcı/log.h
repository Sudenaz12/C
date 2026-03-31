#ifndef log_h
#define log_h
#include <stdlib.h>

typedef struct {
 char date[12];
 char type[10];
 char ip_addres[16];
 char *mesaj;
}LogKaydi;

LogKaydi* log_ayristir(const char *satir);
#endif
//mesajın uzunluğu belli değil pointer yap ve malloc ile mesaj boyutu kadar yer ayır
//Veri yapısının olduğu header file dosyası