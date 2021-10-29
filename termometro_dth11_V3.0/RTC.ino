void hora()
{
  myRTC.updateTime();

  //------------- imprimir hora-----
  Serial.print("Fecha y hora actual: ");
  Serial.print(myRTC.dayofmonth); // Se puede cambiar entre día y mes si se utiliza el sistema Americano
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  lcd.setCursor(0, 0);
  if (myRTC.hours < 10)
  {
    lcd.print("0");
    lcd.print(myRTC.hours);
  }
  else {
    lcd.print(myRTC.hours);
  }

  lcd.print(":");
  lcd.setCursor(3, 0);
  if (myRTC.minutes < 10)
  {
    lcd.print("0");
    lcd.print(myRTC.minutes);
  }
  else {
    lcd.print(myRTC.minutes);
  }
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
 // delay(200);//---cambiar a 200 para instalacion final---
}
