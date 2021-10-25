//LIBRERIAS
#include <WiFi.h>

// WIFI
const char* ssid = "HUAWEI";
const char* password = "12345678";

// PUERTO
WiFiServer server(80);

// ENCABEZADO
String header;

// VARIABLES GLOBALES
String output15State = "off";
String pulsador="off";



// LED
const int output15 = 15;

//PULSADOR
const int pinpulsador=23; 

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

//------setup------------
void setup() {
  Serial.begin(115200);
  pinMode(output15, OUTPUT);
  digitalWrite(output15, LOW);
  pinMode(pinpulsador,INPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

//----LOOP--------
void loop(){

// VERIFICA EL ESTADO DEL PULSADOR 
  if(digitalRead(pinpulsador))
  {
    pulsador="on";
    
    }
    else{
      
       pulsador="off";
      
      }

 //---SERVIDOR ESP-------     
 web();
}
