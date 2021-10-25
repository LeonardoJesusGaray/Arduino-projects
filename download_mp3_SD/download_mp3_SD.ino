/**
   StreamHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>
#include "FS.h"
#include "SD_MMC.h"


#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;
File file;
long tini = 0, tfin = 0;
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void setup() {

  USE_SERIAL.begin(115200);
  if (!SD_MMC.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD_MMC.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  wifiMulti.addAP("SoyMomoRD", "soymomo2");
  file = SD_MMC.open("/winer.mp3", FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  file.close();
}

void loop() {
  // wait for WiFi connection
  if ((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");

    // configure server and url
    http.begin("https://soymomoboxleo.s3.us-east-2.amazonaws.com/track002.mp3");
    //http.begin("192.168.1.12", 80, "/test.html");

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {

        // get lenght of document (is -1 when Server sends no Content-Length header)
        int len = http.getSize();

        // create buffer for read
        uint8_t buff[1024] = { 0 };

        // get tcp stream
        WiFiClient * stream = http.getStreamPtr();



        file = SD_MMC.open("/winer.mp3", FILE_APPEND);
        if (!file) {
          Serial.println("Failed to open file for appending");
          return;
        }
        int count = 0;
        while (http.connected() && (len > 0 || len == -1)) {
          //  count += 1;
          size_t size = stream->available();
          if (size) {
            tini = micros();
            uint8_t c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
            tfin = micros();
             file.write(buff, sizeof(buff));
            USE_SERIAL.println(String(tfin - tini));
           
            // USE_SERIAL.println(len / count);
            if (len > 0) {
              len -= c;
            }
          }
        }

        USE_SERIAL.println();
        USE_SERIAL.print("[HTTP] connection closed or file end.\n");


      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    file.close();
    http.end();
  }

  delay(10000);
}
