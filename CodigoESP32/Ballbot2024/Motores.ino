void Inicia_Motores()
{
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);

  digitalWrite(dir1,direccion1);
  digitalWrite(dir2,direccion2);
  digitalWrite(dir3,direccion3);
}

void Control_Motores()
{
  Entrada_1=T_1;
  Entrada_2=T_2;
  Entrada_3=T_3;
  
  if(Entrada_1>=0)  direccion1=HIGH;
  else              direccion1=LOW;
  
  if(Entrada_2>=0)  direccion2=HIGH;
  else              direccion2=LOW;
  
  if(Entrada_3>=0)  direccion3=HIGH;
  else              direccion3=LOW;

  digitalWrite(dir1,direccion1);
  digitalWrite(dir2,direccion2);
  digitalWrite(dir3,direccion3);

  Entrada_1=constrain(Entrada_1,-255,255);
  Entrada_2=constrain(Entrada_2,-255,255);
  Entrada_3=constrain(Entrada_3,-255,255);

  ledcWrite(pwm1, abs(Entrada_1));
  ledcWrite(pwm2, abs(Entrada_2));
  ledcWrite(pwm3, abs(Entrada_3));
/*   Serial.print("T_1:  "); Serial.println(T_1);
  Serial.print("T_2:  "); Serial.println(T_2);
  Serial.print("T_3:  "); Serial.println(T_3); */
 }
