/////////////////////////////////////////////////////////////
//          Facultad de Ingenieria UNAM                    //
//          Taller de Robótica Abierta                     //
//                                                         //
//    Proyect: Ballbot                                     //
//                                                         //
//    Description: Digital state feedback control to       //
//    stabilize a ballbot.                                 //
//                                                         //
//    Franco Ángel Jasso Osorio                            //
//    Rafael Cuéllar Ramírez                               //
//                                                         //
//    2024 MIT License                                     //
/////////////////////////////////////////////////////////////

// LIBRARIES
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include <PID_v1.h> // bilioteca PID 
#include <BluetoothSerial.h>

// Physical Parameters (w: wheel    b: ball    r: robot)
const float rw = 0.03;  // [m]
const float rb = 0.274;  // bola cargada
//const float rb = 0.12;   // bola basquet
float angle_w1 = 0, angle_w2 = 0, angle_w3 = 0; 
float theta_b = 0, theta_b_x = 0, theta_b_y = 0;      //angulo de la pelota (variable de estado)
float beta = 0;

// IMU
MPU6050 mpu;
#define INTERRUPT_PIN  19  // use pin 2 on Arduino Uno & most boards
float yaw=0,pitch=0,roll=0;

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// Motion
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

//////////////VARIABLES PARA MOTORES/////////////////////////////////////////////////////////////////////////////////////
int dir1=18, dir2=17, dir3=4;   
int pwm1=5, pwm2=16, pwm3=2;
boolean direccion1=HIGH,direccion2=HIGH,direccion3=HIGH;

///////////////// VARIABLES PARA CONTROL MOTORES /////////////////////////
float Entrada_1 = 0;
float Entrada_2 = 0;
float Entrada_3 = 0;

//////////////VARIABLES PARA RELACIÓN DE PAR/////////////////////////////////////////////////////////////////////////////
//float alfa=1.169;     //67° en radianes   KAB
float alfa = 0.401;     //23° en radianes   Zurich
float T_1 = 0, T_2 = 0, T_3 = 0;
//////////////VARIABLES PARA ENCODER///////////////////////////////////////////////////////////////////////////////////
const int canal_b1 = 35;
const int canal_a1 = 32;
const int canal_b2 = 33;
const int canal_a2 = 25;
const int canal_b3 = 14;
const int canal_a3 = 12;

int count1a = 0;

//////////////VARIABLES PARA ALGORITMO DE CONTROL///////////////////////////////////////////////////////////////////
//Variables de estado
float roll_pasado = 0, pitch_pasado = 0, theta_b_x_pasado = 0, theta_b_y_pasado = 0;
float roll_d = 0, pitch_d = 0, theta_b_x_d = 0, theta_b_y_d = 0;
float k1 = 0, k2 = 0, k3 = 0, k4 = 0;

//PID
float error_roll = 0,  error_d_roll = 0,  error_i_roll = 0,  errorpasado_roll = 0;        //Roll
float error_pitch = 0, error_d_pitch = 0, error_i_pitch = 0, errorpasado_pitch = 0;        //Pitch
float kp=80, kd=0.8, ki=8.0;

float T_x = 0, T_y = 0;
/*Para el tiempo*/
float tact=0, tant=0, tmuestreo=100;

/*INTERRUPT DETECTION ROUTINE*/
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() 
{
    mpuInterrupt = true;
}

///////////////////////////////////////////VOID SETUP////////////////////////////////////////////////////////////
void setup() 
{  
  Wire.begin(21,22);//Para la IMU
  Serial.begin(9600);

  ledcAttach(pwm1, 1000, 8);
  ledcAttach(pwm2, 1000, 8);
  ledcAttach(pwm3, 1000, 8);
  
  //Inicia_IMU();
  Inicia_Encoders();
  //Inicia_Motores();
}

//////////////////////////////////////////VOID LOOP////////////////////////////////////////////////////////////////


void loop() 
{
  Theta_w();
  AnguloPelota();
}

/*   if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Leer hasta que se presione Enter
    input.trim();  // Eliminar espacios en blanco
    int index = input.indexOf(' ');
    String T_x_string = input.substring(0,index);
    String T_y_string = input.substring(index+1);
    T_x = T_x_string.toFloat();
    T_y = T_y_string.toFloat();

    ParPlanosParMotores();
    ledcWrite(pwm1, T_1);
    ledcWrite(pwm2, T_2);
    ledcWrite(pwm3, T_3);

    Serial.print("T_x: ");
    Serial.print(T_x);
    Serial.print("       ");
    
    Serial.print("T_y: ");
    Serial.println(T_y);

    Serial.print("T_1: ");
    Serial.print(T_1);
    Serial.print("       ");
    Serial.print("T_2: ");
    Serial.print(T_2);
    Serial.print("       ");
    Serial.print("T_3: ");
    Serial.print(T_3);
    Serial.print("       "); 
  } */


/*   Mide_Angulo();
////////////////////////////////
 if (millis()>1000)
 inicio = false;
///////////////////////////////////////
 if(!inicio)
 {
  Realiza_Control();
  ParPlanosParMotores();
  Control_Motores();
  Serial.print("Roll:  "); Serial.println(roll);
  Serial.print("Pitch:  "); Serial.println(pitch);
  Serial.print("Yaw:  "); Serial.println(yaw); Serial.println();
 } */
