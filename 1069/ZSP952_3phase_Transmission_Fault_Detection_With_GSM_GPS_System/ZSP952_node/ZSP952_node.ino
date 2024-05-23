int in1=D1;
int in2=D2;
int in3=D5;
int in4=D6;
int in5=D7;

#define BLYNK_TEMPLATE_ID "TMPL6BEfeOqR9"
#define BLYNK_TEMPLATE_NAME "3phase fault detection"
#define BLYNK_AUTH_TOKEN "VE2LX8NV-yl2zzZhZGdJ5VTtktSYY-RM"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "abcde";
char pass[] = "123456789";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1


void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(in1,INPUT);
  pinMode(in2,INPUT);
  pinMode(in3,INPUT);
  pinMode(in4,INPUT);
  pinMode(in5,INPUT);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();

int inn1=digitalRead(in1);
int inn2=digitalRead(in2);
int inn3=digitalRead(in3);
int inn4=digitalRead(in4);
int inn5=digitalRead(in5);

Serial.print(inn1);
Serial.print(inn2);
Serial.print(inn3);
Serial.print(inn4);
Serial.println(inn5);

if(inn1==1){
 Blynk.virtualWrite(V0, HIGH); 
  }
if(inn1==0){
 Blynk.virtualWrite(V0, LOW); 
  }  

if(inn2==1){
 Blynk.virtualWrite(V1, HIGH); 
  }
if(inn2==0){
 Blynk.virtualWrite(V1, LOW); 
  } 
   
  if(inn3==1){
 Blynk.virtualWrite(V2, HIGH); 
  }
if(inn3==0){
 Blynk.virtualWrite(V2, LOW); 
  } 
   
if(inn4==1){
 Blynk.virtualWrite(V3, HIGH); 
  }
if(inn4==0){
 Blynk.virtualWrite(V3, LOW); 
  }
    
if(inn5==1){
 Blynk.virtualWrite(V4, HIGH); 
  }
if(inn5==0){
 Blynk.virtualWrite(V4, LOW); 
  }  
  
}
