const int canal_a1 = 19; // Pin de señal A del encoder

volatile long count = 0; // Contador de pulsos del encoder
unsigned long prevTime = 0;
float rpm = 0.0;
const int pulsesPerRevolution = 12*75;
float tiempo;

void Achange1()
{
  count++;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(canal_a1,INPUT);
  attachInterrupt(digitalPinToInterrupt(canal_a1),Achange1,CHANGE); 
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();
  unsigned long timeInterval = currentTime - prevTime;
  
  // Calcular la velocidad cada 100 ms (0.1 segundos)
  if (timeInterval >= 20) {
    noInterrupts(); // Pausa las interrupciones para leer el valor del encoder
    long pulses = count;
    count = 0; // Reinicia el contador de pulsos
    interrupts(); // Reactiva las interrupciones

    // Cálculo de la velocidad en RPM
    float revolutions = (float)pulses / pulsesPerRevolution;
    rpm = (revolutions / (timeInterval / 60000.0));
    tiempo = millis();
    prevTime = currentTime; // Actualiza el tiempo anterior
  } 
  Serial.print("A");
  Serial.print(rpm);
  Serial.print("B");
  Serial.print(currentTime);
  Serial.print("C");
  
}
