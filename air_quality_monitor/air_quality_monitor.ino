
/* 
* Air Quality Reader
* Reads the analog output of an MQ-135 sensor and indicates range by LEDs
*/


// Constants
const int baudRate = 9600;
const int RED = 13;
const int YELLOW = 12;
const int GREEN = 11;
const int ANALOG_IN = A0;
const int SLEEP = 1000;
const boolean isDebug = false;

void setup() {
  Serial.begin(baudRate); 
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT); 
  pinMode(ANALOG_IN, INPUT);
}

void loop() {
    int sensorValue = readValue();
    processValue(sensorValue);
    delay(SLEEP); 
}

/**
* Read from the input and log debug if enabled.
* @returns int the value of the sensor
*/
int readValue() {
  int sensorValue = analogRead(ANALOG_IN);
  if (isDebug) {
    char buffer[15];
    sprintf(buffer, "DEBUG: %d", sensorValue);
    Serial.println(buffer);
  }
  return sensorValue; 
}

/**
* process the value by writing to the LED outputs
* @arg sensorValue - the integer value read from the sensor
*/
void processValue(int sensorValue) {
  
  if (sensorValue < 400) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
  } else if (sensorValue < 750) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, LOW);
  } else if (sensorValue < 1200) {
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, HIGH);
  } else {
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);
  }  
}

