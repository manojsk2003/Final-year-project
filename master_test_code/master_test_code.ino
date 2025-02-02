#include <Servo.h>

#define in1 4
#define in2 7
#define in3 8
#define in4 12
#define enA 5 // PWM
#define enB 3 // PWM
#define MOISTURE_PIN A2  // Moisture sensor analog pin

int M1_Speed = 80; 
int M2_Speed = 80; 
int LeftRotationSpeed = 130;  
int RightRotationSpeed = 130; 

Servo myServo; 

int stopCounter = 1; // Start counter from 1

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(A0, INPUT); // Left sensor
  pinMode(A1, INPUT); // Right sensor
  pinMode(MOISTURE_PIN, INPUT); // Moisture sensor

  myServo.attach(11); 
  myServo.write(90);  

  Serial.begin(9600); // Start Serial Communication
}

void loop() {
  int LEFT_SENSOR = digitalRead(A0);
  int RIGHT_SENSOR = digitalRead(A1);

  if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0) {
    forward(); 
  } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1) {
    right(); 
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0) {
    left(); 
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1) {
    Stop();  
    delay(5000); 
    servofunction(); 
    stopCounter++;  // Increment stop counter
    if (stopCounter > 3) stopCounter = 1; // Reset counter after stop 3
    delay(5000); 
    forward(); 
  }
}

void servofunction() {
  myServo.write(0);  
  delay(3000);       

  sendMoistureData(); 

  myServo.write(90);  
  delay(1000);        
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void sendMoistureData() {
  int moistureValue = analogRead(MOISTURE_PIN);  
  int moisturePercent = map(moistureValue, 1023, 0, 0, 100);  

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  if (moisturePercent < 5) {  
    Serial.print("irrigate");
    Serial.println(stopCounter);  // Send "irrigate1", "irrigate2", or "irrigate3"
  }
}
