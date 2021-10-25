//--- modo manual bomba recirculacion

void manualR()
{
  alarmaR();// buscar una condicion para que solo se repita n-veces "repetecionesR"
  if (bomR and setbomR)
  {
    bombaRon();
    setbomR = false;
    alarmax = myRTC.minutes;
    Serial.println("-----ALARMAX");
  }



}


void manualP()
{
  alarmaP();// buscar una condicion para que solo se repita n-veces "repetecionesR"
  if (bomP and setbomP)
  {
    motorPon();
    setbomP = false;
    alarmaxP = myRTC.minutes;
    Serial.println("-----ALARMAX");
  }



}
