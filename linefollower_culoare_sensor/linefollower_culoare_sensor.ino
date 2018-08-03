#include <QTRSensors.h>
#include <Servo.h> 
Servo servo;
int enA = 6;
int in1 = 2;
int in2 = 3;
// motor 2
int enB = 4;
int in3 = 5;
int in4 = 9;
int sensora = A5;
#define S0 10
#define S1 11
#define S2 12
#define S3 7
#define sensorOut A4
int frequency = 0;
int rosu,albastru,galben;
int i,j;
int color[5];
int maxi;
#define NUM_SENSORS   4     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN     // emitter is controlled by digital pin 2
int ok=0;
int oke=0;
int turn=0;
// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {A3,A2,A1,A0},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];


void setup()
{ servo.attach(8);
  servo.write(60);
   pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in4, OUTPUT);
  //spate(150);
  pinMode(in3, OUTPUT);
  pinMode(sensora, INPUT);
  delay(500);
  servo.detach();
     // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 2; i < 6; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 2; i < 6; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtrrc.read(sensorValues); instead of unsigned int position = qtrrc.readLine(sensorValues);
  if(ok==0)
  {
  if(digitalRead(sensora)==LOW)
  {
   stop();
   delay(1500);
   servo.attach(8);
   servo.write(170); 
   delay(1000); 
   servo.detach();
  rosu=0;
  albastru=0;
  galben=0;
  for(j=1;j<=2;j++)
  {
  for(i=0;i<5;i++)
  {// Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 10,30,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  rosu=rosu+frequency;
  //delay(0);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output freqency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 10,65,255,0);
  galben=galben+frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 10,59,255,0); 
  albastru=albastru+frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  // delay(100);
  }
  if(rosu>albastru)
  { maxi=rosu;
    //Serial.println("rosu");
  }
  else
  {
    maxi=albastru;
   // Serial.println("albastru");
  }
  if(galben>maxi)
  {
    maxi=galben;
  }
  if(maxi==rosu)
  {
    
    color[j]=1;
  }
  else  if(maxi==albastru)
  {
    
    color[j]=3;
  }
  else  if(maxi==galben)
  {
    
    color[j]=2;
  }
  if(color[1]!=color[2])
  {
    j=1;
  }
  else
  {
    oke=color[1];
  }
  }
   dreapta(128);
   delay(270);
   stop();
   delay(700);
   spate(140);
   delay(520);
   stop();
   delay(500);
   dreapta(128);
   delay(150); //180
   ok=1;
   
   
  }
  
}
  if(ok==1)
  {
  if(sensorValues[0]==1000 && sensorValues[1]==1000 && sensorValues[2]==1000 && sensorValues[3]==1000)
  {
    //stanga
  if(oke==1  )  
  {stanga(130);
   delay(500);
   fata(130);
   delay(170);
   stop();
   delay(500);
   servo.attach(8);
   servo.write(60); 
   delay(1000); 
   servo.detach();
   spate(140);
   delay(500);
   stop();
   delay(500);
   dreapta(128);
   delay(500);
   stop();
   delay(570);
   stanga(130);
   delay(30);
    stop();
   delay(570);
    fata(130);
   delay(20);
   ok=0; }
   //dreapta;
    if(oke==3)  
  {
   dreapta(130);
   delay(60);//120
   fata(130);
   delay(200);
   stop();
   delay(500);
   servo.attach(8);
   servo.write(60); 
   delay(1000); 
   servo.detach();
   spate(140);
   delay(500);
   stop();
   delay(500);
  dreapta(128);
   delay(250);
   stop();
   delay(500);
    fata(130);
   delay(30);
   stanga(130);
   delay(30);
    stop();
   ok=0;}
    if(oke==2)  
  {
   //centru
   fata(130);
   delay(100);
   stop();
   delay(500);
   servo.attach(8);
   servo.write(60); 
   delay(1000); 
   servo.detach();
   spate(130);
   delay(500);
   dreapta(128);
   delay(450);
   stop();
   delay(500);
   /*fata(130);
   delay(10);*/
   ok=0;
  }
  }
  }
  unsigned int position = qtrrc.readLine(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
 /* for (int i = 2; i <= 5; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(' ');
  }
  Serial.print('\n');*/
  Serial.print(sensorValues[0]);
  Serial.print(' ');
    Serial.print(sensorValues[1]);
  Serial.print(' ');
    Serial.print(sensorValues[2]);
  Serial.print(' ');
    Serial.print(sensorValues[3]);
  Serial.print(' ');
  Serial.print('\n');
  delay(62);
 if(position==3000  || position==0)
{
 stanga(200);
   //delay(10);
    stop();
    delay(10);
    delayMicroseconds(1);
   /* turn=turn+1;
    if(turn==150 ||((sensorValues[0]>0) && (sensorValues[1]>0) &&(sensorValues[2]>0) &&(sensorValues[3]>0)))
    {
      fata(130);
      delay(20);
    }*/
}
 else if(position!=3000  || position!=0)
 {turn=0;
  if(position<1000)
  {
    dreapta(150);
    delay(5);
    stop();
    delayMicroseconds(1);
  }
  
  
 else if(position>1400)
  {
    
    stanga(170);
    delay(5);
    stop();
    delayMicroseconds(1);
  }
  else
  {
    fata(150);
    delay(5);
    stop();
    delayMicroseconds(1);
  }
 }
 }


void fata(int x)
{
   digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
  analogWrite(enA, x);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, x);
  delay(40);
 
}
void stanga(int x)
{
   digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
  analogWrite(enA, x);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enB, x);
 delay(50);
 
}
void dreapta(int x)
{
   digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
  analogWrite(enA, x);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, x);
  delay(50);
 
}
void stop()
{
  digitalWrite(in1, LOW);

  analogWrite(enA, 0);
  digitalWrite(in3, LOW);
  
  analogWrite(enB, 0);
  
}
void spate(int x)
{
   digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
  analogWrite(enA, x);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, x);
  delay(35);
 
}
