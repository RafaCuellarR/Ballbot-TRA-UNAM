//Inicializa encoders, interrupcion y calculo de posición (theta_w)
void Inicia_Encoders(){
  pinMode(canal_a1,INPUT);
  attachInterrupt(digitalPinToInterrupt(canal_a1),Achange1,CHANGE); 
}

void Achange1()
{
  count1a++;
}

void Theta_w(){
  //Funciona bien
  theta_w = ((float)count1a / 1800) * (6.283);
  if(count1a > 1800){
    count1a = 0;
  }
  Serial.print("Theta_w: " + String(theta_w) + "     ");
}

/*void Inicia_Encoders() 
{
  pinMode(canal_a1,INPUT);
  pinMode(canal_b1,INPUT);
  pinMode(canal_a2,INPUT);
  pinMode(canal_b2,INPUT);
  pinMode(canal_a3,INPUT);
  pinMode(canal_b3,INPUT);

  
  attachInterrupt(digitalPinToInterrupt(canal_a1),Achange1,CHANGE); 
  attachInterrupt(digitalPinToInterrupt(canal_b1),Bchange1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(canal_a2),Achange2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(canal_b2),Bchange2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(canal_a3),Achange3,CHANGE);
  attachInterrupt(digitalPinToInterrupt(canal_b3),Bchange3,CHANGE);
}

void Calcula_Velocidad()
{
  vel1=(1000*60/(48*75))/(tant1-tact1);//Esta en RPM
  pos1=(0.06*3.1416*(360*count1)/(48*75));//Esta en metros 
  
  vel2=(1000*60/(48*75))/(tant2-tact2);
  pos2=(0.06*3.1416*(360*count2)/(48*75));
  
  vel3=(1000*60/(48*75))/(tant3-tact3);
  pos3=(0.06*3.1416*(360*count3)/(48*75));
}

void Calcula_pos()
{
  Pti=pos1-(pos2*cos(60)+pos3*cos(60));
  Ptj=-pos2*sin(60)+pos3*sin(60);
}


void vel_esfera()
{
  if(T_1>=0.1)
  w_e1=(vel1/0.25)/(T_1);
  if(T_2>=0.1)
  w_e2=(vel2/0.25)/(T_2);
  if(T_3>=0.1)
  w_e3=(vel3/0.25)/(T_3);
}

void Achange1()
{
  count1a++;
}

void Bchange1()
{
  count1b++;
}

void Achange2()
{
  count2a++;
}

void Bchange2()
{
  count2b++;
}

void Achange3()
{
  count3a++;
}

void Bchange3()
{
  count3b++;
}

void CicloEncoder(){
    if(count1a == 500)
      {  A_1=digitalRead(canal_a1);
      B_1=digitalRead(canal_b1);
      
      if ((A_1 == HIGH)&&(B_1 == HIGH))state1 = 0;
      if ((A_1 == HIGH)&&(B_1 == LOW))state1 = 1;
      if ((A_1 == LOW)&&(B_1== LOW))state1 = 2;
      if ((A_1== LOW)&&(B_1== HIGH))state1 = 3;
      indexx1 = 4*state1 + statep1;
      count1 = count1 + QEM[indexx1];
      statep1 = state1;
      tant1=tact1;
      tact1=millis();
      count1a = 0;
      }

    if(count1b == 500)
      {  B_1=digitalRead(canal_b1);
        A_1=digitalRead(canal_a1);

        if ((A_1 == HIGH)&&(B_1 == HIGH))state1 = 0;
        if ((A_1 == HIGH)&&(B_1 == LOW))state1 = 1;
        if ((A_1 == LOW)&&(B_1 == LOW))state1 = 2;
        if ((A_1 == LOW)&&(B_1 == HIGH))state1 = 3;
        indexx1 = 4*state1 + statep1;
        count1 = count1 + QEM[indexx1];
        statep1 = state1;
        count1b = 0;
        }

    if(count2a == 500)  
      {A_2=digitalRead(canal_a2);
      B_2=digitalRead(canal_b2);
      
      if ((A_2 == HIGH)&&(B_2 == HIGH))state2 = 0;
      if ((A_2 == HIGH)&&(B_2 == LOW))state2 = 1;
      if ((A_2 == LOW)&&(B_2== LOW))state2 = 2;
      if ((A_2== LOW)&&(B_2== HIGH))state2 = 3;
      indexx2 = 4*state2 + statep2;
      count2 = count2 + QEM[indexx2];
      statep2 = state2;
      tant2=tact2;
      tact2=millis();
      count2a = 0;
      }
    
    if(count2b == 500)
    {  B_2=digitalRead(canal_b2);
      A_2=digitalRead(canal_a2);
      
      if ((A_2 == HIGH)&&(B_2 == HIGH))state2 = 0;
      if ((A_2 == HIGH)&&(B_2 == LOW))state2 = 1;
      if ((A_2 == LOW)&&(B_2 == LOW))state2 = 2;
      if ((A_2 == LOW)&&(B_2 == HIGH))state2 = 3;
      indexx2 = 4*state2 + statep2;
      count2 = count2 + QEM[indexx2];
      statep2 = state2;
      count2b = 0;
      }

      if(count3a == 500)
      {  A_3= digitalRead(canal_a3);
        B_3=  digitalRead(canal_b3);
        
        if ((A_3 == HIGH)&&(B_3 == HIGH))state3 = 0;
        if ((A_3 == HIGH)&&(B_3 == LOW))state3 = 1;
        if ((A_3 == LOW)&&(B_3== LOW))state3 = 2;
        if ((A_3== LOW)&&(B_3== HIGH))state3 = 3;
        indexx3 = 4*state3 + statep3;
        count3 = count3 + QEM[indexx3];
        statep3 = state3;
        tant3=tact3;
        tact3=millis();
        count3a = 0;
        }

    if(count3b == 500)
    {  B_3=  digitalRead(canal_b3);
      A_3 = digitalRead(canal_a3);
      
      if ((A_3 == HIGH)&&(B_3 == HIGH))state3 = 0;
      if ((A_3 == HIGH)&&(B_3 == LOW))state3 = 1;
      if ((A_3 == LOW)&&(B_3 == LOW))state3 = 2;
      if ((A_3 == LOW)&&(B_3 == HIGH))state3 = 3;
      indexx3 = 4*state3 + statep3;
      count3 = count3 + QEM[indexx3];
      statep3 = state3;
      count3b = 0;
      }
} */