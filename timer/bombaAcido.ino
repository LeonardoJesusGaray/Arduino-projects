void bombaAon()
{

  Serial.println("alarma on");
  digitalWrite(bombaA, HIGH);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("BOMBA AC.");
  lcd.setCursor(1, 1);
  lcd.print("ON");
  Serial.println("encendi motor");
  delay(100);
}


void bombaAoff()
{
  Serial.println("alarma off");
  digitalWrite(bombaA, LOW);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("BOMBA AC.");
  lcd.setCursor(1, 1);
  lcd.print("OFF");
  Serial.println("apague motor");
  delay(100);
}
