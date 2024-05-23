#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial gsmSerial(7, 8); // GSM module
SoftwareSerial gpsSerial(9, 10); // GPS module

TinyGPSPlus gps; // Create a TinyGPS++ object

// Pin definitions
int o1 = 11;
int o2 = 12;
int o3 = 13;
int o4 = A0;
int o5 = A1;

int buzzer = A2;

int b1 = 2;
int b2 = 3;
int b3 = 4;
int b4 = 5;
//int b5 = 6;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  gsmSerial.begin(9600); // Begin GSM module communication
  gpsSerial.begin(9600); // Begin GPS module communication
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
//  pinMode(b5, INPUT);
  pinMode(o1, OUTPUT);
  pinMode(o2, OUTPUT);
  pinMode(o3, OUTPUT);
  pinMode(o4, OUTPUT);
  pinMode(o5, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
}

void loop() {
  // Process GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // You can access GPS data using the TinyGPS++ functions
      if (gps.location.isValid()) {
        // Process other tasks
        Serial.println(gps.location.lat(), 6);
        Serial.println(gps.location.lng(), 6);
          lcd.setCursor(0, 1);
    lcd.print("T. Impedace=100ohm        ");
        lcd.setCursor(0, 2);
        lcd.print("lat:");
        lcd.print(gps.location.lat(), 6);

        lcd.setCursor(0, 3);
        lcd.print("long:");
        lcd.print(gps.location.lng(), 6);
       bbb();
      }
    }
  }
}

void bbb() {
  int b11 = digitalRead(b1);
  int b22 = digitalRead(b2);
  int b33 = digitalRead(b3);
  int b44 = digitalRead(b4);
//  int b55 = digitalRead(b5);

        Serial.print(b11);
        Serial.print(b22);
        Serial.print(b33);
        Serial.println(b44);
     



  
  if (b11 == HIGH) {
    sendSMS("Line 1+2 Fault & Impedance Was recorded 80ohm ", gps.location.lat(), gps.location.lng());
    digitalWrite(o1, LOW);
    digitalWrite(o2, LOW);    
    analogWrite(buzzer, 1023);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+2 Fault    ");
     lcd.setCursor(0, 1);
    lcd.print("Total Impedace=80ohm         ");
    delay(5000);

    
  } else {
    digitalWrite(o1, HIGH);
     digitalWrite(o2, HIGH);
    analogWrite(buzzer, 0);
    lcd.setCursor(0, 0);
    lcd.print("                        ");
  }

  if (b22 == HIGH) {
    sendSMS("Line 2+3 Fault & Impedance Was recorded 60ohm ", gps.location.lat(), gps.location.lng());
    digitalWrite(o2, LOW);
        digitalWrite(o3, LOW);

    analogWrite(buzzer, 1023);
    lcd.setCursor(0, 0);
    lcd.print("Line 2+3 Fault    ");
      lcd.setCursor(0, 1);
    lcd.print("Total Impedace=60ohm      ");
    delay(5000);
  } else {
    digitalWrite(o2, HIGH);
        digitalWrite(o3, HIGH);

    analogWrite(buzzer, 0);    
    lcd.setCursor(0, 0);
    lcd.print("                      ");
  }

  if (b33 == HIGH) {
    sendSMS("Line 1+gnd Fault & Impedance Was recorded 40ohm ", gps.location.lat(), gps.location.lng());
    digitalWrite(o1, LOW);
    
    analogWrite(buzzer, 1023);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+gnd Fault    ");

      lcd.setCursor(0, 1);
    lcd.print("Total Impedace=40ohm        ");
    delay(5000);
  } else {
    digitalWrite(o3, HIGH);
    analogWrite(buzzer, 0);
    lcd.setCursor(0, 0);
    lcd.print("                   ");
  }

  if (b44 == HIGH) {
    sendSMS("Line 2+gnd Fault  & Impedance Was recorded 20ohm ", gps.location.lat(), gps.location.lng());
    digitalWrite(o2, LOW);
    analogWrite(buzzer, 1023);    
    lcd.setCursor(0, 0);
    lcd.print("Line 2+gnd Fault");
      lcd.setCursor(0, 1);
    lcd.print("Total Impedace=20ohm          ");
    delay(5000);
  } else {
    digitalWrite(o4, HIGH);
    analogWrite(buzzer, 0);    
    lcd.setCursor(0, 0);
    lcd.print("                     ");    
  }


}


void sendSMS(String message, float latitude, float longitude) {
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  gsmSerial.print("AT+CMGS=\"+01886501961\""); // Replace with the recipient's phone number
  gsmSerial.write(0x0D); // Enter
  delay(100);
  gsmSerial.print(message + " - Google Maps Link:  ");
  gsmSerial.print("http://maps.google.com/maps?q=");
  gsmSerial.print(latitude, 6);
  gsmSerial.print(",");
  gsmSerial.print(longitude, 6);
  gsmSerial.write(0x1A); // Ctrl+Z (End of SMS)
  delay(100);
}
