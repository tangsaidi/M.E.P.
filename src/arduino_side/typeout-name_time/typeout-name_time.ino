#include <LiquidCrystal.h>

LiquidCrystal lcd1(7,8,9,10,11,12);

String text;
int recomTime;

int i = 0;

//int ledPin = 1;
//int buttonpin = 0;
//byte leds = 0;

void setup() {
  Serial.begin(9600);
  lcd1.begin(16,2);
//  pinMode(ledPin, OUTPUT);
//  pinMode(buttonpin, INPUT_PULLUP);
}

void loop() {
 
  lcd1.setCursor(0,0);
//  
//      //-------------------------
//      if (digitalRead(buttonpin) == LOW){
//        digitalWrite(ledPin, HIGH);
//      }
//      if (digitalRead(buttonpin) == HIGH){
//        digitalWrite(ledPin, LOW);
//        
//        i = 0;
//      }
//    // ----------------------------- 

    
  if(Serial.available() > 1){

      lcd1.clear();
      
      text = Serial.readStringUntil(';');
      recomTime = Serial.parseInt();
      
      lcd1.print("Product: ");
      lcd1.print(text);
      
      lcd1.setCursor(0,1);
      
      lcd1.print("Time: ");
      lcd1.print(recomTime);
      
      i = 1;
      text = "";
      recomTime = 0;
  
    }else if(i == 0){
      lcd1.print("Put in your food");
    }
}
