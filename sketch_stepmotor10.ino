/* Step Motor Control sketch(code)

We have here, a positioning controller system, with the Arduino Uno microcontroller board.
It uses the Step Motor, coded 28byj-48,  the Driver, coded uln2003 and the Incremental Rotary
Encoder, coded ky-040.
Stages of the Control Process : Direct drive, Reverse drive and Recovery of Positioning, after
an eventual fault of the electrical Power Supply.
This project does not involves any Limit Switches, because it involves the use of an Incremental
Rotary Encoder.
Find all the hardware connections, in the void setup section.

Development Year : 2024
Control System Accuracy : +/- 1 (one) pulse of encoder.
Acknowledgements : Mathias Hertel (mathertel), by his Library 'RotaryEncoder' (in github.com)

Read,please, the README and the Usage sections, for the present sketch(code).
*/

// opening the libraries of the C++ programming language (built-in and imported ).
#include <EEPROM.h>  // Library built-in

#include "RotaryEncoder.h"   // Library imported
RotaryEncoder encoder(A2,A3);

#define abs(x) ((x)>0?(x):-(x))   // Modulo Function

// initialization of variables.
unsigned long ton;
unsigned long toff;
const unsigned long period = 20;
const float f1 = .35; 
const float f3 = .4;
const int value1 = 4;
const unsigned long nmax = 500;
const unsigned long speed = 9600;
int comando = 1;
float count = 1;
int stopbutton=0;
const int buttonpin = 13;
byte deltateta = EEPROM.read(1);
byte posit = deltateta;
//int pos = 257*deltateta-32768;
byte flag1 = EEPROM.read(2);
byte flag2 = EEPROM.read(3);
byte flag3 = EEPROM.read(5);
byte posit1 = EEPROM.read(6);
byte count1 = EEPROM.read(4);
const int value2 = 4;
const int value3 = 5;

