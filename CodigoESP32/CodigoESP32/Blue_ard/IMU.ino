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
  pinMode(LED_PIN, OUTPUT);
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

   blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
   
 } 
}


