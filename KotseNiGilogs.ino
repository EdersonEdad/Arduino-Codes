#include <HCSR04.h>
#include <Servo.h>

byte triggerPin = 11;
byte echoPin = 12;

Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

int pos = 0;  

void setup() {
  myservo.attach(13);
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
  // put your setup code here, to run once:

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);


}

void loop() {

  double* distances = HCSR04.measureDistanceCm();
  
  Serial.print("1: ");
  Serial.print(distances[0]);
  Serial.println(" cm");
  Serial.println("---");
  delay(50);
  if(distances[0] <= 5.0){

    pos = 90;
    myservo.write(pos);
    delay(3000);

  }else{
    myservo.write(0);
    delay(50);
  }



  // put your main code here, to run repeatedly:

}
