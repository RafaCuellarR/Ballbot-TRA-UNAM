void Control()
{  
  tact = millis();
  if(tact-tant>tmuestreo)
  {
////////////    CONTROL VARIABLES DE ESTADO      /////////////    
    //Derivadas
    pitch_d = (pitch - pitch_pasado) / tmuestreo;
    roll_d = (roll - roll_pasado) / tmuestreo;
    theta_b_x_d = (theta_b_x - theta_b_x_pasado) / tmuestreo;
    theta_b_y_d = (theta_b_y - theta_b_y_pasado) / tmuestreo;

    T_x  =  pitch*k1  +  pitch_d*k2  +  theta_b_x*k3 + theta_b_x_d*k4;
    T_y  =  roll*k1   +  roll_d*k2   +  theta_b_y*k3 + theta_b_y_d*k4;
    beta = atan(T_y / T_x);

    tant = tact;
    roll_pasado = roll;
    pitch_pasado = pitch;
    theta_b_x_pasado = theta_b_x;
    theta_b_y_pasado = theta_b_y;

    Serial.print("T_x: " + String(T_x) + "     ");
    Serial.println("T_y: " + String(T_y));
/* /////    CONTROL  PID   ///////    
    //Control roll
    error_roll   = degrees(roll);    
    error_d_roll = 1000*(error_roll-errorpasado_roll)/tmuestreo;
    if(error_roll < 5)     error_i_roll+=error_roll*(tmuestreo/1000);
    else                   error_i_roll = 0;

    //Control pitch
    error_pitch = degrees(pitch);    
    error_d_pitch = 1000*(error_pitch-errorpasado_pitch)/tmuestreo;
    if(error_pitch < 5)    error_i_pitch+=error_pitch*(tmuestreo/1000);
    else                   error_i_pitch = 0;

    T_y  =  error_roll *kp  +  error_d_roll*kd   +  error_i_roll*ki;
    T_x  =  error_pitch*kp  +  error_d_pitch*kd  +  error_i_pitch*ki;
    beta = atan(T_y / T_x);

    errorpasado_roll  = error_roll;
    errorpasado_pitch = error_pitch;
    tant = tact;
 */  
  }
}

