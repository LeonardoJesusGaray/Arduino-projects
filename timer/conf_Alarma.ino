//--funcion para setear los tiempos de cada bomba--

void selectmotor()
{
  long tinicio = millis();
inicio:
  motor = 0;
  lcd.noBacklight();
  delay(1000);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SELECION");
  lcd.setCursor(4, 1);
  lcd.print("MOTOR");
  lcd.backlight();
  delay(500);
  Serial.println("----MENU----");


  while (1)
  {
    Serial.println("---Seleccione motor---");
    long tfinal = millis();

    if ( tfinal - tinicio > 60000)
    {
      lcd.clear();
      break;

    }

    if (!digitalRead(OK))
    {
      break;
    }
    if (!digitalRead(SET))
    {
      Serial.println("----SET motor----");

      motor++;
///**************** CONFIGURA TIEMPOS MOTOR PICADOR**********
      if (motor == 1)
      { 
        long tinicio = millis();
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("MOTOR");
        lcd.setCursor(3, 1);
        lcd.print("PICADOR");
        delay(200);
        while (1)//-------------revisar
        {
          long tfinal = millis();

          if ( tfinal - tinicio > 5000)
          {
            lcd.clear();
            goto inicio;

          }

          if (!digitalRead(OK))
          {
            delay(500);
            lcd.noBacklight();
            delay(1000);
            lcd.backlight();
            confAlarmaP();
            break;

          }
          if (!digitalRead(SET))
          {
            Serial.println("~~~SET~~~");
            break;
          }

        }
      }
///**************** CONFIGURA TIEMPOS BOMBA RECIRCULACION**********
      if (motor == 2)
      {
        long tinicio = millis();
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("BOMBA");
        lcd.setCursor(1, 1);
        lcd.print("RECIRCULACION");
        delay(200);
        while (1)//-------------revisar
        {
          long tfinal = millis();

          if ( tfinal - tinicio > 5000)
          {
            lcd.clear();
            goto inicio;

          }

          if (!digitalRead(OK))
          {
            delay(500);
            lcd.noBacklight();
            delay(1000);
            lcd.backlight();
            confAlarmaR();
            break;

          }
          if (!digitalRead(SET))
          {
            Serial.println("~~~SET~~~");
            break;
          }

        }
      }
///**************** CONFIGURA TIEMPOS BOMBA ACIDO**********
      if (motor == 3)
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("BOMBA");
        lcd.setCursor(4, 1);
        lcd.print("ACIDO");
        delay(200);
        motor = 0;
      }
    }
  }
}
