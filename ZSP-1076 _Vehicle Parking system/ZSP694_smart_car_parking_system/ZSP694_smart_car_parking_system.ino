#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Servo myservo;

int irsen1=2;
int irsen2=7;
int irsen3=4;
int irsen4=5;
int irsen5=6;
int node5=10;
int node6=11;
int node7=12;
int node8=13;
int ir1;
int ir2;
int ir3;
int ir4;
int ir5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
myservo.attach(9);
  myservo.write(80); 
pinMode(irsen1,INPUT);
pinMode(irsen2,INPUT);
pinMode(irsen3,INPUT);
pinMode(irsen4,INPUT);
pinMode(irsen5,INPUT);
pinMode(node5,OUTPUT);
pinMode(node6,OUTPUT);
pinMode(node7,OUTPUT);
pinMode(node8,OUTPUT);



lcd.init();
lcd.backlight();
}
void (*resetFunc)(void)=0;
void loop() {
  // put your main code here, to run repeatedly:
  ir1=digitalRead(irsen1);
  ir2=digitalRead(irsen2);
  ir3=digitalRead(irsen3);
  ir4=digitalRead(irsen4);
  ir5=digitalRead(irsen5);
  Serial.println(ir1);

       if(ir1==0 && ir2==0 && ir3==0 && ir4==0 && ir5==0){
    myservo.detach(); // sets the servo position to 90 degrees
  lcd.setCursor(0, 0);
  lcd.print(" Parking Is Full    ");
   lcd.setCursor(0, 1);
  lcd.print("      Sorry          ");
  delay(2000);
  resetFunc();
    }

 if(ir2==0){
 lcd.setCursor(0, 0);
  lcd.print("P1:");
  lcd.println("Full       ");
  digitalWrite(node5,HIGH);
    }
 if(ir2==1){
 lcd.setCursor(0, 0);
  lcd.print("P1:");
  lcd.println("Free       ");
    digitalWrite(node5,LOW);

    }
  if(ir3==0){
 lcd.setCursor(8, 0);
  lcd.print("P2:");
   lcd.println("Full       ");
     digitalWrite(node6,HIGH);

   delay(1000);
    }
 if(ir3==1){
 lcd.setCursor(8, 0);
  lcd.print("P2:");  
   lcd.println("Free       ");
   digitalWrite(node6,LOW);

    }  
if(ir4==0){
 lcd.setCursor(0, 1);
  lcd.print("P3:");
   lcd.println("Full       ");
   digitalWrite(node7,HIGH);

    }
 if(ir4==1){
 lcd.setCursor(0, 1);
  lcd.print("P3:");
   lcd.println("Free       ");
  digitalWrite(node7,LOW);

    }  

if(ir5==0){
 lcd.setCursor(8, 1);
  lcd.print("P4:");
   lcd.println("Full         ");
     digitalWrite(node8,HIGH);

    }
 if(ir5==1){
 lcd.setCursor(8, 1);
  lcd.print("P4:");
   lcd.println("Free      ");
     digitalWrite(node8,LOW);
      delay(1000);
    } 
  if(ir1==0){
  myservo.write(0);   delay(2000);
    myservo.write(80); // sets the servo position to 90 degrees
 }
}
