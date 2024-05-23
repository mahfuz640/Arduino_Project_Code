#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int r = 8;
int y = 9;
int g = 10;

int b1 = 5;
int b2 = 6;
int b3 = 7;
int b4 = 2;
int b5 = 3;
int b6 = 4;

const int poten = A0;

void setup() {
  Serial.begin(9600);

  pinMode(poten, INPUT);

  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);

  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(g, OUTPUT);

  lcd.backlight();
  lcd.init();
  lcd.clear();
  lcd.begin(16, 2);
}

void loop() {
  int b11 = digitalRead(b1);
  int b22 = digitalRead(b2);
  int b33 = digitalRead(b3);
  int b44 = digitalRead(b4);
  int b55 = digitalRead(b5);
  int b66 = digitalRead(b6);
  int pot = analogRead(poten);
  int volt = analogRead(pot);
  volt = pot / 3.9;

  Serial.print("volt ");
  Serial.println(volt);
  Serial.print(b11);
  Serial.print(b22);
  Serial.print(b33);
  Serial.print(b44);
  Serial.print(b55);
  Serial.print(b66);
  Serial.println();

  // Check voltage conditions and update LED states accordingly
  if (volt < 190) {
    lcd.setCursor(0, 1);
    lcd.print("U_voltage:");
    lcd.print(volt);
    lcd.print("v    ");
    digitalWrite(r, LOW);
    digitalWrite(y, LOW);
    digitalWrite(g, LOW);
    //digitalWrite(buzzer,HIGH);
    //delay(2000);
  } else if (volt > 240) {
    lcd.setCursor(0, 1);
    lcd.print("O_voltage:");
    lcd.print(volt);
    lcd.print("v    ");
    digitalWrite(r, LOW);
    digitalWrite(y, LOW);
    digitalWrite(g, LOW);
    //digitalWrite(buzzer,HIGH);
    delay(2000);
  } else { // Voltage is within acceptable range
    lcd.setCursor(0, 1);
    lcd.print("N_voltage:");
    lcd.print(volt);
    lcd.print("v    ");

    digitalWrite(r, HIGH);
    digitalWrite(y, HIGH);
    digitalWrite(g, HIGH);
    //digitalWrite(buzzer,LOW);
    delay(2000);
  }

  // Check other button conditions and update LED states accordingly
  if (b11 == HIGH) {
    digitalWrite(r, LOW);
    digitalWrite(y, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+2 Fault");
    delay(10000);
  }

  if (b22 == HIGH) {
    digitalWrite(y, LOW);
    digitalWrite(g, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 2+3 Fault");
    delay(10000);
  }

  if (b33 == HIGH) {
    digitalWrite(g, LOW);
    digitalWrite(r, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+3 Fault");
    delay(10000);
  }

  if (b44 == HIGH) {
    digitalWrite(r, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+gnd Fault");
    delay(10000);
  }

  if (b55 == HIGH) {
    digitalWrite(y, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 2+gnd Fault");
    delay(10000);
  }

  if (b66 == HIGH) {
    digitalWrite(g, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Line 3+gnd Fault");
    delay(10000);
  }

  if (b11 == LOW && b22 == LOW && b33 == LOW && b44 == LOW && b55 == LOW && b66 == LOW) {
    
    lcd.setCursor(0, 0);
    lcd.print("                               ");
    delay(1000);
  }
}
