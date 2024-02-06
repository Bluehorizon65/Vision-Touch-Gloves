
#include <DHT.h>

int const trigPin = 10;        // Defines the data pins of the ultrasonic sensor -used for triggering  the ultrasonic sound pulses
int const echoPin = 9;         // Defines the echo pins of the ultrasonic sensor -used for receving the ultrasonic waves after relefecting from a object
int const buzzPin = 2;         // Defines the buzzer pin -used for producing the buzzer sound 
int const vibrationPin = 3;    // Defines the pin for the vibration motor module -used for the vibration module to activate the vibration module 

// Define the type of DHT sensor (DHT11)
DHT dht(A0, DHT11); //this analog pin is used to measure the value for the temperature sensor

void setup() {
  pinMode(trigPin, OUTPUT);      // Sets trig pin to have output pulses
  pinMode(echoPin, INPUT);       // Sets echo pin to be input and get the pulse width
  pinMode(buzzPin, OUTPUT);      // Sets buzz pin as output to control the sound
  pinMode(vibrationPin, OUTPUT); // Sets the vibration motor pin as output
  
  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  int duration, distance;        // Duration will be the input pulse width, and distance will be the distance to the obstacle in centimeters
  float temperatureC = dht.readTemperature(); // Read temperature from DHT sensor

  digitalWrite(trigPin, HIGH);  // Output pulse with 1ms width on trigPin
  delay(1);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);   // Measure the pulse input in the echo pin
  distance = (duration / 2) / 29.1;    // Distance is half the duration divided by 29.1 (from datasheet)

  // If the distance is less than 0.5 meters and more than 0 (0 or less means over the range)
  if (distance <= 50 && distance >= 0) {
    // Trigger the Buzzer
    digitalWrite(buzzPin, HIGH);

    // Check temperature and activate vibration motor if above 40 degrees Celsius
    if (temperatureC > 40) {
      digitalWrite(vibrationPin, HIGH); // Activate the vibration motor
    } else {
      digitalWrite(vibrationPin, LOW);  // Turn off the vibration motor
    }
  } else {
    // if the the distance is not less than 0.5 meters 
    // No Sound and turn off the vibration motor
    digitalWrite(buzzPin, LOW); // the buzz pin is set to low 
    digitalWrite(vibrationPin, LOW); // the vibration motor pin is set to low
  }

  // Waits 50 milliseconds
  delay(50);
}

