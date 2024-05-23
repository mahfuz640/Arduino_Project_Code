#include <Servo.h>
#include <Wire.h>


float input_voltage = 0.0;
float temp=0.0;

float input_voltage1 = 0.0;
float temp1=0.0;

// horizontal servo
Servo horizontal;
int servoh = 90;
int servohLimitHigh = 180;
int servohLimitLow = 0;

Servo vertical;
int servov = 90;
int servovLimitHigh = 180;
int servovLimitLow = 0;

// LDR pin connections
int ldrTR = A3; // LDR top right
int ldrTL = A2; // LDR top left
int ldrBR = A1; // LDR bottom right
int ldrBL = A0; // LDR bottom left

/*// LDR pin connections
int ldrTR = A2; // LDR top right
int ldrTL = A3; // LDR top left
int ldrBR = A0; // LDR bottom right
int ldrBL = A1; // LDR bottom left
*/

  int dtime ; // change for debugging only
  int tol ;

  int avt ; // average value top
  int avd ; // average value bottom
  int avl ; // average value left
  int avr ; // average value right

  int dvert;  // check the difference of up and down
  int dhoriz; // check the difference of left and right
  int tr ; // top right
  int tl ; // top left
  int br ; // bottom right
  int bl ; // bottom left

   int analog_value ;
   int analog_value1 ;
float t1 ;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
 
  pinMode(A6,INPUT);
   horizontal.attach(10);
  vertical.attach(9);
  // move servos
  horizontal.write(50);
  vertical.write(50);
  
delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  int tr = analogRead(ldrTR); // top right
  int tl = analogRead(ldrTL); // top left
  int br = analogRead(ldrBR); // bottom right
  int bl = analogRead(ldrBL); // bottom left
   //int analog_value = analogRead(A6);
   //int analog_value1 = analogRead(A7);       ///solar voltage print 
//input_voltage = (analog_value * 8.0) / 1024.0;
//input_voltage1 = (analog_value1 * 5.0) / 1024.0;
//float batteryvoltage = input_voltage1*8;
//lcd.setCursor(0, 0);
//lcd.print("Solar: ");
//lcd.setCursor(6, 0);
//lcd.print(input_voltage      );

 
   tr = analogRead(ldrTR); // top right
   tl = analogRead(ldrTL); // top left
   br = analogRead(ldrBR); // bottom right
   bl = analogRead(ldrBL); // bottom left

   dtime = 0; // change for debugging only
   tol = 50;

   avt = (tl + tr) / 2; // average value top
   avd = (bl + br) / 2; // average value bottom
   avl = (tl + bl) / 2; // average value left
   avr = (tr + br) / 2; // average value right

   dvert = avt - avd;  // check the difference of up and down
   dhoriz = avl - avr; // check the difference of left and right

  Serial.print(tl);
  Serial.print(" ");
  Serial.print(tr);
  Serial.print(" ");
  Serial.print(bl);
  Serial.print(" ");
  Serial.print(br);
  Serial.print("  ");
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("  ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.print("  ");
  Serial.print(servov);
  Serial.print("   ");
  Serial.print(servoh);
  Serial.println(" ");

  if (-1 * tol > dvert || dvert > tol) {
if (avt > avd) {
    servov = ++servov;
      if (servov > servovLimitHigh) {
     servov = servovLimitHigh;
      }
    }
    else if (avt < avd) {
     servov = --servov;
      if (servov < servovLimitLow) {
      servov = servovLimitLow;
      }
    }
    vertical.write(servov);
  }

  if (-1 * tol > dhoriz || dhoriz > tol) {
    if (avl > avr) {
     servoh = --servoh;
      if (servoh < servohLimitLow) {
       servoh = servohLimitLow;
      }
    }
    else if (avl < avr) {
     servoh = ++servoh;
      if (servoh > servohLimitHigh) {
      servoh = servohLimitHigh;
      }
    }
    else if (avl = avr) {
     // nothing
    }
    horizontal.write(servoh);
  }
  delay(dtime);
  
}
