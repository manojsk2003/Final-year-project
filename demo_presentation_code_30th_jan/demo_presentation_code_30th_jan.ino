#include <Servo.h>

#define in1 4
#define in2 7
#define in3 8
#define in4 12
#define enA 5 //pwm
#define enB 3 //pwm

int M1_Speed = 80; // speed of motor 1
int M2_Speed = 80; // speed of motor 2
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

  pinMode(A0, INPUT); // initialize Left sensor as an input
  pinMode(A1, INPUT); // initialize Right sensor as an input

  myServo.attach(11); // Attach the servo to pin 11
  myServo.write(90);   // Initialize the servo position to 0°

 // Serial.begin(9600);  // Start Serial Communication for debugging
  Serial.begin(9600); // Start Serial Communication for Bluetooth module (RX/TX connected to 0,1)
}

void loop() {
  int LEFT_SENSOR = digitalRead(A0);
  int RIGHT_SENSOR = digitalRead(A1);

  if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0) {
    forward(); // FORWARD
  } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1) {
    right(); // Move Right
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0) {
    left(); // Move Left
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1) {
    Stop();  // STOP
    delay(5000); //wait
    sendBluetoothMessage(); // send message to bluetooth connected device 
   // Serial.print("stopped, checking moisture");
    servofunction(); // Call the servo function
    //Serial.print("data sent, moving forward");
    delay(5000); //wait
    forward(); // Move forward after the servo operation
  }
}

void servofunction() {
  myServo.write(0); // Rotate servo to 180°
  delay(3000);        // Wait for 3 seconds
  myServo.write(90);   // Rotate servo back to 0°
  delay(1000);        // Brief delay to ensure the servo completes movement
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
  sendBluetoothMessage(); // Send message when stopping
}

void sendBluetoothMessage() {
  int moisture = random(10, 100);  // Generate a random moisture percentage (10% to 100%)
  int fertilizer = random(5, 50);  // Generate a random fertilizer content in mg/kg (5 to 50)

  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.print("%, Fertilizer: ");
  Serial.print(fertilizer);
  Serial.println(" mg/kg");

  if (moisture < 30) {
    Serial.println("irrigate");  // Send irrigation alert if moisture is below 30%
  }

  if (fertilizer < 15) {
    Serial.println("Add Fertilizer");  // Send fertilizer alert if content is below 15 mg/kg
  }
}
