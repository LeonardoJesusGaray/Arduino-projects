#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h> //Libreria
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

virtuabotixRTC myRTC(6, 7, 8); // CLK-->6|DAT--->7|RST--->8
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F, 16, 2); //0x3F,16,2 para LCD 16x2
#include <DHT11.h>
int pin = 9;
DHT11 dht11(pin);
int err;
float temp, tempMin = 50, tempMax = -10 , humi;
void setup() {
 mySerial.begin(9600);
  Serial.begin(9600);
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();

  // Escribimos el Mensaje en el LCD.
  lcd.print("INICIANDO...");
  //----configurar hora------- hacer la primera vez que se configure el RTC, horario invierno
 // myRTC.setDS1302Time(10, 32, 21, 1, 21, 9, 2020); // SS, MM, HH, DW, DD, MM, YYYY
}

void loop() {

  if ((err = dht11.read(humi, temp)) == 0)
  {
    Serial.print("temperature:");
    Serial.print(temp);
    mySerial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else
  {
    VER("**ERROR**", 2, 0, 1);
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();
  }
  delay(DHT11_RETRY_DELAY); //delay for reread
  iA(temp);
  VER("t:", 10, 0, 0);
  VER(String(temp, 1), 12, 0, 0);
  VER(String(humi, 0), 12, 1, 0);
  VER("%", 15, 1, 0);
  VER("RH:", 9, 1, 0);
  VER("m", 0, 1, 0);
  VER(String (minima(), 0), 1, 1, 0);
  VER("M", 5, 1, 0);
  VER(String (maxima(), 0), 6, 1, 0);
  delay(1000);
}

void VER(String palabra, uint8_t columna, uint8_t fila, boolean limpiar )
{

  if (limpiar )lcd.clear();
  lcd.setCursor(columna, fila);
  lcd.print(palabra);


}

void iA(float t)
{
  lcd.clear();
  hora();
  if (t < 10)
  {
    VER("F ", 8, 0, 0);
  }
  else if (t >= 10 and t < 15)
  {
    VER("B", 8, 0, 0);
  }
  else if (t >= 15 and t < 25)
  {
    VER("N", 8, 0, 0);
  }
  else if (t >= 25)
  {
    VER("C", 8, 0, 0);
  }


}

float minima()
{
  if (temp != tempMin)
  {
    if (temp < tempMin)
    {
      tempMin = temp;
      return tempMin;
    }
  }
  else {
    return tempMin;
  }
}

float maxima()
{
  if (temp != tempMax)
  {
    if (temp > tempMax)
    {
      tempMax = temp;
      return tempMax;
    }
  }
  else {
    return tempMax;
  }
}
