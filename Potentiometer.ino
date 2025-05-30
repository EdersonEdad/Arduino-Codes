// Define the pins for the RGB LED
int redPin = 2;
int greenPin = 3;
int bluePin = 4;

// Define the analog input pins for the potentiometers
int potRed = A0;
int potGreen = A1;
int potBlue = A2;

void setup() {
  // Set LED pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the potentiometer values (0 to 1023)
  int redVal = analogRead(potRed);
  int greenVal = analogRead(potGreen);
  int blueVal = analogRead(potBlue);

  // Map the potentiometer values to PWM values (0 to 255)
  redVal = map(redVal, 0, 1023, 0, 255);
  greenVal = map(greenVal, 0, 1023, 0, 255);
  blueVal = map(blueVal, 0, 1023, 0, 255);

  // Write the PWM values to the RGB LED
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);

  int sensorValue1 = analogRead(potRed);
  int sensorValue2 = analogRead(potGreen);
  int sensorValue3 = analogRead(potBlue);

  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  Serial.println(sensorValue3);
  
  delay(1);
}

