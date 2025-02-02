#define MOISTURE_PIN A2  // Moisture sensor analog pin

void setup() {
  Serial.begin(9600);  // Initialize Bluetooth communication (TX/RX on pins 0 and 1)
  pinMode(MOISTURE_PIN, INPUT);
}

void loop() {
  int moistureValue = analogRead(MOISTURE_PIN);  // Read raw sensor value (0-1023)

  // Convert to percentage (assuming 0 = dry, 1023 = fully wet)
  int moisturePercent = map(moistureValue, 1023, 0, 0, 100);

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  delay(2000);  // Send data every 2 seconds
}
