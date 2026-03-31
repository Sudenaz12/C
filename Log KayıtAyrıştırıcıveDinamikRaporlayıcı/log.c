#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "log.h"

LogKaydi* log_ayristir(const char *satir){

    //genel log için yer
    LogKaydi* ayrilan = (LogKaydi*)malloc( sizeof(LogKaydi));
    if( ayrilan == NULL){
        printf("bellek ayrilmadi.\n");
        return  NULL;
    }
    char *ilk_tire=strchr(  satir,'-');
    char *son_tire = strrchr(satir, '-');
    char *ikinci_tire = strchr(ilk_tire + 1, '-');

    //mesaj kısmı son tireden sonra başlar
    int mesaj_length = strlen(son_tire +1);
    //mesaj için yer ayır ,mesaj char pointrı tipinde,+1 yap satır sonunu belirtir
    ayrilan->mesaj =( char*)malloc((mesaj_length +1)*sizeof(char));

    if (ayrilan->mesaj != NULL) {
        // Mesajı kopyala
        strcpy(ayrilan->mesaj, son_tire + 1);
    }
    int type_length= ikinci_tire -(ilk_tire +1);
    strncpy(ayrilan -> type,ilk_tire +1 ,type_length);
    ayrilan->type[type_length]='\0';

    int ip_length = son_tire -(ikinci_tire +1);
    strncpy(ayrilan -> ip_addres ,ikinci_tire +1 ,ip_length);
    ayrilan->ip_addres[ip_length]='\0';

    int date_length= ilk_tire-satir;
    strncpy(ayrilan ->date,satir,date_length);//satirden başlayip yazar
    ayrilan->date[date_length]='\0';

    return ayrilan;
}