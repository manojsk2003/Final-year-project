#define LED1 3  
#define LED2 5  
#define LED3 6  

int counter = 1;  // Start counter from 1

void setup() {
  Serial.begin(9600);  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {                              //snippet 1 starts here
  if (Serial.available()) {  
    String receivedData = Serial.readString();  
    receivedData.trim();  
    Serial.println(receivedData);          
    // Check if the message starts with "irrigate" and extract the stop counter value
    if (receivedData.startsWith("irrigate")) {
      // Extract the number after "irrigate"
      int stopNumber = receivedData.substring(8).toInt();   //snippet 1 ends here
      Serial.println(stopNumber);
      // Based on the stop number, light up the appropriate LED
      if (stopNumber == 1) {                           // snippet 2 starts here
        digitalWrite(LED1, HIGH);
        delay(8000);
        digitalWrite(LED1, LOW);
      } 
      else if (stopNumber == 2) {  
        digitalWrite(LED2, HIGH);
        delay(8000);
        digitalWrite(LED2, LOW);
      } 
      else if (stopNumber == 3) {  
        digitalWrite(LED3, HIGH);
        delay(8000);
        digitalWrite(LED3, LOW);                     //snippet 2 ends here
      }
    }
  }
}
