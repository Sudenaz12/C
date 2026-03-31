#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "log.h"

int main(){
    char log_satir[100];
    printf("lütfen bir log satiri girin:\n");

    fgets(log_satir,sizeof(log_satir),stdin);
    // fgets ile gelen '\n' karakterini temizleyelim
    log_satir[strcspn(log_satir, "\n")] = 0;

    LogKaydi *sonuc = log_ayristir(log_satir);

    if (sonuc == NULL) {
        printf("Hata: Bellek ayrilamadi veya format yanlis!\n");
        return 1;
    }

    printf("\n--- LOG ANALIZI ---\n");
    printf("Tarih:  %s\n", sonuc->date);
    printf("Tip:    %s\n", sonuc->type);
    printf("IP:     %s\n", sonuc->ip_addres);
    printf("Mesaj:  %s\n", sonuc->mesaj);

    // Önce içteki dinamik alanı sil:
    free(sonuc->mesaj); 
    // Sonra ana yapıyı sil:
    free(sonuc);

    return 0;
}