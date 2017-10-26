#include <LiquidCrystal.h>

LiquidCrystal lcd1(7,8,9,10,11,12);
LiquidCrystal lcd2(7,2,9,10,11,12);


void setup() {
  // put your setup code here, to run once:
  lcd1.begin(16,2);
  
  lcd2.begin(16,2);
  Serial.begin(9600);
 // lcd1.write("Andy");
}

void loop() {
      if (Serial.available()) {
    delay(100);  //wait some time for the data to fully be read
    lcd1.clear();
    while (Serial.available() > 0) {
      char c = Serial.read();
      if(c == '\n') break;
      lcd1.write(c);
      }
      }
    }
