void Calcula_Thetabeta()
{
  w1[0]=cos(radians(roll+b));
  w1[1]=0;
  w1[2]=sin(radians(roll+b));
  
  v1[0]=0;
  v1[1]=cos(radians(pitch+a));
  v1[2]=sin(radians(pitch+a));

  u1[0]=w1[1]*v1[2]-w1[2]*v1[1];
  u1[1]=-(w1[0]*v1[2]-w1[2]*v1[0]);
  u1[2]=w1[0]*v1[1]-w1[1]*v1[0];
  
  n1[0]=u1[1]*uz[2]-u1[2]*uz[1];
  n1[1]=-(u1[0]*uz[2]-u1[2]*uz[0]);
  n1[2]=u1[0]*uz[1]-u1[1]*uz[0];
    
  /////Recordar que estos ángulos estan en radianes/////
  theta=acos((u1[2])/sqrt(pow(u1[0],2)+pow(u1[1],2)+pow(u1[2],2)));
  beta=asin((n1[0]*w1[0]+n1[1]*w1[1]+n1[2]*w1[2])/(sqrt(pow(n1[0],2)+pow(n1[1],2)+pow(n1[2],2))*sqrt(pow(w1[0],2)+pow(w1[1],2)+pow(w1[2],2)))); 
  if(roll+b>=0)
  beta=-beta+PI;

  if(theta>= (PI/2))
  theta= PI/2;
}
