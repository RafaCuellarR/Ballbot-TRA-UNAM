//////////////LIBRERIAS////////////////////////////////////////////////////////////////////////////////////////////
#include "ESP32_IDE.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include <PID_v1.h> // bilioteca PID 
//////////////VARIABLES PARA LA IMU///////////////////////////////////////////////////////////////////////////////
MPU6050 mpu;
#define INTERRUPT_PIN  19  // use pin 2 on Arduino Uno & most boards
#define LED_PIN E1 

// Configuración PWM
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int pwmChannel3 = 2;
const int freq = 5000;
const int resolution = 8;

bool blinkState = false;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

/*Orientation/motion vars*/
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

/*Packet structure for InvenSense teapot demo*/
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

/*INTERRUPT DETECTION ROUTINE*/
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() 
{
    mpuInterrupt = true;
}
/*Variables de la IMU*/
float yaw=0,pitch=0,roll=0;

//////////////VARIABLES PARA THETA Y BETA///////////////////////////////////////////////////////////////////////////////
float w1[3];
float v1[3];
float u1[3];
float n1[3];

float ux[3]={1,0,0};
float uy[3]={0,1,0};
float uz[3]={0,0,1};
float theta,beta;
float beta_ant;

//////////////VARIABLES PARA CYTRON/////////////////////////////////////////////////////////////////////////////////////
#define dir1  S6
#define pwm1  S7

#define dir2  S8
#define pwm2  S9

#define dir3  S10
#define pwm3  S11

/* int dir1=8, dir2=6, dir3=4;   
int pwm1=7, pwm2=5, pwm3=3; */
boolean direccion1=HIGH,direccion2=HIGH,direccion3=HIGH;


//////////////VARIABLES PARA RELACIÓN DE PAR/////////////////////////////////////////////////////////////////////////////
float cosi=0,seni=0,seno=0,coseno=0;
float alpha=67;
float T_1,T_2,T_3;
float T1d, T2d, T3d;
float T1m, T2m,T3m;

float Ep1=0,Ep2=0,Ep3=0;

//////////////VARIABLES PARA ENCODER///////////////////////////////////////////////////////////////////////////////////
#define canal_b1  E3
#define canal_a1  E4
#define canal_b2  E5
#define canal_a2  E6
#define canal_b3  E9
#define canal_a3  E10


/* int canal_a1= 46;
int canal_b1= 44;
int canal_a2= 42;
int canal_b2= 40;
int canal_a3= 38;
int canal_b3= 36; */

/*Para el tiempo entre cada pulso*/
static volatile float tant1=0,tact1=0,count1=0; 
static volatile float tant2=0,tact2=0,count2=0; 
static volatile float tant3=0,tact3=0,count3=0; 

static volatile boolean A_1,B_1,A_2,B_2,A_3,B_3;

static volatile byte state1, statep1, indexx1;
static volatile byte state2, statep2, indexx2;
static volatile byte state3, statep3, indexx3;

static volatile int QEM[16]= {0,-1,0,1,1,0,-1,0,0,1,0,-1,-1,0,1,0};

float vel1=0;
float pos1=0;
float vel2=0;
float pos2=0;
float vel3=0;
float pos3=0;

float w_e1=0,w_e2=0,w_e3=0;

//////////////VARIABLES PARA ALGORITMO DE CONTROL///////////////////////////////////////////////////////////////////

//double kp=80,kd=0.8,ki=8.0,kt=0;//Con estás se relaizo el video de movilidad 

//double kp=78,kd=0.82,ki=8.2,kt=0;//Con estás se relaizo el video de movilidad 

//Este es para la relacion de par: double kp=40,kd=0.08,ki=1.5,kt=0;
double kp=80,kd=0.8,ki=8.0,kt=0;//Este es para la esfera sin canicas con voltaje de 7.4 a kp de 80.
//Con un voltaje mas bajo es decir a 7.2 --------..... Entonces se lo pine un kp de 8.2  

double errorj=0,Uj=0;

double kpj=0.12,kdj=0.0,kij=0.0;///D=1500 kp era 0.12

float Pti=0,Ptj=0,Pt=0,angulo_pos=0;

//float kp_pos=0.09;

double angulo=0,error=0,errorpasado=0,error_d=0;
double U;
/*Para el tiempo*/
float tact=0,tant=0,tmuestreo=7;
float Entrada_1=0, Entrada_2=0, Entrada_3=0;
float Error_suma=0;

boolean inicio=true;

//////////////VARIABLES PARA SENSORES DE CORRRIENTE///////////////////////////////////////////////////////////////////
float sens_1=0.0374,sens_2=0.0378,sens_3=0.034; //sensibilidad en Voltios/Amperio para sensor77 de 30A
float off_1=1.354,off_2=1.392,off_3=1.37;
float I_1,I_2,I_3;