void setup() {
  // put your setup code here, to run once:
// step motor phases initialization and else connections:
pinMode(2,OUTPUT); // initialize phase1 in pin2, as a digital input (IN1) of uln2003 driver.
pinMode(4,OUTPUT); // initialize phase2 in pin4, as a digital input (IN2) of uln2003 driver.
pinMode(7,OUTPUT); // initialize phase3 in pin7, as a digital input (IN3) of uln2003 driver.
pinMode(8,OUTPUT); // initialize phase4 in pin8, as a digital input (IN4) of uln2003 driver.
// connector of 28byj-48 step motor : connect in the slot, over uln2003 board.
// feed the uln2003 board and the Arduino board : + (connect to +5v), GND (connect to GrouND).
pinMode(3,OUTPUT); // initialize pwm out in pin3, for void loop running indicator (connect to the anode).
// indicator : a 5mm blue led, in second plane. Insert a 220 ohm resistor.
pinMode(buttonpin,INPUT); // initialize stop button in pin13.
// connections : connect to +5v one of two pins of the stop button;
// pin13 to another pin of the stop button and (in pull-down) from this point to GrouND through a 10Kohm resistor.
pinMode(A2,INPUT); // initialize analog input A2 to connect with DT pin of encoder.
pinMode(A3,INPUT); // initialize analog input A3 to connect with CLK pin of encoder.
// the else pins of encoder : + (connect to +5v), GND (connect to GrouND) and SW (not used).
pinMode(5,OUTPUT); // initialize pwm out in pin5 : connect to the smd green led (at left side of step motor).
pinMode(6,OUTPUT); // initialize pwm out in pin6 : connect to the smd blue led (at left side of step motor).
pinMode(9,OUTPUT); // initialize pwm out in pin9 : connect to the smd green led (at right side of step motor).
pinMode(10,OUTPUT);// initialize pwm out in pin10 : connect to the smd blue led (at right side of step motor).
// insert a resistor of 220 ohm in all the connections, for smd led's above.
Serial.begin(speed);
Serial.println("começa aqui esse run");
Serial.print("deltateta=");
Serial.println(deltateta);
Serial.print("posit=");
Serial.println(posit);
int comando = 1;
float count = 1.00;
int stopbutton=1;

if(flag2 != 1 && (posit >= 0)) {   
  
  EEPROM.write( 6, posit );
  count1 = count1+1;
  EEPROM.write( 4 , count1 );
  
  unsigned long n = 1;
  analogWrite(3,value1); // turns to HIGH led, void loop running indicator.
  analogWrite(6,value3);

  Serial.println("xxxxxxxxxxxxxxxx Direct Adj. xxxxxxxxxxxxxxxx");
     
 while((n >= 1 && n <= nmax) && ((posit != (19-deltateta) && posit != (255-deltateta)))) { 
 // step motor runs in the first gear and in the counterclockwise way, para Adj.
    
  ton = 7.00;
  toff = 13.00;
 // encoder's informations lecture.

  static byte pos = deltateta;
  encoder.tick();

byte newPos = encoder.getPosition();
// if the angular position was changed, shows the new value on the Serial Monitor.

if( pos != newPos ){
  Serial.println( newPos );
pos = newPos;
posit = newPos;
}
  digitalWrite(4,HIGH);
  delay(ton);
  digitalWrite(4,LOW);
  delay(toff);

  digitalWrite(2,HIGH);
  delay(ton);
  digitalWrite(2,LOW);
  delay(toff);

  digitalWrite(8,HIGH);
  delay(ton);
  digitalWrite(8,LOW);
  delay(toff);

  digitalWrite(7,HIGH);
  delay(ton);
  digitalWrite(7,LOW);
  delay(toff);

  n = n+1;

analogWrite(9,value2);
delay(1);
analogWrite(9,0);
delay(1);
   
  }

EEPROM.write( 2 , 1 );
flag1 = EEPROM.read(2);
analogWrite(6,0);
}
  

if(flag1 != 1 && (posit >= 0)) {

  unsigned long n = 1;
  analogWrite(3,value1); // turns to HIGH led, void loop running indicator.
  analogWrite(10,value3);

Serial.println("xxxxxxxxxxxxxxxx REV Adj. xxxxxxxxxxxxxxxx");
    
if(count1 != 0) {

  while((n >= 1 && n <= nmax) && posit != (256-(18-(255-posit1))+(255-deltateta)) && posit != ((256-(19-(255-posit1+deltateta))-(19-(255-posit1))))) { 
  // step motor runs in the third gear and in the clockwise way, para Adj.
  ton = 8.00;
  toff = 12.00;
  
 // encoder's informations lecture.

 static byte pos = deltateta;
 encoder.tick();

byte newPos = encoder.getPosition();
// if the angular position was changed, shows the new value on the Serial Monitor.

if( pos != newPos ){
  Serial.println( newPos );
pos = newPos;
posit = newPos;
}

  digitalWrite(2,HIGH);
  delay(ton);
  digitalWrite(2,LOW);
  delay(toff);

  digitalWrite(4,HIGH);
  delay(ton);
  digitalWrite(4,LOW);
  delay(toff);

  digitalWrite(7,HIGH);
  delay(ton);
  digitalWrite(7,LOW);
  delay(toff);

  digitalWrite(8,HIGH);
  delay(ton);
  digitalWrite(8,LOW);
  delay(toff);

  n = n+1;

analogWrite(5,value2);
delay(1);
analogWrite(5,0);
delay(1);

  }
} else
{   while((n >= 1 && n <= nmax) && (posit != (19-deltateta) && posit != (256-(deltateta-237)))) { 
  // step motor runs in the third gear and in the clockwise way, para Adj.
  ton = 8.00;
  toff = 12.00;
  
 // encoder's informations lecture.

 static byte pos = deltateta;
 encoder.tick();

byte newPos = encoder.getPosition();
// if the angular position was changed, shows the new value on the Serial Monitor.

if( pos != newPos ){
  Serial.println( newPos );
pos = newPos;
posit = newPos;
}

  digitalWrite(2,HIGH);
  delay(ton);
  digitalWrite(2,LOW);
  delay(toff);

  digitalWrite(4,HIGH);
  delay(ton);
  digitalWrite(4,LOW);
  delay(toff);

  digitalWrite(7,HIGH);
  delay(ton);
  digitalWrite(7,LOW);
  delay(toff);

  digitalWrite(8,HIGH);
  delay(ton);
  digitalWrite(8,LOW);
  delay(toff);

  n = n+1;

analogWrite(5,value2);
delay(1);
analogWrite(5,0);
delay(1);
  
}
}
EEPROM.write( 5, 1 );
flag3 = EEPROM.read(5);
analogWrite(10,0);
}
Serial.println("the encoder rotates coupled to the step motor...");

}

