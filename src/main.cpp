#include <Arduino.h>

#define trigPin 9
#define echoPin 10

#include <SoftwareSerial.h> // for SIM800L

SoftwareSerial mySerial(10, 11); // RX, TX   // creating an instance of the SoftwareSerial class

void setup() {
  //==========================Ultrasonic==========================
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  
}

void loop() {
  //==========================Ultrasonic==========================
  long duration, distance;
  
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration / 58.2;  // Convert time to distance (in cm)
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10)
  {
    //==========================SIM800L comes here======================================
   Serial.begin(9600);
   mySerial.begin(9600);
   delay(1000);
   mySerial.println("AT+CMGF=1"); // Set SMS mode to text
   delay(1000);
   mySerial.println("AT+CMGS=\"+1234567890\""); // Replace with recipient's phone number
   delay(1000);
   mySerial.println("Hello from SIM800L!"); // Replace with your message
   delay(1000);
   mySerial.write(26); // Send CTRL+Z character to end message 
  }
  
  delay(500);
}

