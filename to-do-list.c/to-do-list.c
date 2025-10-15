#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sabitlerimizi tanımlayalım
#define MAX_ACIKLAMA_UZUNLUGU 256
#define BASLANGIC_KAPASITESI 10
#define DOSYA_ADI "gorevler.txt"

//görev yapımızı struct ile tanımladık
typedef struct  Task{
    int Id;
    char aciklama[MAX_ACIKLAMA_UZUNLUGU];
    int oncelik;
    int durum;// 0=devam ediyor,1=tamamlandı
}Task;

//Dizi, aynı türden verileri bellekte arka arkaya saklayan bir veri yapısıdır
//Bu bir dizi değil, bir pointer'dır. Başlangıçta bellekte hiçbir yeri göstermiyor (NULL). main fonksiyonunda malloc ile ona yer ayıracağız. Bu sayede
// programımız 100 veya 1000 gibi sabit bir limitle kısıtlı kalmaz
Task* gorevler =NULL;//Görevleri tutacak dinamik dizimiz bir pointer
int gorevSayisi=0;//sayacı 0 dan başlattık,bize kaç tane görev yapıldığını gösterir
int kapasite = 0; //Dizinin o an en fazla kaç görev tutabildiğini belirtir. gorevSayisi bu değere ulaştığında realloc ile kapasiteyi artırırız.

void MenuGoster();
void gorevEkle();
void gorevleriFiltreliListele(int filtre);
void goreviIsaretle();
void dosyayaKaydet();
void dosyadanYukle();
void kapasiteyiArtir();

int main(){
  kapasite =BASLANGIC_KAPASITESI;
   gorevler =(Task *)malloc(kapasite*sizeof(Task));//görevler task pointeri tipinde 
   if(gorevler == NULL){
       printf("error:Bellekte yer ayrilmadi!");
       return 1;//hata kodu ile çık
   }
//eski görev varsa dosyadan belleğe yğkle
//şimdi çağrılmasının nedeni :Kalıcılık (Persistence).böylece kapatılıp açıldığında hiç kapanmamış gibi davranmasını,yeni verileri unutmamasını isterim.
   dosyadanYukle();
   int secim;
//kullancı çıkmak isteyene kadar secim yaptırır
   while(1){
     MenuGoster();
     printf("lütfen secim yapiniz (1-6) :");
     //Eğer scanf fonksiyonu 1 tane öğeyi başarıyla okuyup atayamadıysa (yani kullanıcı sayı dışında bir şey girdiyse),
     // o zaman bu if bloğunun içindeki kodları çalıştır
       if(scanf("%d",&secim) != 1){
           printf("Gecersiz giris! Lutfen bir sayi girin.\n");
           while(getchar() != '\n'); // Hatalı girişi temizle
           continue; // Döngünün başına dön
        }
        while(getchar() != '\n');// Sayıdan sonra kalan Enter karakterini temizle
        switch(secim){
            case 1:
             gorevEkle();
             break;
            case 2:
             gorevleriFiltreliListele(-1);//-1 hepsini gösterir
             break;
            case 3:
             gorevleriFiltreliListele(0);//0 devam edenleri(yapılmayanları)göster
             break;
             case 4:
             gorevleriFiltreliListele(1);//tamamlananları göster
             break;
             case 5:
             goreviIsaretle();
            break;
            case 6:
             printf("program kapatiliyor \n");
             dosyayaKaydet();
             free(gorevler);// Ayrılan belleği sisteme geri ver.
             return 0;
            default :
             printf("geçersiz secim !!");
        }
   }return 0;
}

void MenuGoster(){
    printf("\n--- YAPILACAKLAR LISTESI ---\n");
    printf("1. Yeni Gorev Ekle\n");
    printf("2. Tum Gorevleri Listele\n");
    printf("3. Devam Eden Gorevleri Listele\n");
    printf("4. Tamamlanan Gorevleri Listele\n");
    printf("5. Gorevi Tamamlandi Olarak Isaretle\n");
    printf("6. Cikis\n");
    printf("---------------------------\n");
}

void kapasiteyiArtir(){
    kapasite*=2;
    Task *gecici_pointer = (Task*)realloc(gorevler,kapasite*sizeof(Task));
    if(gecici_pointer == NULL){
        printf("Error: Bellek genişletilemedi");
        dosyayaKaydet();
        free(gorevler);
        exit(1); // Programı acil olarak sonlandır
    }
gorevler = gecici_pointer; // Başarılı ise yeni bellek adresini al
}

