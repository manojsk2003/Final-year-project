#define LED1 3  // LED for Row 1 (PWM pin 3)
#define LED2 5  // LED for Row 2 (PWM pin 5)
#define LED3 6  // LED for Row 3 (PWM pin 6)

int counter = 1;  // Counter to track LED sequence

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readString();  // Read received data
    command.trim();  // Remove any whitespace or newlines

    if (command.equals("irrigate")) {
      // Turn off all LEDs before turning on the next one
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);

      // Turn on the respective LED based on counter value
      if (counter == 1) {
        analogWrite(LED1, 255);  // Full brightness
        delay(3000);
        analogWrite(LED1, 0);
      } 
      else if (counter == 2) {
        analogWrite(LED2, 255);
        delay(3000);
        analogWrite(LED2, 0);
      } 
      else if (counter == 3) {
        analogWrite(LED3, 255);
        delay(3000);
        analogWrite(LED3, 0);
      }

      counter++;  // Increment counter

      if (counter > 3) {
        counter = 1;  // Reset counter after 3rd LED
      }
    
    }
  }
}
