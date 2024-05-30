void Realiza_Control()
{  
  tact=millis();
  if(tact-tant>tmuestreo)
  {
    error=angulo-degrees(theta);
    errorj=-yaw+c;
    Uj=kpj*errorj;
    
    error_d= 1000*(error-errorpasado)/tmuestreo;
    //ki_sum=ki_sum+error*(Tiempo_muestreo/1000);  

   if(abs(degrees(beta)-beta_ant)>=180)
    {
    Error_suma=error*(tmuestreo/1000)-Error_suma;
    }
    else
    {
    Error_suma=error*(tmuestreo/1000)+Error_suma;
    }

    //Error_suma=constrain(Error_suma,-100,100);
    U=error*kp+error_d*kd+Error_suma*ki;
    
    
    errorpasado=error;
    tant=tact;
    beta_ant=degrees(beta);
  }
}

void Control_pos()
{
  /*a=-kp_pos*Ptj;
  b=-kp_pos*Pti;

  a=constrain(a,-2,2);
  b=constrain(b,-2,2);*/
}