void gorevEkle(){
    if(gorevSayisi >= kapasite ){
        printf("kapasite doldu,artiriliyor \n");
        kapasiteyiArtir();
    }
    Task yeniGorev;
// Benzersiz bir ID oluştur: son görevin ID'sinin bir fazlası
//-1 yapmamızın nedeni dizilerin 0. indeksten başlaması.sondaki 1 ise dizi boştur ve ilk görev olur
    yeniGorev.Id=gorevSayisi >0 ? gorevler[gorevSayisi -1].Id +1 : 1;
    
    printf("gorevi giriniz:");
    fgets(yeniGorev.aciklama, MAX_ACIKLAMA_UZUNLUGU, stdin);
//fgets tüm satırı okur ve sona \n ekler.bunu silmemiz gerek
//fgets okuduğu  metni  yeniGorev.aciklama ya kaydeder
//stdin=ile kullanıcıdan giriş alırız
//STRCSPN ==String'in içindeki \n karakterini bulur ve onu string'in sonu
// anlamına gelen \0 ile değiştirerek string'i temizler.
    yeniGorev.aciklama[strcspn(yeniGorev.aciklama, "\n")] = 0;
    printf("Oncelik seviyesini girin (1-Yuksek, 2-Orta, 3-Dusuk): ");
    scanf("%d", &yeniGorev.oncelik);
    while(getchar() != '\n');
    yeniGorev.durum = 0; // Yeni görev her zaman "Devam Ediyor" olarak başlar.
//görevSayısı bir sonraki boş kutunun numarasını verir    
    gorevler[gorevSayisi]=yeniGorev;
    gorevSayisi++;
    printf("Gorev basariyla eklendi!\n");
    dosyayaKaydet(); // Her eklemeden sonra dosyayı güncelle.
 
}

void gorevleriFiltreliListele(int filtre){
    char* baslik ="---GOREVLER---";
    if(filtre== 0) baslik ="---DEVAM EDEN GOREVLER---";
    else if(filtre == 1) baslik ="---TAMAMLANAN GOREVLER---";
    else baslik ="---TUM GOREVLER---";
    printf("\n%s\n",baslik);

    int gosterilenGorevSayisi=0;
    for(int i=0;i<gorevSayisi;i++){
        if (filtre ==-1 || gorevler[i].durum==filtre){
            printf("ID:%-3d | durum:[%-12s] | oncelik:%d | aciklama:%s \n",
                    gorevler[i].Id,(gorevler[i].durum ==1 ? "tamamlandi": "devam ediyor"),
                    gorevler[i].oncelik,gorevler[i].aciklama  );
           gosterilenGorevSayisi ++;
        }
    }
    if(gosterilenGorevSayisi==0){
        printf("gösterilecek görev yok.\n");
    }
}
void goreviIsaretle(){
    int id;
    printf("Tamamlandi olarak isaretlemek istediginiz gorevin ID'sini girin: ");
    scanf("%d", &id);
    while(getchar()!='\n');
    int bulundu =0;
    for(int i=0;i<gorevSayisi;i++){
        if(gorevler[i].Id==id){
            gorevler[i].durum =1;//tamamlandı olarak işaretlenir
            bulundu =1;
            printf("Id %d olan gorev tamamlandi olarak işaretlendi. \n",id);
            dosyayaKaydet();
            break;//görevi bulduktan sonra döngüden çık
        }
    }
    if(!bulundu){
        printf("Girdiginiz ID'ye sahip bir gorev bulunamadi.\n");
    }
}

void dosyayaKaydet(){
    FILE *dosya=fopen(DOSYA_ADI ,"w");//yazma modunda açalım
    if(dosya == NULL){
        printf("error:%s dosyasi açilamadi",DOSYA_ADI );
        return;
    }

//tüm görevleri dosyaya yazalım
for(int i=0;i<gorevSayisi;i++){
    fprintf(dosya,"%d,%d,%d,%s\n",gorevler[i].Id,gorevler[i].oncelik,gorevler[i].durum,gorevler[i].aciklama);
}
fclose(dosya);
}

void dosyadanYukle(){
     FILE *dosya = fopen(DOSYA_ADI, "r"); // "r": Okuma modu.
    if (dosya == NULL) {
        // Dosya yoksa bu bir hata değil, program ilk kez çalışıyor.
        printf("Gorev dosyasi bulunamadi, yeni bir tane olusturulacak.\n");
        return;
    }

    while(!feof(dosya)){
        if(gorevSayisi>=kapasite){
            kapasiteyiArtir();//dosyadan yüklerkende yerimiz olması gerek
        }

        int sonuc =fscanf(dosya,"%d,%d,%d,%[^\n]\n",&gorevler[gorevSayisi].Id,&gorevler[gorevSayisi].oncelik, &gorevler[gorevSayisi].durum,&gorevler[gorevSayisi].aciklama);
    
         
        if (sonuc == 4) { // Eğer 4 eleman da başarıyla okunduysa
            gorevSayisi++;
        }
    }fclose(dosya);
}