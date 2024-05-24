#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


//Pin define
int r=8;
int y=9;
int g=10;


int a0=A0;
int a1=A1;   //Node MCU ar shate connected hobe 
int a2=A2;
int a3=A3;
int d11=11;
int d12=12;


int b1 = 2;  
int b2 = 3;
int b3 = 4;    //microcontroller ar pin gulo variable a declear kore deya
int b4 = 5;
int b5 = 6;
int b6 = 7;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // serial monitor ar code 

  lcd.begin();
  lcd.backlight();


  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);

  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(g, OUTPUT);


  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(d11, OUTPUT);
  pinMode(d12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int b11 = digitalRead(b1);     //pin gulo seral monitor a check diye dekhte hobe variable nite hobe 
  int b22 = digitalRead(b2);
  int b33 = digitalRead(b3);
  int b44 = digitalRead(b4);
  int b55 = digitalRead(b5);
  int b66 = digitalRead(b6);



  Serial.println(b11);    //pin gulo seral monitor a check diye dekhte hobe variable nite hobe and akhne dekha jabe output serial monitor a show hobe 
  Serial.println(b22);
  Serial.println(b33);
  Serial.println(b44);
  Serial.println(b55);
  Serial.println(b66);


  if (b11 == LOW) {
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  analogWrite(a0,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+3 Fault    ");
     lcd.setCursor(0, 1);
    lcd.print("Temporary Fault    ");
    delay(5000);  
    }
    
  else
  {
    digitalWrite(r, HIGH);
    digitalWrite(g, HIGH);
    analogWrite(a0,HIGH);
    
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");

}



  if (b22 ==LOW ) {
  digitalWrite(y, LOW);
  digitalWrite(g, LOW);
  analogWrite(a1,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 2+3 Fault    ");
    lcd.setCursor(0, 1);
    lcd.print("Temporary Fault    ");
    delay(5000);  
    }
    else {
    digitalWrite(y, HIGH);
    digitalWrite(g, HIGH);
    analogWrite(a1,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("            ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
}


   
 if (b33 == LOW) {
  digitalWrite(r, LOW);

  analogWrite(a2,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+gnd Fault    ");
     lcd.setCursor(0, 1);
    lcd.print("Temporary Fault    ");
    delay(5000);  
    }else {
    digitalWrite(r, HIGH);
    analogWrite(a2,HIGH);
 
    lcd.setCursor(0, 0);
    lcd.print("                   ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
}




if (b44 == LOW) {
  digitalWrite(y, LOW);
 analogWrite(a3,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 2+gnd Fault    ");
    lcd.setCursor(0, 1);
    lcd.print("Temporary Fault    ");
    delay(5000);  
    }else {
    digitalWrite(y, HIGH);
    analogWrite(a3,HIGH);
  
    lcd.setCursor(0, 0);
    lcd.print("                     ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
}


if (b55 == LOW) {
  
  digitalWrite(g, LOW);
  digitalWrite(d11,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 3+gnd Fault    ");
    lcd.setCursor(0, 1);
    lcd.print("Temporary Fault    ");
    delay(5000);  
    }else {
   
    digitalWrite(g, HIGH);
      digitalWrite(d11,HIGH);

    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
}
if (b66 == LOW) {
    digitalWrite(r, LOW);
  digitalWrite(g, LOW);
   digitalWrite(y, LOW);
   digitalWrite(d12,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Fault Permanent    ");
       lcd.setCursor(0, 1);
    lcd.print("                   "); 
  delay(5000);
    }else {
    digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
   digitalWrite(y, HIGH);
    digitalWrite(d12,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
}

}
