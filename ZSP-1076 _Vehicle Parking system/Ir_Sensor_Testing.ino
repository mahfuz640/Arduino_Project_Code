#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
#define SS_PIN 10
#define RST_PIN 9

//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
byte readCard[4];
String MasterTag = "3B3B9622";
String tagID = "";

//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int irSensorPin = 2; // Pin connected to the IR sensor output
const int irSensorPina = 3; // Pin connected to the IR sensor output2
const int irSensorPinb = 4; // Pin connected to the IR sensor output3

const int ledPinc= 5;     // Pin connected to the LED (optional)
const int ledPin = 6;     // Pin connected to the LED (optional) c

void setup() {
  pinMode(irSensorPin, INPUT); // Set the IR sensor pin as input
    pinMode(irSensorPina, INPUT); // Set the IR sensor pin as input
      pinMode(irSensorPinb, INPUT); // Set the IR sensor pin as input
      
  pinMode(ledPin, OUTPUT);     // Set the LED pin as output
  pinMode(ledPinc, OUTPUT);     // Set the LED pin as output c
    myservo.attach(7);  // attaches the servo on pin 9 to the servo object

  Serial.begin(9600);          // Initialize serial communication at 9600 bps

//  LCD
 // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Parking Already full");
  lcd.print("");


  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  Serial.begin(9600);
  SPI.begin();
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  mfrc522.PCD_Init();
  delay(4);
  //Show details of PCD - MFRC522 Card Reader
  mfrc522.PCD_DumpVersionToSerial();
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  Serial.println("--------------------------");
  Serial.println(" Access Control ");
  Serial.println("Scan Your Card>>");
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
}


void loop() {
  int sensorValue = digitalRead(irSensorPin); // Read the sensor value
   int sensorValuea = digitalRead(irSensorPina); // Read the sensor value
    int sensorValueb = digitalRead(irSensorPinb); // Read the sensor value
  Serial.print(sensorValue);
    Serial.println(sensorValuea);
      Serial.println(sensorValueb);
  
  if (sensorValue == HIGH && sensorValuea == HIGH && sensorValueb == HIGH) { // IR sensor detects an obstacle
    digitalWrite(ledPin, HIGH); // Turn on the LED
    digitalWrite(ledPinc, HIGH); // Turn on the LED
    myservo.write(90); 
    Serial.println("Obstacle detected"); // Print message to Serial Monitor

  } if(sensorValue == LOW && sensorValuea == HIGH && sensorValueb == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    digitalWrite(ledPinc, HIGH); // Turn on the LED
        myservo.write(0); 
        delay(5000);
        myservo.write(90); 

    Serial.println("No obstacle"); // Print message to Serial Monitor
  }if(sensorValue == HIGH && sensorValuea == LOW && sensorValueb == HIGH) {
    digitalWrite(ledPin, LOW); // Turn on the LED
    digitalWrite(ledPinc, HIGH); // Turn on the LED
    Serial.println("No obstacle"); // Print message to Serial Monitor
        myservo.write(0); 
        delay(5000);
        myservo.write(90); 

  }
  if(sensorValue == HIGH && sensorValuea == HIGH && sensorValueb == LOW) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    digitalWrite(ledPinc, LOW); // Turn on the LED
    myservo.write(0); 
        delay(5000);
        myservo.write(90); 
    Serial.println("No obstacle"); // Print message to Serial Monitor
  }if(sensorValue == LOW && sensorValuea == LOW && sensorValueb == LOW) {
    digitalWrite(ledPin, LOW); // Turn on the LED
    digitalWrite(ledPinc, LOW); // Turn on the LED
    myservo.write(0); 
        delay(5000);
        myservo.write(90); 
    Serial.println("No obstacle"); // Print message to Serial Monitor
  }
  
  delay(100); // Small delay to avoid spamming the Serial Monitor

 //----------------------------------------------------------------------
  //Wait until new tag is available
  while (getID()) {
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    if (tagID == MasterTag){
      Serial.println(" Access Granted!");
      Serial.println("--------------------------");
       //You can write any code here like, opening doors, 
       //switching ON a relay, lighting up an LED etc...
    }
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    else{
      Serial.println(" Access Denied!");
      Serial.println("--------------------------");
    }
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    delay(2000);
    Serial.println(" Access Control ");
    Serial.println("Scan Your Card>>");
  }
  //----------------------------------------------------------------------
  
}

boolean getID() 
{
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  // Getting ready for Reading PICCs
  //If a new PICC placed to RFID reader continue
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  //Since a PICC placed get Serial and continue
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return false;
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  tagID = "";
  // The MIFARE PICCs that we use have 4 byte UID
  for ( uint8_t i = 0; i < 4; i++) {
  //readCard[i] = mfrc522.uid.uidByte[i];
  // Adds the 4 bytes in a single String variable
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
}
