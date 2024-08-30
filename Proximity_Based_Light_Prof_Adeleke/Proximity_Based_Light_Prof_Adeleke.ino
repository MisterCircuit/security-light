// Define the pin connections
#define PIR_SENSOR_PIN 2
#define RELAY 3

// Variables
bool motionDetected = false;
unsigned long detectionTime = 0;
const unsigned long debounceDelay = 500; // Time to wait for confirming detection (in milliseconds)

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW); // Ensure the LED is off initially
  Serial.begin(9600);
  delay(30000);
  digitalWrite(RELAY, LOW);
}

void loop() {
  int pirState = digitalRead(PIR_SENSOR_PIN);
  
  if (pirState == HIGH) {
    if (!motionDetected) {
      motionDetected = true;
      detectionTime = millis();
    }
  } else {
    motionDetected = false;
  }
  
  if (motionDetected) {
    if (millis() - detectionTime > debounceDelay) {
      digitalWrite(RELAY, HIGH);
      Serial.println("Motion detected, LED turned on");
    }
  } else {
    digitalWrite(RELAY, LOW);
    Serial.println("No motion, LED turned off");
  }
}
