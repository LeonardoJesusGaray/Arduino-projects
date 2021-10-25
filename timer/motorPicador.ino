//---funciones para encender/apagar motor picador--
void motorPon()
{

  Serial.println("alarma on");
  digitalWrite(motorP, HIGH);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("M.PICADOR");
  lcd.setCursor(1, 1);
  lcd.print("ON");
  Serial.println("encendi motor");
  delay(100);
}


void motorPoff()
{
  Serial.println("alarma off");
  digitalWrite(motorP, LOW);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("M.PICADOR");
  lcd.setCursor(1, 1);
  lcd.print("OFF");
  Serial.println("apague motor");
  delay(100);
}

//funcion para configurar los tiempos ON/OFF motor_P

void confAlarmaP()//---OK---
{
  long tinicio = millis();
  Serial.println("----MENU----");
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TIEMPO");
  lcd.setCursor(7, 1);
  lcd.print("ON");
  delay(200);
  minxPP = 0;
  repetecionesPP=0;
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
      minxPP++;
      if (minxPP > 59) // NUMERO DE ALARMAS PREESTABLECIDAS
      {
        minxPP = 0;

      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("min encendido");
      lcd.setCursor(7, 1);
      lcd.print(minxPP);
      Serial.println(minxPP);


    }
    if (!digitalRead(OK))
    {
      lcd.clear();
      alarmaxP = 100;//para que no vuelva a setear
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
  minyP = 0;
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
      minyP++;
      if (minyP > 59) // NUMERO DE ALARMAS PREESTABLECIDAS
      {
        minyP = 0;//para que no vuelva a setear

      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("min apagado");
      lcd.setCursor(7, 1);
      lcd.print(minyP);
      Serial.println(minyP);


    }
    if (!digitalRead(OK))
    {
      lcd.clear();
      alarmayP = 100;
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
      repetecionesP++;
      if (repetecionesP > 7) // NUMERO DE ALARMAS PREESTABLECIDAS
      {
        repetecionesP = 0;

      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("repeticiones");
      lcd.setCursor(7, 1);
      lcd.print(repetecionesP);
      Serial.println(repetecionesP);


    }
    if (!digitalRead(OK))
    {
      lcd.clear();
      break;
    }

  }
  bomP = true;
}

//--- modo manual motorP
void alarmaP() //--Configurable---
{

//---funcion corrije el desborde----
  if (myRTC.minutes == 59 and myRTC.seconds > 58 and bomP and !pasoyP) //---ok---
  {
    Serial.println("-----DESBORDE---");
    int paso1, paso2;
    paso1 = 60 - alarmaxP; 
    minxPPx = minxPP;
    paso2 = paso1 - minxPP;
    alarmaxP = 0;
    minxPP = abs(paso2);
    Serial.println(minxPP);
    pasoxP = true;


  }
//---funcion corrije el desborde----
  if (myRTC.minutes == 59 and myRTC.seconds > 58 and !bomP and !pasoxP) //---ok----
  {
    Serial.println("-----DESBORDE---");
    int paso1, paso2;
    paso1 = 60 - alarmayP;
    minyPy = minyP;
    paso2 = paso1 - minyP;
    alarmayP = 0;
    minyP = abs(paso2);
    Serial.println(minyP);
    pasoyP = true;

  }

//----funcion para apagar la bombaR despues de x min-----------
  if (myRTC.hours == myRTC.hours and myRTC.minutes == alarmaxP + minxPP and bomP)
  {

    motorPoff();
    alarmayP = myRTC.minutes;
    if (pasoxP)
    {
      minxPP = minxPPx;
    }
    bomP = false;
  }

//----funcion para encender la bombaR despues de y min----------
  if (myRTC.hours == myRTC.hours and myRTC.minutes == alarmayP + minyP and !bomP)
  {
    motorPon();// distinta de minute
    if (pasoyP)
    {
      minyP = minyPy;
    }
    bomP = true;
    setbomP = true;
  }

repetecionesPP++;

}
