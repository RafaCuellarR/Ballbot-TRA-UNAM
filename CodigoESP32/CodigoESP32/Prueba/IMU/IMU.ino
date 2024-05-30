#include "ESP32_IDE.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
MPU6050 mpu;
#define INTERRUPT_PIN  S5  // use pin 2 on Arduino Uno & most boards

//float arreglo[3];

/*INTERRUPT DETECTION ROUTINE*/
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() 
{
    mpuInterrupt = true;
}

bool blinkState = false;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

/*Variables de la IMU*/
float yaw=0,pitch=0,roll=0;
/*Orientation/motion vars*/
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

void Inicia_IMU()
{
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);
  devStatus = mpu.dmpInitialize();
  
/*********Para calibrar la IMU****************/
  mpu.setXAccelOffset(-4614);
  mpu.setYAccelOffset(-1365);
  mpu.setZAccelOffset(1517);
  mpu.setXGyroOffset(-32);
  mpu.setYGyroOffset(-30);
  mpu.setZGyroOffset(21);

/**********************************************/
  if (devStatus == 0) 
  {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } 
/*********************************************/
  //pinMode(LED_PIN, OUTPUT);
}


void Mide_Angulo()
{

  while (!mpuInterrupt && fifoCount < packetSize) {   }
/*********************************************/
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount(); 
/*********************************************/
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
  {
    mpu.resetFIFO();
  } 
  else 
  if (mpuIntStatus & 0x02) 
  {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize); 
    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    
   /*Obetncion de los ángulos*/
   yaw=ypr[0] * 180/M_PI;
   pitch=ypr[1]*180/M_PI;
   roll=ypr[2]*180/M_PI;
   //arreglo[3] = [yaw, pitch, roll];

/*    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState); */
   
 } 
}

void setup()
{
  Wire.begin();//Para la IMU
  //Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  Serial.begin(9600);
  pinMode(S5, INPUT);
  Inicia_IMU();
}

void loop()
{
  Mide_Angulo();

  Serial.println(yaw);
  Serial.println(pitch);
  Serial.println(roll);

}
