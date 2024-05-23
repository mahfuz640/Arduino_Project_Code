#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//SoftwareSerial gsmSerial(7, 8); // GSM module
//SoftwareSerial gpsSerial(9, 10); // GPS module

//TinyGPSPlus gps; // Create a TinyGPS++ object

// Pin definitions
int r = 8;
int y = 9;
int g = 10;

int buzzer = A2;

int b1 = 2;
int b2 = 3;
int b3 = 4;
int b4 = 5;
int b5 = 6;
int b6 = 7;

void setup() {
  Serial.begin(9600);

  lcd.backlight();
 gsmSerial.begin(9600); // Begin GSM module communication
 gpsSerial.begin(9600); // Begin GPS module communication
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);

  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(g, OUTPUT);

 pinMode(buzzer, OUTPUT);
  
}

void loop() {
  // Process GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // You can access GPS data using the TinyGPS++ functions
      if (gps.location.isValid()) {
        // Process other tasks
        Serial.print(gps.location.lat(), 6);
        Serial.println(gps.location.lng(), 6);
        
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
  int b55 = digitalRead(b5);

  if (b11 == HIGH) {
    sendSMS("Line 1+2 Fault", gps.location.lat(), gps.location.lng());
    digitalWrite(o1, HIGH);
    analogWrite(buzzer, 1023);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+2 Fault    ");
    delay(5000);
  } else {
    digitalWrite(o1, LOW);
    analogWrite(buzzer, 0);
    lcd.setCursor(0, 0);
    lcd.print("                        ");
  }

  if (b22 == HIGH) {
    sendSMS("Line 2+3 Fault", gps.location.lat(), gps.location.lng());
    digitalWrite(o2, HIGH);
    analogWrite(buzzer, 1023);
    lcd.setCursor(0, 0);
    lcd.print("Line 2+3 Fault    ");
    delay(5000);
  } else {
    digitalWrite(o2, LOW);
    analogWrite(buzzer, 0);    
    lcd.setCursor(0, 0);
    lcd.print("                      ");
  }

  if (b33 == HIGH) {
    sendSMS("Line 1+3 Fault", gps.location.lat(), gps.location.lng());
    digitalWrite(o3, HIGH);
    analogWrite(buzzer, 1023);
    lcd.setCursor(0, 0);
    lcd.print("Line 1+3 Fault    ");
    delay(5000);
  } else {
    digitalWrite(o3, LOW);
    analogWrite(buzzer, 0);
    lcd.setCursor(0, 0);
    lcd.print("                   ");
  }

  if (b44 == HIGH) {
    sendSMS("Line 1+gnd Fault", gps.location.lat(), gps.location.lng());
    analogWrite(o4, 1023);
    analogWrite(buzzer, 1023);    
    lcd.setCursor(0, 0);
    lcd.print("Line 1+gnd Fault");
    delay(5000);
  } else {
    analogWrite(o4, 0);
    analogWrite(buzzer, 0);    
    lcd.setCursor(0, 0);
    lcd.print("                     ");    
  }

  if (b55 == HIGH) {
    sendSMS("Line 2+gnd Fault", gps.location.lat(), gps.location.lng());
    analogWrite(o5, 1023);
    analogWrite(buzzer, 1023);        
    lcd.setCursor(0, 0);
    lcd.print("Line 2+gnd Fault");
    delay(5000);
  } else {
    analogWrite(o5, 0);
    analogWrite(buzzer, 0);        
    lcd.setCursor(0, 0);
    lcd.print("                      ");
  }
}


void sendSMS(String message, float latitude, float longitude) {
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);
  gsmSerial.print("AT+CMGS=\"+01774490501\""); // Replace with the recipient's phone number
  gsmSerial.write(0x0D); // Enter
  delay(100);
  gsmSerial.print(message + " - Google Maps Link: ");
  gsmSerial.print("http://maps.google.com/maps?q=");
  gsmSerial.print(latitude, 6);
  gsmSerial.print(",");
  gsmSerial.print(longitude, 6);
  gsmSerial.write(0x1A); // Ctrl+Z (End of SMS)
  delay(100);
}
