/*************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App dashboard setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6G1H1wafP"
#define BLYNK_TEMPLATE_NAME "node mcu"
#define BLYNK_AUTH_TOKEN "qred8KerFdSQJpUn-UTDyy5t_FKZABwU"

/* Comment this out to disable prints and save space */


#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


char ssid[] = "abcde";
char pass[] = "123456789";

BlynkTimer timer;
bool Relay = 0;

DHT dht(D3, DHT22);
#define sensor A0
#define waterPump D5

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  lcd.begin();
  lcd.backlight();
  dht.begin();

  Blynk.begin( ssid, pass, "blynk.cloud", 80);

  lcd.setCursor(1, 0);
  lcd.print("System Loading");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();

  timer.setInterval(100L, DHT22sensor);
  timer.setInterval(100L, soilMoistureSensor);
}

//Get the button value
BLYNK_WRITE(V7) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);

  } else {
    digitalWrite(waterPump, HIGH);
  }
}

//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V8, value);
  lcd.setCursor(0, 0);
  lcd.print("Moisture :");
  lcd.print(value);
  lcd.print(" ");
}

void DHT22sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(t);

  lcd.setCursor(8, 1);
  lcd.print("H:");
  lcd.print(h);
}

void loop() {
  Blynk.run();  //Run the Blynk library
  timer.run();  //Run the Blynk timer
}
