#include <LiquidCrystal.h>
#include "SR04.h"
#define trigPin1 3
#define echoPin1 4
#define trigPin2 5
#define echoPin2 6

//Hand gesture
int dist11;
int dist12;
int dist21;
int dist22;
int value  = 0;
int value2 = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;
//Timers
unsigned long preTimer;
unsigned long curTimer;
unsigned long Interval = 500;
unsigned long preTimer2=0;
unsigned long curTimer2;
unsigned long Interval2 = 3000;
unsigned long preTimer3;
unsigned long curTimer3;
unsigned long Interval3 = 1000;

//LCD screens
LiquidCrystal lcd1(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd2(7, 13, 9, 10, 11, 12);

//Display Food Types
String text;
int prepTime = 0;
int microTime;

//Flags
int flag =0;
int flag2 = 0; //open hand gesture
int flag3 = 0; //put in food
int flag4 = 0;//start cooking
int flag5 = 0;
//Button variable
//int ledPin = 1;
//int buttonpin = 0;
//byte leds = 0;
int i = 0;

//Temp variable
float tempC;
double tempK;
int tempReading;
float tempF;
int tempPin = 0;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  delay(500);
  //used for button
  //  pinMode(ledPin, OUTPUT);
  //  pinMode(buttonpin, INPUT_PULLUP);
}

int time = 0;
int temp (double input, double temp1) {
  int change = input - (int)((temp1 - 25) / 5) * 10;
  //Serial.println(change);
  if (change >= 1000) change = 999;
  else if (change < 0) change = 0;
  return change;
}

int rightTleft(int time) {
  Serial.println("FROM Right to Left");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  return time - 5;
}
int leftTright(int time) {
  Serial.println("FROM Left to Right");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 =0;
  return time + 5;
}
void push(){
  Serial.println("PUSH");
    delay(200);
    value=0;
    count1=0;
    count2=0;
    count3=0;
    flag4=1;
    flag2=0;
}
void loop() {
  lcd1.setCursor(0, 0);
  lcd2.setCursor(0, 0);
  curTimer = millis();
  curTimer3 = millis();
  //Serial.println(curTimer);
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

  //Measure the temperature of surrounding with thermosenser
  if ((curTimer - preTimer) > Interval) {
    tempReading = analogRead(tempPin);
    tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
    tempC = tempK - 273.15;            // Convert Kelvin to Celcius
    tempF = (tempC * 9.0) / 5.0 + 32.0; // Convert Celcius to Fahrenheit
    lcd2.print("Temp         C  ");
    lcd2.setCursor(6, 0);
    lcd2.print(tempC);
    //delay(1000);
    preTimer = millis();
  }

  //Take serial input from raspberry pi and print it on the LED display
  if (Serial.available() > 1) {
    lcd1.clear();
    text = Serial.readStringUntil(';');
    microTime = Serial.parseInt();
    lcd1.print("Type: ");
    lcd1.print(text);
    lcd1.setCursor(0, 1);
    lcd1.print("Time: ");
    lcd1.print(microTime);
    lcd1.print("  sec");
    lcd2.setCursor(0, 1);
    lcd2.print("Swipe to adjust");
    flag = 1;
    flag2 = 1;
    flag3 = 1;
    text = "";
    prepTime = microTime;
    microTime = 0;
  } else if (flag3 == 0) {
    lcd1.print("Put in your food");
  }
    
  //Gesture Recognition with supersonic sensor. Recognizes swipe left and swipe,
  //adjust time in reponse to your gestures.
  if (flag == 1) {
    if (flag2 == 1) {
      long duration1, distance1;
      digitalWrite(trigPin1, LOW);
      digitalWrite(trigPin1, HIGH);
      digitalWrite(trigPin1, LOW);
      duration1 = pulseIn(echoPin1, HIGH);
      distance1 = (duration1 / 2) / 29.1;
      long duration2, distance2;
      digitalWrite(trigPin2, LOW);
      digitalWrite(trigPin2, HIGH);
      digitalWrite(trigPin2, LOW);
      duration2 = pulseIn(echoPin2, HIGH);
      distance2 = (duration2 / 2) / 29.1;
      /*Serial.print("Pre: " );
        Serial.print(distance1);
        Serial.print(" : " );
        Serial.println(distance2);*/
      if ((distance1 < 30) && distance1 > 15 && distance2 < 30 && distance2 > 15 && value2 == 0) {
        count3++;
        //value2=0;
        if (count3 > 10) {
          push();
          value2 = 1;
          count3 = 0;
          preTimer2 = millis();
        }
      }
      else if ((distance1 < 20) && (value == 2)) {
        prepTime=rightTleft(prepTime);
        value2 = 0;
      }
      else if ((distance2 < 20) && (value == 1)) {
        prepTime=leftTright(prepTime);
        value2 = 0;
      }
      else if ((distance1 < 20) && (value == 0)) {
        value = 1;
      }
      else if ((distance2 < 20) && (value == 0)) {
        value = 2;
      }
      if (value == 1) {
        count1++;
        if (count1 > 10) {
          count1 = 0;
          value = 0;
        }
      }
      if (value == 2) {
        count2++;
        if (count2 > 20) {
          count2 = 0;
          value = 0;
        }
      }
      if (value2 == 1) {
        curTimer2 = millis();
        if ((curTimer2 - preTimer2) > Interval2) {
          //Serial.print(value2);
          value2 = 0;
        }
      }
    }
    if (flag4 == 0) {
      prepTime = temp(prepTime, tempC);
      lcd1.setCursor(6, 1);
      lcd1.print(prepTime);
      lcd1.setCursor(10, 1);
      lcd1.print("sec");
    }
    else if ((curTimer3 - preTimer3) > Interval3) {
      lcd2.setCursor(0, 1);
      lcd2.print("Start Cooking!  ");
      prepTime--;
      if(prepTime<10){
        lcd1.setCursor(7, 1);
      }
      else{
        lcd1.setCursor(6, 1);
      }
      lcd1.print(prepTime);
      lcd1.setCursor(10, 1);
      lcd1.print("sec");
      preTimer3 = millis();
    }
    if (prepTime <= 0) {
      flag=0;
      flag3=0;
      flag5=1;  // restart to begining
     }
  }
  if(flag5==1){
    lcd2.setCursor(0, 1);
    lcd2.print("Food Finished. ");
  }
}

