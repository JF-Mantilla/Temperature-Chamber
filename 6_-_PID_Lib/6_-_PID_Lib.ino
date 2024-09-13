#include <PID_v1.h>

// AC Control V1.1
//
// This Arduino sketch is for use with the heater 
// control circuit board which includes a zero 
// crossing detect function and an opto-isolated TRIAC.
//
// AC Phase control is accomplished using the internal 
// hardware timer1 in the Arduino
//
// Timing Sequence
// * timer is set up but disabled  - Timer config pero deshabilitado
// * zero crossing detected on pin 2 - Pin2 detecta cruce por 0 de la señal AC
// * timer starts counting from zero - timer empieza a contar desde cero (interno arduino)
// * comparator set to "delay to on" value 
// * counter reaches comparator value
// * comparator ISR turns on TRIAC gate
// * counter set to overflow - pulse width
// * counter reaches overflow
// * overflow ISR turns off TRIAC gate
// * TRIAC stops conducting at next zero cross


// The hardware timer runs at 16MHz. Using a
// divide by 256 on the counter each count is 
// 16 microseconds.  1/2 wave of a 60Hz AC signal
// is about 520 counts (8,333 microseconds).



#include <avr/io.h>
#include <avr/interrupt.h>

#include "DHT.h"

#include "max6675.h" // Librería para la termocupla

#define DHTPIN 13 //pin donde está conectado la termocupla
#define DHTTYPE DHT22
int thermoDO = 10;
int thermoCS = 11;
int thermoCLK = 12;

#define DETECT 2  //zero cross detect
#define GATE 9    //TRIAC gate
#define PULSE 4   //trigger pulse width (counts)

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
DHT dht(DHTPIN, DHTTYPE);

int per = 0;
int i=483;
float tempDHT;

//variables pid
double Referencia,Input,Output,Min=0,Max=100;
float Kp = 17,Ki = 100,Kd = 0;
PID myPID(&Input,&Output,&Referencia,Kp,Ki,Kd,DIRECT);

void setup(){
  Referencia = 60; //*.*.*.*.*.*.*. INGRESE EL VALOR DE TEMPERATURA DESEADO .*.*.*.*.*.*.*.
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(Min,Max);
  myPID.SetSampleTime(300);

   
  Serial.begin(9600);
  dht.begin();
  Serial.println("MAX6675 initialization / DHT initialization");
  delay(500);
  // set up pins
  pinMode(DETECT, INPUT);     //zero cross detect
  digitalWrite(DETECT, HIGH); //enable pull-up resistor
  pinMode(GATE, OUTPUT);      //TRIAC gate control

  

  // set up Timer1 
  //(see ATMEGA 328 data sheet pg 134 for more details)
  OCR1A = 100;      //initialize the comparator
  TIMSK1 = 0x03;    //enable comparator A and overflow interrupts
  TCCR1A = 0x00;    //timer control registers set for
  TCCR1B = 0x00;    //normal operation, timer disabled


  // set up zero crossing interrupt
  attachInterrupt(0,zeroCrossingInterrupt, RISING);    
    //IRQ0 is pin 2. Call zeroCrossingInterrupt 
    //on rising signal

}  

//Interrupt Service Routines

void zeroCrossingInterrupt(){ //zero cross detect   
  TCCR1B=0x04; //start timer with divide by 256 input
  TCNT1 = 0;   //reset timer - count from zero
}

ISR(TIMER1_COMPA_vect){ //comparator match
  digitalWrite(GATE,HIGH);  //set TRIAC gate to high
  TCNT1 = 65536-PULSE;      //trigger pulse width
}

ISR(TIMER1_OVF_vect){ //timer1 overflow
  digitalWrite(GATE,LOW); //turn off TRIAC gate
  TCCR1B = 0x00;          //disable timer stopd unintended triggers
}

void loop(){ // sample code to exercise the circuit  */*/*/*/*/*/
  
// Control PI
Input = thermocouple.readCelsius();
myPID.Compute();
per = Output;

//per = 0;
//if(per<0){per=0;}
//if(per>100){per=100;}


OCR1A = int(483 - 4.18*per);
 



Serial.print(per);
Serial.print(",");
Serial.println(thermocouple.readCelsius());
//Serial.print(",");
//Serial.println(tempDHT = dht.readTemperature());
delay(300);                             

}
