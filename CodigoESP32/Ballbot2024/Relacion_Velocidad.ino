//Relaciones: angulo de la llanta (theta_w) --> angulo bola (theta_b);     Par de planos a par llantas

/* void VelocidadPlanosVelocidadMotores()
{
  //taken from Kinematic Analysis and Control Algorithm for the Ballbot
  v_1 = -U_pitch  * sin(alfa);
  v_2 = sin(alfa) * ( 0.866*U_roll + 0.5*U_pitch);
  v_3 = sin(alfa) * (-0.866*U_roll + 0.5*U_pitch);    //Asegurarse que pitch y roll se consideraron en el plano correcto
} */

/* void AnguloPelota(){
  //Taken from Design of LQR Controller
  theta_b = rw*theta_w / (rb * cos(beta - 0.523) * cos(alfa));
  theta_b_x = theta_b * cos(beta);
  theta_b_y = theta_b * sin(beta);
  Serial.print("Theta_b: " + String(theta_b) + "     ");  
} */

void VelocidadAngularPelota(){
  //Taken from Zurich pp. 76
  theta_b_x_d = 1/(3*rb) * (2.45) * rb *

}

void ParPlanosParMotores()
{
  //Funciona bien
  //taken from Zurich pp. 70
  T_1 =  0.666*( T_x)             / cos(alfa);
  T_2 = -0.333*( T_x + 1.732*T_y) / cos(alfa);
  T_3 =  0.333*(-T_x + 1.732*T_y) / cos(alfa);
}