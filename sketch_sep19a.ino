int pins[] = {2,3,4,5,6,7,8,9,10,11};
int tpins = 10;
int tDelay = 70;

void setup() {
  
  for (int i = 0; i < tpins; i++) {
    pinMode(pins[i], OUTPUT);
  }

}

void loop() {
  
  for (int j = 0; j < tpins; j++) { 
    for (int i = j; i < tpins; i++) {
      digitalWrite(pins[i], HIGH); 
      delay(tDelay); 

      digitalWrite(pins[i], LOW);
      delay(tDelay);
    }
    digitalWrite(pins[j],HIGH);-
  }

  for (int i = 0; i < tpins; i++) {
    digitalWrite(pins[i], LOW); 
  }

}
