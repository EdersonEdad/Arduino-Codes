int tpin = 5;
int buttonpin = 9;
int value;



void setup() {
  // put your setup code here, to run once:

  pinMode(tpin, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = digitalRead(buttonpin);
  Serial.println(buttonpin);
  delay(400);

  value = digitalRead(buttonpin);

  if (value == LOW)
  {
    digitalWrite (tpin,LOW);
  }
  else {
    digitalWrite(tpin,HIGH);
  }
}
