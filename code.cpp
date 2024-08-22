// This code will check distance and indicate if an obstacle/person is away for 5 seconds from 
// a fixed distance ( it is set at 70cm here). A lock keyboard press is issued via bluetooth keyboard
// ESP 32, Ultrasonic sensor HC SR04

#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 KB"); // this is the name of the keyboard displayed on the laptop

// Define pins

const int trigPin = 14;
const int echoPin = 27;

// Define other variables
long duration, distance;
int tCnt;
bool flagBlueMsg = false;

void setup() {
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // initialise trigger count. this counter counts how many seconds the obstacle / person was away
  tCnt=0;
  // Initialize serial communication for debugging (optional)
    Serial.begin(9600);
    Serial.print("Starting BLE work!");
    bleKeyboard.begin();
   
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  //digitalWrite(led3, LOW);
  delayMicroseconds(2);

  // Set trigPin on for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read pulseIn on echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;
  
  // Check if something is detected
  if (distance <= 70) { // Adjust distance threshold as needed in cm
   
     flagBlueMsg = false; // flag to ensure bluetooth message is sent only after the count is more than 5    
    tCnt=0;
  } else {
    tCnt++;
       
    if (tCnt > 5) //this is the duration for which an object can be away from the set distance threshold. Here it is set at 5 x delay(1000) 5 seconds
    {
    
    if(!flagBlueMsg && bleKeyboard.isConnected()) //check flag and bluetooth connection
      {
        flagBlueMsg = true;
        Serial.println("Sending Bluetooth message");
        //bleKeyboard.println("Hi bluetooth world ");
        bleKeyboard.press(KEY_LEFT_GUI); //press windows key
        bleKeyboard.write('l'); // press l button
        bleKeyboard.releaseAll(); // release all. this is mandatory
        delay(2000); 
      }
    }
  }

  // Print distance and LED states for debugging in the serial monitor (optional)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, LED1: ");
  Serial.print(", trigCount: ");
  Serial.print(tCnt);
  delay(1000); // Adjust delay as needed. This will determine the distance reading sampling. it is set to sample every minute
}
