void Mide_corrientes()
{
  /*********************Se deben de cambiar los pines***************************/
  I_1=get_corriente(100,sens_1,off_1,0);
  I_2=get_corriente(100,sens_2,off_2,1);
  I_3=get_corriente(100,sens_3,off_3,2);
}

/////////Corriente///////////
float get_corriente(int n_muestras,float Sensibilidad,float offset,int pin)
{
  float voltajeSensor;
  float corriente=0;
  for(int i=0;i<n_muestras;i++)
  {
    voltajeSensor = analogRead(pin) * (3.3 / 1023);////lectura del sensor
    corriente=corriente+(voltajeSensor-offset)/Sensibilidad; //Ecuación  para obtener la corriente
  }
  corriente=corriente/n_muestras;
  return(corriente);
}
