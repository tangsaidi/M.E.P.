#include <LiquidCrystal.h>

LiquidCrystal lcd1(7,8,9,10,11,12);
LiquidCrystal lcd2(7,2,9,10,11,12);

String text;
int recomTime;

int i = 0;

//int ledPin = 1;
//int buttonpin = 0;
//byte leds = 0;
int tempPin = 0;
void setup() {
  Serial.begin(9600);
  lcd1.begin(16,2);
  lcd2.begin(16,2);
//  pinMode(ledPin, OUTPUT);
//  pinMode(buttonpin, INPUT_PULLUP);
}

void loop() {
// 
    lcd1.setCursor(0,0);
    lcd2.setCursor(0,0);
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
      
      
      int tempReading = analogRead(tempPin);
      double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
      tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
      float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
      float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
      lcd2.print("Temp         C  ");
      lcd2.setCursor(6, 0);
      lcd2.print(tempC);
      delay(500);

      
  if(Serial.available() > 1){

      lcd1.clear();
      
      text = Serial.readStringUntil(';');
      recomTime = Serial.parseInt();
      
      lcd1.print("Product: ");
      lcd1.print(text);
      
      lcd1.setCursor(0,1);
      
      lcd1.print("Time: ");
      lcd1.print(recomTime);
      lcd1.print(" sec");
      
      i = 1;
      text = "";
      recomTime = 0;
  
    }else if(i == 0){
      lcd1.print("Put in your food");
    }

    
}
