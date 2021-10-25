//---definiciones---
#define bombaR 12
#define motorP 11
#define bombaA 10
#define SET 3
#define OK 2

//---librerias----
#include <virtuabotixRTC.h> //Libreria
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

//-----objetos-----
virtuabotixRTC myRTC(6, 7, 8); // CLK-->6|DAT--->7|RST--->8
LiquidCrystal_I2C lcd(0x3F, 16, 2); //
//----variables----
byte nalarm;
int pos = 0, posiv = 1, alarmax, alarmay, minxRR = 1, minyR = 1, minxRRx, minyRy, motor = 0;
int alarmaxP, alarmayP, minxPP = 1, minyP = 1, minxPPx, minyPy;
int repetecionesR = 0, repetecionesRR = 0, repetecionesP = 0, repetecionesPP = 0;
boolean verano = true, bomR = true, setbomR = true, pasox = false, pasoy = false;
boolean  bomP = true, setbomP = true, pasoxP = false, pasoyP = false;

void setup()
{
  Serial.begin(9600);
  //---Salidas-------
  pinMode(motorP, OUTPUT);
  pinMode(bombaR, OUTPUT);
  //---entradas---
  pinMode(SET, INPUT_PULLUP);
  pinMode(OK, INPUT_PULLUP);
  delay(1000);
  //---configura LCD---
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();

  // Escribimos el Mensaje en el LCD.
  lcd.setCursor(2, 0);
  lcd.print("INICIANDO");
  lcd.setCursor(3, 1);
  lcd.print("SISTEMA");
  delay(1000);
  lcd.clear();

  //--- menu configuraciones
  if (digitalRead(OK) and !digitalRead(SET))
  {
    nalarm = 0;
    delay(100);
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
    delay(1000);
    configuracion();
    EEPROM.update(pos, nalarm);
    Serial.println("ALARM----- " + String(nalarm));

  }

  if (!digitalRead(SET) and !digitalRead(OK))
  {
    delay(100);
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
    delay(1000);
    horaverano();
    EEPROM.update(posiv, verano);
  }
  lcd.clear();

  //--- actualizacion Variables---
  EEPROM.get(pos, nalarm);
  EEPROM.get(posiv, verano);
  Serial.print(F("---N ALARMA---") );
  Serial.println(nalarm);
  Serial.print(F("----verano----"));
  Serial.println(verano);
  //----configurar hora------- hacer la primera vez que se configure el RTC, horario invierno
  //myRTC.setDS1302Time(30, 58, 13, 7, 29, 9, 2019); // SS, MM, HH, DW, DD, MM, YYYY

}

void loop()
{

  if (verano)
  {
    horaverano();
  }
  else
  {
    hora();

  }
  //alarma1();//alarma automatica

  //---funcion alarma configurable---
  if (nalarm == 5)// condicion para que opere en modo "manual".
  {
    if (bomR)//----REVISAR---- la idea es crear una condicion para evitar que ambas se enciendan.
    {
      manualR();
    }
    if (!bomR)
    {
      manualP();
    }
    Serial.println(F("-----Alarma 5"));

  }


  //-----funcion configurar horarios ON/OFF n-veces
  if (!digitalRead(SET))
  {
    delay(100);
    lcd.noBacklight();
    delay(1000);
    lcd.backlight();
    delay(500);
    ///----agregar opcion configurar todos o uno a las vez----
    selectmotor();
    //confAlarmaR();
    setbomR = true;
  }
}
