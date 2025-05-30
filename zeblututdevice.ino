#include <SoftwareSerial.h>
int rx=10, tx=11;

SoftwareSerial mySerial(rx,tx);
String val;
char data;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
while(mySerial.available()){
  data = mySerial.read();
  val+=data;

   
}
if(val == "on")
    {
      digitalWrite(7, HIGH);
    }
    if(val == "off")
    {
      digitalWrite(7, LOW);
    }
    

Serial.println(val);
delay(1000);
val="";
}
