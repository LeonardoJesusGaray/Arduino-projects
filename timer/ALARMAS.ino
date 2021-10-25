//---- veces que se repetirá el programa en el día---
void alarma1()
{

  if (myRTC.hours == 20 and myRTC.minutes == 37)
  {
    digitalWrite(bombaR, HIGH);
    lcd.setCursor(1, 0);
    lcd.print("bomba ON");
    lcd.setCursor(1, 1);
    lcd.print("MOTOR OFF");
    Serial.println("encendi bomba");

  }
  if (myRTC.hours == 20 and myRTC.minutes == 38)
  {
    digitalWrite(bombaR, LOW);
    delay(1000);
    digitalWrite(motorP, HIGH);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("bomba OFF");
    lcd.setCursor(1, 1);
    lcd.print("MOTOR ON");
    Serial.println("encendi motor");

  }

  if (myRTC.hours == 20 and myRTC.minutes == 39)
  {
    digitalWrite(bombaR, LOW);
    digitalWrite(motorP, LOW);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("bomba OFF");
    lcd.setCursor(1, 1);
    lcd.print("MOTOR OFF");
    Serial.println("encendi motor");

  }

}
