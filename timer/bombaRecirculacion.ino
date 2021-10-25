//---funciones para encender/apagar bomba recirculacion--
void bombaRon()
{

  Serial.println("alarma on");
  digitalWrite(bombaR, HIGH);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("BOMBA REC.");
  lcd.setCursor(1, 1);
  lcd.print("ON");
  Serial.println("encendi motor");
  delay(100);
}


void bombaRoff()
{
  Serial.println("alarma off");
  digitalWrite(bombaR, LOW);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("BOMBA REC.");
  lcd.setCursor(1, 1);
  lcd.print("OFF");
  Serial.println("apague motor");
  delay(100);
}

//--funcion para configurar los tiempos ON/OFF BOMBA_R
void confAlarmaR()//---OK---
{
  long tinicio = millis();
  Serial.println("----MENU----");
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TIEMPO");
  lcd.setCursor(7, 1);
  lcd.print("ON");
  delay(200);
  minxRR = 0;
  repetecionesRR=0;
  while (1)
  {

    long tfinal = millis();

    if ( tfinal - tinicio > 60000)
    {
      lcd.clear();
      break;

    }
    if (!digitalRead(SET))// AL PRESIONAR SET AUMENTA ALARMAS
    {
      delay(200);
      minxRR++;
      if (minxRR > 59) // NUMERO DE ALARMAS PREESTABLECIDAS
      {
        minxRR = 0;

      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("min encendido");
      lcd.setCursor(7, 1);
      lcd.print(minxRR);
      Serial.println(minxRR);


    }
    if (!digitalRead(OK))
    {
      lcd.clear();
      alarmax = 100;//para que no vuelva a setear
      break;
    }

  }

  delay(200);
  lcd.noBacklight();
  delay(1000);
  lcd.backlight();
  delay(100);
  Serial.println("----MENU2----");
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TIEMPO");
  lcd.setCursor(7, 1);
  lcd.print("OFF");
  minyR = 0;
  while (1)
  {

    long tfinal = millis();

    if ( tfinal - tinicio > 120000)
    {
      lcd.clear();
      break;

    }
    if (!digitalRead(SET))// AL PRESIONAR SET AUMENTA ALARMAS
    {
      delay(200);
      minyR++;
      if (minyR > 59) // NUMERO DE ALARMAS PREESTABLECIDAS
      {
        minyR = 0;//para que no vuelva a setear

      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("min apagado");
      lcd.setCursor(7, 1);
      lcd.print(minyR);
      Serial.println(minyR);


    }
    if (!digitalRead(OK))
    {
      lcd.clear();
      alarmay = 100;
      break;
    }

  }
  delay(200);
  lcd.noBacklight();
  delay(1000);
  lcd.backlight();
  delay(100);
  Serial.println("----MENU2----");
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("REPETICIONES");
  lcd.setCursor(3, 1);
  lcd.print("DIARIAS");
  while (1)
  {

    long tfinal = millis();

    if ( tfinal - tinicio > 120000)
    {
      lcd.clear();
      break;

    }
    if (!digitalRead(SET))// AL PRESIONAR SET AUMENTA ALARMAS
    {
      delay(200);
      repetecionesR++;
      if (repetecionesR > 7) // NUMERO DE ALARMAS PREESTABLECIDAS
      {
        repetecionesR = 0;

      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("repeticiones");
      lcd.setCursor(7, 1);
      lcd.print(repetecionesR);
      Serial.println(repetecionesR);


    }
    if (!digitalRead(OK))
    {
      lcd.clear();
      break;
    }

  }
  bomR = true;
}


//*****************************************************
//--- modo manual bombaR
void alarmaR() //--Configurable---
{

//---funcion corrije el desborde----
  if (myRTC.minutes == 59 and myRTC.seconds > 58 and bomR and !pasoy) //---ok---
  {
    Serial.println("-----DESBORDE---");
    int paso1, paso2;
    paso1 = 60 - alarmax; 
    minxRRx = minxRR;
    paso2 = paso1 - minxRR;
    alarmax = 0;
    minxRR = abs(paso2);
    Serial.println(minxRR);
    pasox = true;


  }
//---funcion corrije el desborde----
  if (myRTC.minutes == 59 and myRTC.seconds > 58 and !bomR and !pasox) //---ok----
  {
    Serial.println("-----DESBORDE---");
    int paso1, paso2;
    paso1 = 60 - alarmay;
    minyRy = minyR;
    paso2 = paso1 - minyR;
    alarmay = 0;
    minyR = abs(paso2);
    Serial.println(minyR);
    pasoy = true;

  }

//----funcion para apagar la bombaR despues de x min-----------
  if (myRTC.hours == myRTC.hours and myRTC.minutes == alarmax + minxRR and bomR)
  {

    bombaRoff();
    alarmay = myRTC.minutes;
    if (pasox)
    {
      minxRR = minxRRx;
    }
    bomR = false;
  }

//----funcion para encender la bombaR despues de y min----------
  if (myRTC.hours == myRTC.hours and myRTC.minutes == alarmay + minyR and !bomR)
  {
    bombaRon();// distinta de minute
    if (pasoy)
    {
      minyR = minyRy;
    }
    bomR = true;
    setbomR = true;
  }

repetecionesRR++;

}
