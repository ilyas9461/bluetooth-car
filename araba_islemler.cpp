//
#include "araba_islemler.h"

/////////// Araba işlemleri Fonksiyon Halinde
//void SolMotorBosta() {
//  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
//}
//void SagMotorBosta() {
//  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
//}
//void ArabaDur() {
//  digitalWrite(ENA, LOW); digitalWrite(ENB, LOW);
//}
//void ArabaDurBekle(int sure) {
//  digitalWrite(ENA, LOW); digitalWrite(ENB, LOW); delay(sure);
//}
//void ArabaIleriAyarla() {
//  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); //SolMotorIleriAyarla();
//  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); //SagMotorIleriAyarla();
//}
//void ArabaGeriAyarla() {
//  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); //SolMotorGeriAyarla();
//  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); //SagMotorGeriAyarla();
//}
//void ArabaMotorPinKurulum() {
//  pinMode(ENA, CIKIS); pinMode(ENB, CIKIS); pinMode(IN1, CIKIS); pinMode(IN2, CIKIS); pinMode(IN3, CIKIS); pinMode(IN4, CIKIS);
//}
//void SolMotorGit(int hiz) {
//  analogWrite(ENA, hiz);
//}
//void SagMotorGit(int hiz) {
//  analogWrite(ENB, hiz);
//}
//void ArabaGit(int hiz) {
//  SolMotorGit(hiz);
//  SagMotorGit(hiz);
//}
//void ArabaGitBekle(int hiz, int sure)  {
//  ArabaGit(hiz); delay(sure);
//}
//void ArabaSolaDon(int hiz, int sure) {
//  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); //SolMotorGeriAyarla();
//  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); //SagMotorIleriAyarla();
//  ArabaGitBekle(hiz, sure);
//}
//void ArabaSagaDon(int hiz, int sure) {
//  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); //SagMotorGeriAyarla();
//  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); //SolMotorIleriAyarla();
//  ArabaGitBekle(hiz, sure);
//}

/////////////////////////
int HC_SR04(int trigPin,int echoPin)
{
  //const int trigPin = 8;
  //const int echoPin = 12 ;
  long duration = 0;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  return duration / 29 / 2;
}

float sharp_2y0a02() {
#define VOLTS_PER_UNIT    .0049F        // (.0049 for 10 bit A-D) 
  float volts, proxSens;
  float cm;
  int sensorPin = A0; //analog pin 0
  for (int i = 0; i < 25; i++)proxSens = analogRead(sensorPin);
  volts = (float)proxSens * VOLTS_PER_UNIT; // ("proxSens" is from analog read)
  //inches = 23.897 * pow(volts,-1.1907); //calc inches using "power" trend line from Excel
  cm = 60.495 * pow(volts, -1.1904);    // same in cm
  //if (volts < .2) inches = -1.0;        // out of range
  //if(volts>2.5)cm=20;
  //if(volts<.4)cm=150;
  return cm;
}

float gerilim_olc(int an_pin) {
  return (float)(analogRead(an_pin) * 0.0049F * (30 / 10));
}

void bipp(int sure,int sayi,int pin)                              
{
   int a=0;
   for(a=0;a<sayi;a++)
   {
     digitalWrite(pin,HIGH);delay(sure/2);digitalWrite(pin,LOW);delay(sure/2); 
   }                                      
}//


boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}


