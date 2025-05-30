int pins[] = {2,3,4,5,6,7,8,9,10,11};
int tpins = 10;
int tDelay = 50;

void setup() {
  
  for (int i = 0; i < tpins; i++) {
    pinMode(pins[i], OUTPUT);
  }

}

void loop() {
  
  for(int i=0; i<=11; i++){
  digitalWrite(i, HIGH);
  delay(tDelay);
  }
  for(int i=0; i<=11; i++){
    digitalWrite(i, LOW);
    delay(tDelay);
  }

  for(int i = 11; i>=0; i--){
    digitalWrite(i, HIGH);
    delay(tDelay);
  }
  for(int i = 11; i>=0; i--){
    digitalWrite(i, LOW);
    delay(tDelay);
  }

}