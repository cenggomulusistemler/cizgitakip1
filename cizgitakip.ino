
/*Sensörler */
const int sensorler[]={A0,A1,A2}; // A0 Sol sensör, A1 Orta Sensör, A2 Sag Sensor "CNY70".
int sensor[3];
const int maviled=38; //uçağın üzerindeki mavi led
const int kirmiziled=39; //uçağın kanatlarındaki kırmızı led
unsigned int sayac=0; //uçağın üstündeki mavi ledin yanıp sönmesi için sayac
int katsayi=1; //uçağın üzerindeki mavi ledin yanıp sönmesine karar verecek katsayı negatip veya pozitif

int sonDurum=1; //bu değişken uçak yoldan tamamen çıktığında son konumuna dönmesi için kullanılacak, default değei 1 hiç bir tarafa dönmeyeyaceğini belirtiyor, bu değer 0 veya 2 olduğunda dönme işlemi yapacak

/*Motor 1 */
const int solMotorIleri  = 34;  
const int solMotorGeri  = 35; 
/*Motor 2 */
const int sagMotorIleri  = 36; 
const int sagMotorGeri  = 37;



void setup()  
{
    pinMode(maviled, OUTPUT);// uçağın mavi ledine giden pin çıkış olarak atandı.
    pinMode(kirmiziled, OUTPUT);// uçağın kırmızı ledine giden pin çıkış olarak atandı.
    digitalWrite(kirmiziled,HIGH); //kırmızı led sürekli yanacağı için burada HIGH olarak belirlendi.
  /*Sensörler */
  for (int i=0;i<3;i++){
    pinMode(sensorler[i], INPUT);// sensörlerin pinleri giriş olarak atandı.
  }
      
  pinMode(solMotorIleri, OUTPUT); //Motorlara giden pinler çıkış olarak atandı
  pinMode(sagMotorIleri, OUTPUT);
  pinMode(solMotorGeri, OUTPUT);
  pinMode(sagMotorGeri, OUTPUT);

  digitalWrite(solMotorIleri, LOW); //Bütün motorlar başlangıçta dur oarak ayarlandı
  digitalWrite(sagMotorIleri, LOW);
  digitalWrite(solMotorGeri, LOW);
  digitalWrite(sagMotorGeri, LOW);
              
}

void loop()
{
   sayac=sayac+1;
  if(sayac%3000==0){
    katsayi=-katsayi;
    if(katsayi>0){
      digitalWrite(maviled, HIGH);} //uçağın üstündeki mavi led yanıyor
     else{
      digitalWrite(maviled,LOW);//uçağın üstündeki mavi led sönüyor
      } 
    }  
    if(sayac>60000)
    sayac=0;
    //
  for (int i=0;i<3;i++){
    if (analogRead(sensorler[i])>800)
      sensor[i]=1; //Sensorden gelen analog deger dijitale cevriliyor; Gelen sinyal beyaz ise 1, siyah ise 0
    else
      sensor[i]=0;
  }    
   
  if (sensor[0]==0) //Sol sensor siyahı gördü ise
  {
    sonDurum=0; // sondurum değişkenine 0 atanıyor
    hareket(0); //uçak sola dönüyor
  }  
  
  if (sensor[2]==0) //Sağ sensör siyahı gördü ise
  {
    sonDurum=2; // sondurum değişkenine 0 atanıyor
    hareket(2);//uçak sağa dönüyor
  }
  if (sensor[0]==1 && sensor[1]==0 && sensor[2]==1){ //yan seösörler beyazda orta sensör siyahta ise normal istediğimiz pozisyondadır
    sonDurum=1; //sondurum değişkenine 1 default değeri atanıyor yani sondurum değişkeni resetleniyor
    hareket(1); //uçak hiçbir tarafa dönmeden hareket ediyor
  }
  
  if (sensor[0]==1 && sensor[1]==1 && sensor[2]==1){ //Bütün sensörler beyaz algılıyorsa, uçak yoldan tamamen çıkmış demekdir
    hareket(sonDurum); //Yan sensörlerden en son hagisi siyahı görmüş ise o yöne doğru uçak dönerek yolu arıyor.
  }

}

void hareket(int deger){
  if (deger==0){
    digitalWrite(solMotorIleri, LOW); // Sol Motor Dur
    digitalWrite(sagMotorIleri, HIGH); //Sağ Motor Çalışıyor
  }
  if (deger==1){
    digitalWrite(solMotorIleri, HIGH); //Sol Motor Çalışıyor
    digitalWrite(sagMotorIleri, HIGH); //Sag Motor Çalışıyor
  }
  if (deger==2){
    digitalWrite(sagMotorIleri, LOW); //Sag Motor Dur
    digitalWrite(solMotorIleri, HIGH); //Sol Motor Çalışıyor
  }
  if (deger==3){
      digitalWrite(solMotorIleri, LOW); // Sol Motor Dur
      digitalWrite(sagMotorIleri, LOW); // Sağ Motor Dur
  }
}


