#include <MQUnifiedsensor.h>
#include <SoftwareSerial.h>

#define         Board                   ("Arduino UNO")
#define         Pin                     (A0)  //Analog input 3 of your arduino

#define         Type                    ("MQ-3") //MQ3
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ3CleanAir        (60) //RS / R0 = 60 ppm 

//센서 선언
MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
SoftwareSerial HC06(2, 3);

void setup() {
  
  Serial.begin(9600); //Init serial port
  HC06.begin(9600);

  
  MQ3.setRegressionMethod(1); 
  MQ3.setA(0.3934); MQ3.setB(-1.504); 

  MQ3.init(); 
 
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ3.update(); 
    calcR0 += MQ3.calibrate(RatioMQ3CleanAir);
    Serial.print(".");
  }
  MQ3.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {
    Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply"); 
    while(1);}
  if(calcR0 == 0){
    Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply"); 
    while(1);}
  
}

void loop() {
  MQ3.update();
  float sensor = MQ3.readSensor();
  HC06.println(sensor,3); //HC06 센서에 출력
  Serial.println(sensor,3);
  delay(1000); //Sampling frequency
}
