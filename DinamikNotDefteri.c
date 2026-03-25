#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASLANGIC_BOYUTU 10

 int main() {
    int kapasite = 10;
    char *notDefteri = (char*)malloc(sizeof(char) * kapasite);
    if (notDefteri == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    notDefteri[0] = '\0';
    char girdi[100];

    while (1) {
        printf("Lutfen bir not giriniz (cikmak icin 'exit'):\n");
        
        if (fgets(girdi, sizeof(girdi), stdin) == NULL) break;

 
        girdi[strcspn(girdi, "\n")] = '\0';

//  Eğer 'exit' ise döngüden çık
        if (strcmp(girdi, "exit") == 0) {
            break;
        }

        int gerekenBoyut = strlen(notDefteri) + strlen(girdi) + 2;

        if (gerekenBoyut > kapasite) {
            int eskiKapasite = kapasite;
           
           while(kapasite < gerekenBoyut){
                kapasite *= 2;
           }

            printf("Kapasite yetersiz, bellek buyutuluyor %d -> %d\n", kapasite, kapasite * 2);
            char *temp = (char*)realloc(notDefteri, kapasite);

            if (temp == NULL) {
                printf("Bellek buyutulemedi!\n");
                free(notDefteri);
                return 1;
            }
            notDefteri = temp;
        }

// strcat  IF  dışındaa çünkü her seferinde eklenir
        strcat(notDefteri, girdi);
        strcat(notDefteri, " ");
    }

    FILE *dosya = fopen("notlar.txt", "a");
    if (dosya == NULL) {
        printf("Dosya acilamadi\n");
    } else {
        fprintf(dosya, "\n[Oturum Kaydi ]: %s\n", notDefteri);
        fclose(dosya);
        printf("\nNotlar basariyla 'notlar.txt' dosyasina kaydedildi.\n");
    }

    free(notDefteri);
    notDefteri = NULL;

    return 0;
}