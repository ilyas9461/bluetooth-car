//
#include "araba_islemler.h"
#include <Servo.h>  //  SERVO_PIN 3
#include <SoftwareSerial.h>

SoftwareSerial bl(2, 4); // rx,tx  arduino unoya göre
    //  UNO rx(2) <--  HC-05 tx
    //  UNO tx(4)-->  HC-05 rx
Servo servo;

//
negatif tamSayi t = 0;  //makro ile ardu değişken tanımlamasının türkçe ifade edilmesi.

int on_sensor = 0, z_ileri_calisma = 0, z_servo_calisma = 0;
unsigned long z_olc = 0, z_son = 0;
int hiz_arttir = ilk_hiz;
bool f_ileri_git = 0, f_yon = 0;
float arka_sensor = 0;
int pos = 0;
char bl_komut;
char komut;
byte bl_say = 0;
int _hiz = 0, don_hiz = 0;
byte ileri_geri = 0; // arabanaın ileri geri gitme durumnu kontrol eder 0: stop
                     // 1: ileri  2:geri
bool araba_dur = false;
bool araba_dur_ir1_sens = false;
bool bl_araba_dur = false;
bool servo_don = false;

//fonk. prototip
bool ServoDondur();
void komutYurutBluetoothRcController_Prog() ;
void servo_tara();
//

void setup() {

  Serial.begin(9600);  // PC ile haberleşme.
  bl.begin(9600);      // Bluetooth ile haberleşme

  pinMode(BUZZER_PIN , OUTPUT); //
  pinMode(ARKA_IR1_PIN, INPUT);
  servo.attach(SERVO_PIN);
  servo.write(180);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);
  pos = 30;
  
}
//
void loop() {
  // komutYurutArduinoBlueControl_Prog(); //PC seri porttan komut almak için
  komutYurutBluetoothRcController_Prog(); // Cep Tel. programdan almak için.

  if (bl.available() > 0) {
    komut = bl.read(); // readString();

    Serial.println(komut);
    // bl.flush();
    if (komut == 'X')
      servo_don = true;
    if (komut == 'x')
      servo_don = false;

    while (bl.available()) // Flush yerine seri buffer daha verimli boşaltılıyor
      bl.read();

    bl_araba_dur = false;

    z_olc = millis(); // çalışma zamanında geçen süreyi oku
  } else {
    // komut = 'y';
  }

  if (runEvery(100)) {
    on_sensor = OnSensorOku(onSensTrigPin, onSensEchoPin); // HC_SR04();

    if (on_sensor < ON_SENS_MIN_UZ && on_sensor > 0) {
      Serial.print("On:");
      Serial.println(on_sensor);
      komutBip();

      if (komut != GERI_BUTON) {
        ArabaDur();
        _hiz = 0;
      }
      araba_dur = true;
    } else
      araba_dur = false;

    if (!digitalRead(ARKA_IR1_PIN)) {
      Serial.println("Arka1:");
      komutBip();

      if (komut != ILERI_BUTON) {
        ArabaDur();
        _hiz = 0;
      }
      araba_dur_ir1_sens = true;
    } else
      araba_dur_ir1_sens = false;

    if (servo_don)
      servo_tara();
    else
      servo.write(90);
  }

} // loop sonu

void komutYurutBluetoothRcController_Prog()// bl ile kontrol 
{

  don_hiz = (int)(_hiz * 0.65);

  if (komut == BUZZER_ON) {
    komutBip();
  }

  if (komut == ILERI_BUTON && !araba_dur) {
    ArabaIleriAyarla();
    _hiz += 5;
    if (_hiz > MAX_HIZ)
      _hiz = MAX_HIZ;
    ArabaGit(_hiz);
  }

  if (komut == GERI_BUTON && !araba_dur_ir1_sens) {
    ArabaGeriAyarla();
    _hiz += 5;
    if (_hiz > MAX_HIZ)
      _hiz = MAX_HIZ;
    ArabaGit(_hiz);
  }
  if (komut == SOL_ILERI_BUTON) {
    ArabaSolaDon(don_hiz, 100);
    ArabaIleriAyarla();
  }
  if (komut == SAG_ILERI_BUTON) {
    ArabaSagaDon(don_hiz, 100);
    ArabaIleriAyarla();
  }
  if (komut == SOL_GERI_BUTON) {
    ArabaSagaDon(don_hiz, 100); //
    ArabaGeriAyarla();
  }

  if (komut == SAG_GERI_BUTON) {

    ArabaSolaDon(don_hiz, 100);
    ArabaGeriAyarla();
  }

  if (komut == STOP_BUTON) {
    ArabaDur();
    _hiz = 0;
  }
}

void komutYurutArduinoBlueControl_prog() {  //pc seri porttan kontrol
  if (komut == BUZZER_ON) {              
    komutBip();                          
  }

  if (komut == ILERI_BUTON) {
    ArabaIleriAyarla();
    _hiz += 10;
    if (_hiz > 100)
      _hiz = 100;
    ArabaGit(_hiz);
    ileri_geri = ARABA_ILERI_GIDIYOR;
  }

  if (komut == GERI_BUTON) {
    ArabaGeriAyarla();
    _hiz += 10;
    if (_hiz > 100)
      _hiz = 100;
    ArabaGit(_hiz);
    ileri_geri = ARABA_GERI_GIDIYOR;
  }
  if (komut == SOL_BUTON) {
    ArabaSolaDon(_hiz, 100);

    if (ileri_geri == ARABA_ILERI_GIDIYOR)
      ArabaIleriAyarla();
    if (ileri_geri == ARABA_GERI_GIDIYOR)
      ArabaGeriAyarla();
  }
  if (komut == SAG_BUTON) {
    ArabaSagaDon(_hiz, 100);

    if (ileri_geri == ARABA_ILERI_GIDIYOR)
      ArabaIleriAyarla();
    if (ileri_geri == ARABA_GERI_GIDIYOR)
      ArabaGeriAyarla();
  }
}

void servo_tara() {
  if (on_sensor > ON_SENS_MIN_UZ) {
    if (!f_yon) {
      pos += 12;
      if (pos >= 150) {
        f_yon = 1;
        pos = 150;
      }
    }
    if (f_yon) {
      pos -= 12;
      if (pos <= 30) {
        f_yon = 0;
        pos = 30;
      }
    }
    servo.write(pos);
  }
}
//
bool ServoDondur() {
  do {
    on_sensor = OnSensorOku(onSensTrigPin, onSensEchoPin); // HC_SR04();
    if (!f_yon) {
      pos += 10;
      if (pos > 170)
        f_yon = 1;
    }
    if (f_yon) {
      pos -= 10;
      if (pos < 10)
        f_yon = 0;
    }
    servo.write(pos);
    delay(50);
  } while (on_sensor >  50); // Ön trafta cisim varsa taramayı bırak, yoksa tara...
}
////

// if ((millis() - z_olc > 300) && !araba_dur)
// {
//     if (komut == 'y')
//     {
//         ArabaDur();
//         ileri_geri = ARABA_DURUYOR;
//         _hiz = 0;
//         bl_araba_dur = true;
//     }
//     z_olc = millis(); // çalışma zamanında geçen süreyi oku
// }