//////////////VARIABLES PARA LA DIRECCIÓN///////////////////////////////////////////////////////////////////
char numero;
float count_dir=0.005;
float a=0,b=0,c=0;


///////////////////////////////////////////VOID SETUP////////////////////////////////////////////////////////////
void setup() 
{  
  Wire.begin(21,22);//Para la IMU
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  Serial.begin(9600);
  //Serial1.begin(115200);

  pinMode(E6, INPUT);
  pinMode(E7, INPUT);
  pinMode(E8, INPUT);
  pinMode(E9, INPUT);
  pinMode(E10, INPUT);
  pinMode(E11, INPUT);

  pinMode(S5, INPUT);
  pinMode(S6, OUTPUT);
  pinMode(S7, OUTPUT);
  pinMode(S8, OUTPUT);
  pinMode(S9, OUTPUT);
  pinMode(S10, OUTPUT);
  pinMode(S11, OUTPUT);
  pinMode(S12, OUTPUT);

  ledcSetup(pwmChannel1, freq, resolution);
  ledcAttachPin(pwm1, pwmChannel1);

  ledcSetup(pwmChannel2, freq, resolution);
  ledcAttachPin(pwm2, pwmChannel2);

  ledcSetup(pwmChannel3, freq, resolution);
  ledcAttachPin(pwm3, pwmChannel3);
   
  //Inicial_pot();

  //Seponen los parametros iniciales para iniciar la IMU
  //Aqui se encuentran los valores para calibrarla
  //Revisar pestaña IMU........
  Inicia_IMU();
/**********************************************************************************************************/

  //Se declaran los pines y las direcciones para iniciar los motores 
  //Ver pestaña Motores..............
  Inicia_Motores();
/**********************************************************************************************************/

  //Se declaran pines e interrupciones para los encoders
  //Revisar pestaña Encoders...............
  Inicia_Encoders();
}

//////////////////////////////////////////VOID LOOP////////////////////////////////////////////////////////////////

void loop() 
{
  //Aqui se miden los ángulo Pitch, Roll y Yaw para el control
  Mide_Angulo();
  //Leer_pot();

/***********************Para evitar que al principio los motores se muevan***************************************/
 if (millis()>7000)
 inicio=false;
/****************************************************************************************************************/

 if(!inicio)
 {

  //Esto es de los encoders 
  //Para ver el codigo ir a la pestaña Encoder............ 
  //Se calcula la velocidad y la posicion de cada una de las ruedas 
  Calcula_Velocidad();
/**********************************************************************************************************/
  //Calcula_pos();
  //Control_pos();
/**********************************************************************************************************/


  //Esto es para el calculo de la direccción que se le dará al robot con ayuda de la PC
  //Revisar parte del codigo en la pestaña Direccion.........
  Calcula_dir();
/**********************************************************************************************************/

  //Aqui se calculan los ángulos Theta y beta para realizar el control
  //Para ver el codigo ir a la pestaña Theta_Beta..............
  //Los águlos estan en radianes 
  Calcula_Thetabeta();
/**********************************************************************************************************/


  //Para realizar el control en 3D
  //Las ruedas se deben de mover de cierta forma para lograr mover al robot 
  //Para esto se calcula una relacion
  //La cual tiene que ver con Theta y el ángulo de inclinación de las ruedas
  //Para ver el codigo abrir pestaña Relacion_Par................
  Relacion_Velocidad();
  //Calcula_Relacion();
/**********************************************************************************************************/

  //vel_esfera();
/**********************************************************************************************************/

  //En esta parte se calculan los errores PID para mantener al robot en equiilibrio 
  //Para ver el codigo abrir pestaña Control............
  Realiza_Control();
/**********************************************************************************************************/

  //Para la etapa de potencia se manda una señal PWM a cada controlador de motor CYTRON
  //Para ver el codigo revisar la pestaña Motores...........
  Control_Motores();
/**********************************************************************************************************/


  //Esta parte es solo para imprimir via serial 
  /*Serial.print(pitch);
  Serial.print(",");
  Serial.println(roll);*/
  
  //Serial1.println(roll);
  
  //Serial.print(abs(Entrada_2));
  //Serial.print(",");
  //Serial.print(abs(Entrada_3));
  //Serial.print(",");
  //Serial.println("");///Hola

  
/*   Serial1.print(a);
  Serial1.print(",");
  Serial1.print(b);
  Serial1.print(",");
  Serial1.println(roll); */

  //PRUEBAS
  Serial.println(yaw);
  Serial.println(pitch);
  Serial.println(roll);
  Serial.println();
  
 }
}
