 void Calcula_dir()
{
 if(Serial.available())
  {
    numero=Serial.read();
  }
  if(numero=='0')//48
  {
    a=a+count_dir;
    
    if(b>0.00)
    b=b-count_dir;
    if(b<0.00)
    b=b+count_dir;
    
  }
  if(numero=='1')//49
  {
    a=a-count_dir;

    if(b>0.00)
    b=b-count_dir;
    if(b<0.00)
    b=b+count_dir;
    
  }
  if(numero=='2')//50
  {
    b=b+count_dir;

    if(a>0.00)
    a=a-count_dir;
    if(a<0.00)
    a=a+count_dir;
    
  }
  if(numero=='3')//51
  {
    b=b-count_dir;

    if(a>0.00)
    a=a-count_dir;
    if(a<0.00)
    a=a+count_dir;

  }
  if(numero=='4')//52
  {
    c=c+count_dir;
    
    if(a>0.00)
    a=a-count_dir;
    if(a<0.00)
    a=a+count_dir;
    if(b>0.00)
    b=b-count_dir;
    if(b<0.00)
    b=b+count_dir;
    
  }
  if(numero=='5')//53
  {
    c=c-count_dir;
    
    if(a>0.00)
    a=a-count_dir;
    if(a<0.00)
    a=a+count_dir;
    if(b>0.00)
    b=b-count_dir;
    if(b<0.00)
    b=b+count_dir;
  }
  
  if(numero=='6')//54
  {
    if(a>0.00)
    a=a-count_dir;
    if(a<0.00)
    a=a+count_dir;
    if(b>0.00)
    b=b-count_dir;
    if(b<0.00)
    b=b+count_dir;
  }

  a=constrain(a,-3.3,3.05);
  b=constrain(b,-3.1,3.1);
  // put your main code here, to run repeatedly:  
}