void loop() {
  // put your main code here, to run repeatedly:

if(count >= 0.00 && comando != 0 ) {
Serial.println(count, 2);
}

if (comando == 1) { 
stopbutton = 0;
unsigned long n = 1;
analogWrite(3,value1); // turns to HIGH led, void loop running indicator.
EEPROM.write( 3 , 0 );
EEPROM.write( 2 , 1 );
Serial.println("xxxxxxxxxxxxxxxx Direct Main xxxxxxxxxxxxxxxx");

while(n >= 1 && n <= nmax && flag3 != 1) { // step motor runs in the third gear and in the clockwise way.

ton = 8.00;
toff = 12.00;
if (stopbutton != 1) {
stopbutton=digitalRead(buttonpin);
}

// encoder's informations lecture.
  
static byte pos = 0;
encoder.tick();

byte newPos = encoder.getPosition();
// if the angular position was changed, shows the new value on the Serial Monitor.

if( pos != newPos ){
  Serial.println( newPos );
pos = newPos;
posit = newPos;
}
EEPROM.write( 1 , posit );

digitalWrite(2,HIGH);
delay(ton);
digitalWrite(2,LOW);
delay(toff);

digitalWrite(4,HIGH);
delay(ton);
digitalWrite(4,LOW);
delay(toff);

digitalWrite(7,HIGH);
delay(ton);
digitalWrite(7,LOW);
delay(toff);

digitalWrite(8,HIGH);
delay(ton);
digitalWrite(8,LOW);
delay(toff);

analogWrite(5,value2);
delay(1);
analogWrite(5,0);
delay(1);

if (stopbutton != 1) {
stopbutton=digitalRead(buttonpin);
}

EEPROM.write( 1 , posit );

n = n+1;
}
n = 1;

if(count == 1.00) {
float(ton);
float(toff);
ton = 8.00;
toff = 12.00;
Serial.print("f3:"); 
Serial.println(f3, 2);
Serial.print("ton="); 
Serial.println(ton, 2);
Serial.print("toff=");
Serial.println(toff, 2);

}

Serial.println("xxxxxxxxxxxxxxxx REV Main xxxxxxxxxxxxxxxx");

while(n >= 1 && n <= nmax) { // step motor runs in the first gear and in the counterclockwise way.

EEPROM.write( 3 , 1 );

if (stopbutton == 1) {   // setting the directional flow flags.
  
  EEPROM.write( 2 , 1 );
  EEPROM.write( 4 , 0);
  EEPROM.write( 5 , 0 );
} else {
  EEPROM.write( 2 , 0 );
  EEPROM.write( 5 , 0 ); 
  flag3 = EEPROM.read(5);
}
unsigned long (ton);
unsigned long (toff);
ton = 7;
toff = 13;

if (stopbutton != 1) {
stopbutton=digitalRead(buttonpin);
}

// encoder's informations lecture.

static byte pos = 0;
encoder.tick();

byte newPos = encoder.getPosition();
// if the angular position was changed, shows the new value on the Serial Monitor.

if( pos != newPos ){
  Serial.println( newPos );
  pos = newPos;
  posit = newPos;
}
EEPROM.write( 1 , posit );

digitalWrite(4,HIGH);
delay(ton);
digitalWrite(4,LOW);
delay(toff);

digitalWrite(2,HIGH);
delay(ton);
digitalWrite(2,LOW);
delay(toff);

digitalWrite(8,HIGH);
delay(ton);
digitalWrite(8,LOW);
delay(toff);

digitalWrite(7,HIGH);
delay(ton);
digitalWrite(7,LOW);
delay(toff);

analogWrite(9,value2);
delay(1);
analogWrite(9,0);
delay(1);

if (stopbutton != 1) {
stopbutton=digitalRead(buttonpin);
}

EEPROM.write( 1 , posit );
 
n = n+1;
}

if(count == 1.00) {
float(ton);
float(toff);
 ton = 7.00;
 toff = 13;
 Serial.print("f1:"); 
 Serial.println(f1, 2);
 Serial.print("ton="); 
 Serial.println(ton, 2);
 Serial.print("toff="); 
 Serial.println(toff, 2);

}
  if (stopbutton != 1) {
  int stopbutton=digitalRead(buttonpin);
  }

if (stopbutton == 1) {   // setting the directional flow flags.

  EEPROM.write( 2 , 1 );
  EEPROM.write( 4 , 0);
  EEPROM.write( 5 , 0 );
} else {
  EEPROM.write( 2 , 0 );
  EEPROM.write( 5 , 0 );
  flag3 = EEPROM.read(5);
}


if (stopbutton == 1) { 
  comando = 0;
} else {
  comando = 1;
  }

count = count+1.00;
stopbutton=0;

}
}
