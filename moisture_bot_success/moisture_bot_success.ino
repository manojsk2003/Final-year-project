#include <Servo.h>

#define in1 4
#define in2 7
#define in3 8
#define in4 12
#define enA 5 // PWM
#define enB 3 // PWM
#define MOISTURE_PIN A2  // Moisture sensor analog pin

int M1_Speed = 80; // Speed of motor 1
int M2_Speed = 80; // Speed of motor 2
int LeftRotationSpeed = 120;  // Left Rotation Speed
int RightRotationSpeed = 120; // Right Rotation Speed

Servo myServo; // Create a Servo object

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

  myServo.attach(11); // Attach the servo to pin 11
  myServo.write(90);  // Initialize the servo position to 90°

  Serial.begin(9600); // Start Serial Communication for Bluetooth module
}

void loop() {
  int LEFT_SENSOR = digitalRead(A0);
  int RIGHT_SENSOR = digitalRead(A1);

  if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0) {
    forward(); // Move forward
  } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1) {
    right(); // Turn right
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0) {
    left(); // Turn left
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1) {
    Stop();  // Stop movement
    delay(5000); // Wait
    servofunction(); // Move servo and take moisture reading
    delay(5000); // Wait before moving forward
    forward(); // Move forward after operation
  }
}

void servofunction() {
  myServo.write(0);  // Rotate servo to 0°
  delay(3000);       // Wait for 3 seconds

  sendMoistureData(); // Read and send moisture data

  myServo.write(90);  // Rotate servo back to 90°
  delay(1000);        // Brief delay to complete movement
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
  int moistureValue = analogRead(MOISTURE_PIN);  // Read raw sensor value (0-1023)
  int moisturePercent = map(moistureValue, 1023, 0, 0, 100);  // Convert to %

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  if (moisturePercent < 5) {  
    Serial.println("irrigate");  // Send irrigation alert if moisture is below 5%
  }
}
