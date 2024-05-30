void Inicia_Motores()
{
  pinMode(dir1, OUTPUT);
  pinMode(pwm1, OUTPUT); 
  pinMode(dir2, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(pwm3, OUTPUT);

  digitalWrite(dir1,direccion1);
  digitalWrite(dir2,direccion2);
  digitalWrite(dir3,direccion3);
}

void Control_Motores()
{
  Entrada_1=Uj+U*T_1;
  Entrada_2=Uj+U*T_2;
  Entrada_3=Uj+U*T_3;
  
  if(Entrada_1>=0)
  direccion1=HIGH;
  else
  direccion1=LOW;
  
  if(Entrada_2>=0)
  direccion2=HIGH;
  else
  direccion2=LOW;
  
  if(Entrada_3>=0)
  direccion3=HIGH;
  else
  direccion3=LOW;

  digitalWrite(dir1,direccion1);
  digitalWrite(dir2,direccion2);
  digitalWrite(dir3,direccion3);

  Entrada_1=constrain(Entrada_1,-250,250);
  Entrada_2=constrain(Entrada_2,-250,250);
  Entrada_3=constrain(Entrada_3,-250,250);

  /*if (abs(Entrada_1)<10)
  {
    Entrada_1=10;
  }
   if (abs(Entrada_2)<10)
  {
    Entrada_2=10;
  }
   if (abs(Entrada_3)<10)
  {
    Entrada_3=10;
  }*/
   
  /* analogWrite(pwm1,abs(Entrada_1));
  analogWrite(pwm2,abs(Entrada_2));
  analogWrite(pwm3,abs(Entrada_3));
 */
  ledcWrite(pwmChannel1, abs(Entrada_1));
  ledcWrite(pwmChannel2, abs(Entrada_2));
  ledcWrite(pwmChannel3, abs(Entrada_3));
 }
