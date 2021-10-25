//--funcion para seleccionar la cantidad de veces que se repetirá el modo auto en el dia--
void configuracion()//---OK--- numero de alarmas, guarda en eeprom
{
  long tinicio = millis();
  Serial.println("----MENU----");
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("MENU");
  lcd.setCursor(3, 1);
  lcd.print("ALARMAS");

  while (1)
  {

    long tfinal = millis();

    if ( tfinal - tinicio > 15000)
    {
      break;

    }

    if (!digitalRead(SET))// AL PRESIONAR SET AUMENTA ALARMAS
    {
      delay(200);
      nalarm++;
      if (nalarm > 5) // NUMERO DE ALARMAS PREESTABLECIDAS
      {
        nalarm = 0;

      }
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("ALARMAS");
      lcd.setCursor(7, 1);
      lcd.print(nalarm);
      Serial.println(nalarm);


    }
    if (!digitalRead(OK))// SI PRESIONA OK SALE DEL MENU
    {
      break;
    }

  }


}

//----funcion para seleccionar horario verano/invierno-----
void horarioVerano()//----OK----
{
  long tinicio = millis();
  Serial.println("----MENU HORARIO----");
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("HORARIO");
  lcd.setCursor(0, 1);
  lcd.print("INVIERNO/VERANO");

//---- al presionar SET navega entre verano/invierno----
  while (1)
  {
    long tfinal = millis();

    if ( tfinal - tinicio > 15000)
    {
      break;

    }

    if(!digitalRead(OK))
    {
      break;
      }

    if (!digitalRead(SET))
    {
      verano = !verano;

      if (verano)
      {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("HORARIO");
        lcd.setCursor(3, 1);
        lcd.print("VERANO");
        delay(300);
      }

      if (!verano)
      {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("HORARIO");
        lcd.setCursor(3, 1);
        lcd.print("INVIERNO");
        delay(300);
      }

    }

  }

}
