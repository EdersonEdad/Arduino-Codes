#include <Keypad.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); 

const byte ROWS = 4;
const byte COLS = 4;
char pass[] = "ABCD1234";

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char enteredPass[8]; 
byte passIndex = 0;
int cursor = 0;

void setup() {
  Serial.begin(9600);  
  lcd.begin();   
  lcd.backlight();
  lcd.print("Enter passcode:");
  Serial.println("System Initialized. Enter passcode.");
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {

    if (customKey == '#') {
      enteredPass[passIndex] = '\0';
      Serial.print("Entered passcode: ");
      Serial.println(enteredPass);    
      cursor = 0;   

      if (strcmp(enteredPass, pass) == 0) {
        lcd.clear();
        lcd.print("Correct Password");
        Serial.println("Correct Password");
      } else {
        lcd.clear();
        lcd.print("Incorrect Pass");
        Serial.println("Incorrect Pass");
      }

      delay(2000); 
      lcd.clear();
      lcd.print("Enter passcode:"); 
      passIndex = 0;  
      memset(enteredPass, 0, sizeof(enteredPass));  
    }

    else if (customKey == '*') {
      passIndex = 0;
      memset(enteredPass, 0, sizeof(enteredPass));
      lcd.clear();
      lcd.print("Enter passcode:");
      Serial.println("Passcode reset.");
      cursor = 0;
    }
    else {
      if (passIndex < 8) {
        
        enteredPass[passIndex] = customKey;
        passIndex++;
        Serial.print("Key pressed: ");
        Serial.println(customKey);
        lcd.setCursor(cursor, 1);
        lcd.print(customKey);
        cursor++;
      }
    }
  }
}