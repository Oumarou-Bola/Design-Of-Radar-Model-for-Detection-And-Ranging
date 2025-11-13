
// The program has been duly modified and adapted by Oumarou Moussa Bola in 2022
/*
 * This program is property of SME Dehradun. for any query related to this program, 
 * contact us at www.smedehradn.com
 * if your want any soluiton related for any IoT Customized Boards and Sensor, 
 * then contact to www.nuttyengineer.com 
 * Projet modifier et adapte Par Eng Moussa Bola Oumarou RADAR project
 */
// Replace/ Fill-in information from your Blynk Template here

#define BLYNK_TEMPLATE_ID "TMPLgJ9xJ4zg"
#define BLYNK_DEVICE_NAME "Mini Projet RADAR"

#define BLYNK_FIRMWARE_VERSION "1.0.1"
#define BLYNK_PRINT Serial
#include "BlynkEdgent.h" 
#include <Servo.h>
//what i add
static const int servoPin = 4;
const int trigPin = 5 ;
const int echoPin = 18 ;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
long duration;
float distance;//distance en cm
Servo servo1;


void RADAR()
{//le traitement du Radar
  
for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.print("La position en degre: ");
        Serial.println(posDegrees);
        //
        Blynk.virtualWrite(V0,posDegrees);
        delayMicroseconds(5);
        distance = calculateDistance();
        
    }

    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.print("La position en degre: ");
        Serial.println(posDegrees);
        //
        Blynk.virtualWrite(V0,posDegrees);
        delayMicroseconds(5);
        distance = calculateDistance();
        
    }
 
}



void setup()
{
//  Serial.begin(115200);
////  pinMode(34, INPUT);
//  pinMode(trigPin, OUTPUT); 
//  pinMode(echoPin, INPUT); 
 Serial.begin(115200);// Starts the serial communication
    servo1.attach(
        servoPin, 
        Servo::CHANNEL_NOT_ATTACHED,0,180
    );
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  BlynkEdgent.begin();
  delay(100); 
}


void loop() 
{
  BlynkEdgent.run();
  RADAR();
}


//-------------------here we define a function that calculate the distance

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 microseconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(5);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
distance= duration*SOUND_SPEED/2;

// Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distance);
 //
 Blynk.virtualWrite(V1,distance);
delayMicroseconds(5);
return distance;
}

