int redled1 = 5;      
int yellowled1 = 6;   
int greenled1 = 7;    


int redled2 = 8;    
int yellowled2 = 9;  
int greenled2 = 10;   

unsigned long greendelay = 6000;
unsigned long yellowdelay = 3000;

int button_press1 = 2;   
int button_press2 = 13;   

int Button_State1 = HIGH;  
int Button_State2 = HIGH;  

unsigned long lastDebounceTime1 = 0;  
unsigned long lastDebounceTime2 = 0; 
unsigned long debounceDelay = 50;    

unsigned long previousMillis = 0;
unsigned long interval = 0;  

int state = 0;   

void setup() {
  pinMode(redled1, OUTPUT);
  pinMode(yellowled1, OUTPUT);
  pinMode(greenled1, OUTPUT);
  pinMode(redled2, OUTPUT);
  pinMode(yellowled2, OUTPUT);
  pinMode(greenled2, OUTPUT);

  pinMode(button_press1, INPUT_PULLUP);
  pinMode(button_press2, INPUT_PULLUP);

  trafficLightState(0);
}

void loop() {
  unsigned long currentMillis = millis();

  int reading1 = digitalRead(button_press1);
  int reading2 = digitalRead(button_press2);

  if (reading1 != Button_State1) {
    lastDebounceTime1 = currentMillis;
  }
  if ((currentMillis - lastDebounceTime1) > debounceDelay) {
    if (reading1 == LOW) {
      handleButtonPress(1);  
    }
  }
  Button_State1 = reading1;

  if (reading2 != Button_State2) {
    lastDebounceTime2 = currentMillis;
  }
  if ((currentMillis - lastDebounceTime2) > debounceDelay) {
    if (reading2 == LOW) {
      handleButtonPress(2);  
    }
  }
  Button_State2 = reading2;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    nextState();  
  }
}

void trafficLightState(int s) {
  switch (s) {
    case 0:  
      digitalWrite(greenled1, HIGH);
      digitalWrite(redled1, LOW);
      digitalWrite(yellowled1, LOW);
      digitalWrite(greenled2, LOW);
      digitalWrite(yellowled2, LOW);
      digitalWrite(redled2, HIGH);
      interval = greendelay;
      break;
    case 1:  
      digitalWrite(greenled1, LOW);
      digitalWrite(yellowled1, HIGH);
      digitalWrite(redled1, LOW);
      digitalWrite(greenled2, LOW);
      digitalWrite(yellowled2, LOW);
      digitalWrite(redled2, HIGH);
      interval = yellowdelay;
      break;
    case 2: 
      digitalWrite(greenled1, LOW);
      digitalWrite(yellowled1, LOW);
      digitalWrite(redled1, HIGH);
      digitalWrite(greenled2, HIGH);
      digitalWrite(yellowled2, LOW);
      digitalWrite(redled2, LOW);
      interval = greendelay;
      break;
    case 3: 
      digitalWrite(greenled1, LOW);
      digitalWrite(yellowled1, LOW);
      digitalWrite(redled1, HIGH);
      digitalWrite(greenled2, LOW);
      digitalWrite(yellowled2, HIGH);
      digitalWrite(redled2, LOW);
      interval = yellowdelay;
      break;
  }
}
	void nextState(){

  state = (state + 1) % 4;  
  trafficLightState(state);
}
void handleButtonPress(int button) {
  if (button == 1) {
    if (state == 2){
      state = 3;
      trafficLightState(state); 
    } 

  } else if (button == 2) {
    if (state == 0){
      state = 1;
      trafficLightState(state); 
    }
  
    }
}
