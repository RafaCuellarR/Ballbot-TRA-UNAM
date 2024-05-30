
void Relacion_Velocidad()
{
  cosi=cos(radians(alpha));
  seni=sin(radians(alpha));
  coseno= cos(beta+radians(180));
  seno= sin(beta+radians(180));
  T_1=-(coseno*sqrt(pow(seni,2)+pow(cosi*seno,2)));
  coseno= cos(beta+radians(60));
  seno= sin(beta+radians(60));
  T_2=-(coseno*sqrt(pow(seni,2)+pow(cosi*seno,2)));
  coseno= cos(beta+radians(300));
  seno= sin(beta+radians(300));
  T_3=-(coseno*sqrt(pow(seni,2)+pow(cosi*seno,2)));

  /*if(T_1<0)
  direccion1=LOW;
  else
  direccion1=HIGH;
  if(T_2<0)
  direccion2=LOW;
  else
  direccion2=HIGH;
  if(T_3<0)
  direccion3=LOW;
  else
  direccion3=HIGH;

  digitalWrite(dir1,direccion1);
  digitalWrite(dir2,direccion2);
  digitalWrite(dir3,direccion3); */
}

void Calcula_Relacion()
{
  float P=2*(3.1416/3);
  T_1=(2*sin(beta+P))/(3*cos(radians(alpha)));
  T_3=((sqrt(3)*cos(beta+P))-sin(beta+P))/(3*cos(radians(alpha)));
  T_2=(-(sqrt(3)*cos(beta+P))-sin(beta+P))/(3*cos(radians(alpha)));
}

