#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
String hizmetAd[4] = {"kopukleme", "yikama", "kurulama", "cilalama"};
int kalanHizmet[4] = {30, 50, 100, 20};
int hizmetFiyat[4] = {15, 10, 5, 50};
int hizmetID[4] = {1, 2, 3, 4};
int kasa[5]={20,20,10,30,5};
int butonSayisi = 7;
int butonDizisi[7] ;
boolean butonKontrol[7];
int yuklenenMiktar = 0, bitisSayac = 0;
int yuklenen[5] = {0,0,0,0,0};
int odenecekMiktar = 0;
int kirmiziLED = 10, yesilLED = 9;
int sayac[4] = {0, 0, 0, 0};
int randomSayi;
int sayacReset[4]={0,0,0,0};
int yuzluk=0,ellilik=0,yirmilik=0,onluk=0,beslik=0;
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < butonSayisi; i++) {
    butonDizisi[i] = i + 2; // 2 butonların başlangıç pinidir.
  }
  for (int i = 0; i < butonSayisi; i++) {
    pinMode(butonDizisi[i], INPUT);
  }
  pinMode(kirmiziLED, OUTPUT);
  pinMode(yesilLED, OUTPUT);
  randomSeed(5);
 lcd.begin(16, 2);
}

void loop() {
randomSayi=random(1,5);
  if (digitalRead(butonDizisi[0]) == HIGH) {
    if (bitisSayac == 0) {
      yuklenenMiktar += 5;
      yuklenen[0]++;
      kasa[0]++;
    }
    else if (bitisSayac == 1) {
      odenecekMiktar += hizmetFiyat[0];
      kalanHizmet[0] = kalanHizmet[0] - 1;
      sayac[0] = sayac[0] + 1;
      sayacReset[0]=sayacReset[0]+1;


    }
    delay(200);
  }
  else if (digitalRead(butonDizisi[1]) == HIGH) {
    if (bitisSayac == 0) {
      yuklenenMiktar += 10;
          yuklenen[1]++;
      kasa[1]++;
    }
    else if (bitisSayac == 1) {
      odenecekMiktar += hizmetFiyat[1];
      kalanHizmet[1] = kalanHizmet[1] - 1;
      sayac[1] = sayac[1] + 1;
        sayacReset[1]=sayacReset[1]+1;
    }
    delay(200);
  }

  else if (digitalRead(butonDizisi[2]) == HIGH) {
    if (bitisSayac == 0) {
      yuklenenMiktar += 20;
          yuklenen[2]++;
      kasa[2]++;
    }
    else if (bitisSayac == 1) {
      odenecekMiktar += hizmetFiyat[2];
      kalanHizmet[2] = kalanHizmet[2] - 1;
      sayac[2] = sayac[2] + 1;
        sayacReset[2]=sayacReset[2]+1;
    }
    delay(400);

  }
  else if (digitalRead(butonDizisi[3]) == HIGH) {
    if (bitisSayac == 0) {
      yuklenenMiktar += 50;
          yuklenen[3]++;
      kasa[3]++;
    }
    else if (bitisSayac == 1) {
      odenecekMiktar += hizmetFiyat[3];
      kalanHizmet[3] = kalanHizmet[3] - 1;
      sayac[3] = sayac[3] + 1;
        sayacReset[3]=sayacReset[3]+1;
    }
    delay(400);
  }
  else if (digitalRead(butonDizisi[4]) == HIGH) {
    if (bitisSayac == 0) {
      yuklenenMiktar += 100;
          yuklenen[4]++;
           kasa[4]++;
         delay(400);
    }
 
  }
  else if (digitalRead(butonDizisi[5]) == HIGH) {
    bitisSayac++;
    if (bitisSayac == 1) {
      Serial.println(String(yuklenenMiktar) + " TL Para Attiniz");
      lcd.clear();
     lcd.setCursor(0, 0);
      lcd.print(String(yuklenenMiktar) + " TL Para Attiniz");
     
    }
    else if (bitisSayac == 2) {
      if(odenecekMiktar<=yuklenenMiktar){

      Serial.println("Random Sayi: " +String(randomSayi));
      Serial.println("odenecek hizmet bedeli: " + String(odenecekMiktar));
      if (randomSayi == 2) {
        digitalWrite(kirmiziLED, HIGH);
        digitalWrite(yesilLED, LOW);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PARA SIKISTI");
        Serial.println("HATA: PARA SIKISTI. ISLEMLER GERI ALINIYOR");
       for(int i=0;i<4;i++){
        kalanHizmet[i]+=sayac[i];
       }
             for(int i=0;i<5;i++){
         kasa[i]-=yuklenen[i];}

      }


      else {
        digitalWrite(yesilLED, HIGH);
        digitalWrite(kirmiziLED, LOW);
 
      int paraUstu=yuklenenMiktar-odenecekMiktar;
    Serial.println(" PARA USTU "+String(paraUstu));
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("PARA USTU");
    lcd.setCursor(4,1);
    lcd.println(paraUstu);
       yuzluk= paraUstu/100;
       if(kasa[4]>=yuzluk){
       paraUstu-=100*yuzluk;
      }
      else if(kasa[4]<yuzluk && kasa[4]!=0){
         paraUstu-=100*kasa[4];
         yuzluk=kasa[4];
      }
      else {
        yuzluk=0;
      }
      ellilik=paraUstu/50;
      if(kasa[3]>=ellilik){
       paraUstu-=50*ellilik;
      }
      else if(kasa[3]<ellilik && kasa[3]!=0){
         paraUstu-=50*kasa[3];
         ellilik=kasa[3];
      }
      else {
        ellilik=0;
      }
     yirmilik=paraUstu/20;
         if(kasa[2]>=yirmilik){
       paraUstu-=20*yirmilik;
      }
      else if(kasa[2]<yirmilik && kasa[2]!=0){
         paraUstu-=20*kasa[4];
         yirmilik=kasa[2];
      }
      else {
       yirmilik=0;
      }
      onluk=paraUstu/10;
          if(kasa[1]>=onluk){
       paraUstu-=10*onluk;
      }
      else if(kasa[1]<onluk && kasa[1]!=0){
         paraUstu-=10*kasa[1];
         onluk=kasa[1];
      }
      else {
       onluk=0;
      } 
      beslik=paraUstu/5;
        if(kasa[0]>=beslik){
       paraUstu-=5*beslik;
      }
      else if(kasa[0]<beslik && kasa[0]!=0){
         paraUstu-=5*kasa[0];
         beslik=kasa[0];
      }
      else {
        beslik=0;
      }

     if(paraUstu!=0){
      Serial.println("KASADA YETERLI BANKNOT YOK. ISLEMLER GERI ALINIYOR");
           lcd.clear();
      lcd.setCursor(0,0);
      lcd.println("YETERLI BANKNOT");
      lcd.setCursor(0,1);
      lcd.println("YOK");
 
      for(int i=0;i<5;i++){
        kasa[i]-=yuklenen[i];
      }
      for(int i=0;i<4;i++){
        kalanHizmet[i]+=sayac[i];
      }
     }
     
else if((kalanHizmet[0]<0 || kalanHizmet[1]<0 || kalanHizmet[2]<0  || kalanHizmet[3]<0 )&& paraUstu==0){
  Serial.println("HIZMET YETERSIZ");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HIZMET YETERSIZ");
    for(int i=0;i<5;i++){
        kasa[i]-=yuklenen[i];
      }
      for(int i=0;i<4;i++){
        kalanHizmet[i]+=sayac[i];
      }
}
     
     
     else{
      kasa[4]-=yuzluk;
      kasa[3]-=ellilik;
      kasa[2]-=yirmilik;
      kasa[1]-=onluk;
      kasa[0]-=beslik;
      Serial.println("Para Ustunuz Veriliyor :");
      if(yuzluk!=0){
        Serial.println(String(yuzluk)+ " tane 100 TL");
      }
       if(ellilik!=0){
        Serial.println(String(ellilik)+ " tane 50 TL");
      }
       if(yirmilik!=0){
        Serial.println(String(yirmilik)+ " tane 20 TL");
      }
       if(onluk!=0){
        Serial.println(String(onluk)+ " tane 10 TL");
      }
       if(beslik!=0){
        Serial.println(String(beslik)+ " tane 5 TL");
      }
     }}

  for (int i = 0; i < 4; i++) {
        Serial.println(String (hizmetID[i]) + " , " + String (hizmetAd[i]) +
                       " , " + String(kalanHizmet[i]) + " , " + String(hizmetFiyat[i]));                    

      }

      Serial.println("KASA BILGISI");
      for(int i=0;i<5;i++){
        Serial.print(String(kasa[i])+" , ");
      }
      Serial.println("\n");
     }
     
      
     
     


else{
  Serial.println("YUKLENEN MIKTAR YETERSIZ. ISLEMLER GERI ALINIYOR ");
  lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Yuklenen Miktar");
              lcd.setCursor(4, 1);
              lcd.print("Yetersiz");
              
  for(int i=0;i<5;i++){
    kasa[i]-=yuklenen[i];
  }
  for(int i=0;i<4;i++){
    kalanHizmet[i]+=sayac[i];
  }

   for (int i = 0; i < 4; i++) {
        Serial.println(String (hizmetID[i]) + " , " + String (hizmetAd[i]) +
                       " , " + String(kalanHizmet[i]) + " , " + String(hizmetFiyat[i]));                    

      }
      
      Serial.println("KASA BILGISI");
      for(int i=0;i<5;i++){
        Serial.print(String(kasa[i])+" , ");
      }
      Serial.println("\n");
}

      
Serial.println("\n");
      bitisSayac = 0;
      yuklenenMiktar = 0;
      odenecekMiktar = 0;
      for (int i = 0; i < 4; i++) {
        sayac[i] = 0;
      }
         for (int i = 0; i < 5; i++) {
        yuklenen[i] =0;
      }
      
    }  
    delay(400);
  }
  else if (digitalRead(butonDizisi[6]) == HIGH) {
    lcd.clear();
   /*
    kalanHizmet[0] = kalanHizmet[0] + sayacReset[0];      
    kalanHizmet[1] = kalanHizmet[1] + sayacReset[1];
    kalanHizmet[2] = kalanHizmet[2] + sayacReset[2];
    kalanHizmet[3] = kalanHizmet[3] + sayacReset[3];*/
    
for(int i=0;i<4;i++){
  kalanHizmet[i]+=sayac[i];
}
      
          for(int i=0;i<5;i++){
         kasa[i]-=yuklenen[i];}
    for(int i=0;i<4;i++){
      sayac[i]=0;
    }
     for (int i = 0; i < 5; i++) {
        yuklenen[i] =0;
      }
    bitisSayac = 0;
    odenecekMiktar = 0;
    yuklenenMiktar = 0;
    Serial.println("Resete bastiniz");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RESETE BASTINIZ");
    delay(400);
  }

}
