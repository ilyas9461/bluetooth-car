//
#include <Arduino.h>

//ARDUINO komutları TÜRKÇE makro tanımlamaları
#define CIKIS OUTPUT
#define eger if
#define degilse else
#define dongu for
#define tamSayi int
#define negatif signed
#define pozitif unsigned
//#define dahil #include //direktifler olmuyorrrrr
#define bekle(sure) delay(sure)

//Motor Surucu L298 için PIN tanımlamaları.
#define ENA 5 // MotorA(Sol motor) için PWM yani hız girişi
#define IN1 8      // A Motoru için yönlendirme girişi 1.
#define IN2 7 // A Motoru için yönlendirme girişi 2.

//Motor için komutlar:    ENA           IN1     IN2
//        Motor aktif :   HIGH(PWM)      x       x
//        Motor pasif :   LOW            x       x
//        Yön1        :   HIGH(PWM)      LOW    HIGH
//        Yön2        :   HIGH(PWM)      HIGH   LOW
//        Boşta       :                  LOW    LOW
//        Fren        :                  HIGH   HIGH

#define ENB 6       //sağ motor
#define IN3 10
#define IN4 9

#define onSensTrigPin 12
#define onSensEchoPin 11
#define ON_SENS_MIN_UZ  30 //cm cinsinden mesafe

#define arkaSensTrigPin A0
#define arkaSensEchoPin A1

#define SERVO_PIN 3

#define BUZZER_PIN  13
#define komutBip()  bipp(10,2,BUZZER_PIN)  //sure, sayı, pin
#define komutHata() bipp(5,100,BUZZER_PIN)

#define ILERI_BUTON     'F' 
#define GERI_BUTON      'B' 
#define SOL_BUTON       'L'
#define SOL_ILERI_BUTON 'G'
#define SOL_GERI_BUTON  'H'
#define SAG_BUTON       'R' 
#define SAG_ILERI_BUTON 'I' 
#define SAG_GERI_BUTON  'J'
#define STOP_BUTON      'S'
#define LIGHT_ON        'W'
#define LIGHT_OFF       'w'
#define BUZZER_ON       'V'
#define BUZZER_OFF      'v'

#define STOP_ALL        'D'

#define ARABA_DURUYOR       0
#define ARABA_ILERI_GIDIYOR 1
#define ARABA_GERI_GIDIYOR  2

#define derece90 90 //Mekanik yapıya göre...
#define ilk_hiz 150
#define MAX_HIZ 150  // 0-255 arası olabilir. analogWrite komutu 8bit(0-255) PWM oluşturu.
#define ARKA_IR1_PIN A0
//

#define EgimSensOku() digitalRead(egimSensPin)  //makro tanımlama.,

//Araba komutları için Makro tanımlamaları:

#define ArabaMotorPinKurulum() pinMode(ENA,CIKIS); pinMode(ENB,CIKIS); pinMode(IN1,CIKIS); pinMode(IN2,CIKIS);pinMode(IN3,CIKIS);pinMode(IN4,CIKIS);
#define SolMotorBosta() digitalWrite(IN1,LOW);digitalWrite(IN2,LOW);
#define SagMotorBosta() digitalWrite(IN3,LOW);digitalWrite(IN4,LOW);
#define ArabaBosta() SolMotorBosta();SagMotorBosta()
//
#define SolMotorFren() digitalWrite(IN1,HIGH);digitalWrite(IN2,HIGH);
#define SagMotorFren() digitalWrite(IN3,HIGH);digitalWrite(IN4,HIGH);
#define ArabaFren() SolMotorFren();SagMotorFren();

#define ArabaDur() digitalWrite(ENA,LOW); digitalWrite(ENB,LOW);
#define ArabaDurBekle(sure) digitalWrite(ENA,LOW); digitalWrite(ENB,LOW);delay(sure);

#define SolMotorIleriAyarla() digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
#define SagMotorIleriAyarla() digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
#define ArabaIleriAyarla() SolMotorIleriAyarla();SagMotorIleriAyarla();

#define SolMotorGeriAyarla() digitalWrite(IN1,HIGH);digitalWrite(IN2,LOW);
#define SagMotorGeriAyarla() digitalWrite(IN3,HIGH);digitalWrite(IN4,LOW);
#define ArabaGeriAyarla() SolMotorGeriAyarla();SagMotorGeriAyarla();

#define ArabaSolaDon(hiz,sure) SolMotorGeriAyarla();SagMotorIleriAyarla();ArabaGitBekle(hiz,sure);
#define ArabaSagaDon(hiz,sure) SagMotorGeriAyarla();SolMotorIleriAyarla();ArabaGitBekle(hiz,sure);

#define SolMotorGit(pin,hiz) analogWrite(pin,hiz);
#define SagMotorGit(pin,hiz) analogWrite(pin,hiz);

#define ArabaGit(hiz)  {analogWrite(ENA,hiz);analogWrite(ENB,hiz);}
#define ArabaGit(hiz) SolMotorGit(ENA,hiz);SagMotorGit(ENB,hiz);
#define ArabaGitBekle(hiz,sure)  {ArabaGit(hiz);delay(sure);}

//Fonksiyonlara ait tanımlamalar:
//Bunlar aynı isimdeki .cpp uzantılı dosyada bulunan fonksiyonlardır.
//.cpp uzantılı dosyada "Class" da varsa tanımlaması burada oluşturulur kod ve fonksiyonları .cpp uzantılı dosysada yazılır.
////////////////////
//void ArabaMotorPinKurulum();
//void SolMotorBosta();
//void SagMotorBosta();
//void ArabaDur();
//void ArabaDurBekle(int sure);
//void ArabaIleriAyarla();
//void ArabaGeriAyarla();
//
//void SolMotorGit(int hiz);
//void SagMotorGit(int hiz);
//void ArabaGit(int hiz);
//void ArabaGitBekle(int hiz,int sure);
//void ArabaSolaDon(int hiz,int sure);
//void ArabaSagaDon(int hiz,int sure);
/////////////////////////////

int HC_SR04(int trigPin,int echoPin);
float sharp_2y0a02();
float gerilim_olc(int an_pin);
void bipp(int sure,int sayi,int pin);
boolean runEvery(unsigned long interval);

//#define ArkaSensorOku() sharp_2y0a02();
#define ArkaSensorOku(pTrigArkaSens,pEchoArkaSens) HC_SR04(pTrigArkaSens,pEchoArkaSens);
#define OnSensorOku(pTrigOnSens,pEchoOnSens) HC_SR04(pTrigOnSens,pEchoOnSens);
