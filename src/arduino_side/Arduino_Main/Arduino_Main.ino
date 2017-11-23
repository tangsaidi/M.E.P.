#include <LiquidCrystal.h>
#include <stdlib.h>
#include <string.h>
//--------------------------------------Variable Definition---------------------------------------------------------//
#define trigPin1 3
#define echoPin1 4
#define trigPin2 5
#define echoPin2 6

//-------------------Hand gesture//
long duration1, distance1;
long duration2, distance2;
int value  = 0;
int value2 = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;

//-------------------Timers//
unsigned long preTimer;
unsigned long curTimer;
unsigned long Interval = 2000;
unsigned long preTimer2 = 0;
unsigned long curTimer2 = 0;
unsigned long Interval2 = 3000;
unsigned long preTimer3;
unsigned long curTimer3;
unsigned long Interval3 = 1000;
unsigned long preTimer4;
unsigned long curTimer4;
unsigned long Interval4 = 10000;

//-------------------LCD screens//
LiquidCrystal lcd1(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd2(7, 13, 9, 10, 11, 12);

//-------------------Display Food Types//
String text;
int prepTime = 0;
int microTime = 0;
int countDown = 0;
//Flags
int flag = 0;
int flag2 = 0; //open hand gesture
int flag3 = 0; //put in food
int flag4 = 0;//start cooking
int flag5 = 0;

//-------------------Time//
int time = 0;

//-------------------Temp variable//
float tempC;
double tempK;
int tempReading;
float tempF;
int tempPin = 0;

//-------------------Temp Change//
int change;
int manualChange = 0;

//-------------------Variables for Real-Time & weather request and display//
int hour;
int minute;
int second;
int year;
int month;
int date;
String day[] = {"Sun","Mon","Tue","Wed","Thurs","Fri","Sat"};
String weather;
int dayi = 0;

//--------------------------------------Function Definition--------------------------------------//

//-------------------Receive real time from raspary pi//
void requestTime(){
  Serial.println('t');
  delay(2000);
  String number = Serial.readString();
  String year1 = (String)number[0]+(String)number[1]+(String)number[2]+(String)number[3];
  String month1 = (String)number[4]+(String)number[5];
  String date1 = (String)number[6]+(String)number[7];
  String hour1 = (String)number[8]+(String)number[9];
  String minute1 = (String)number[10]+(String)number[11];
  year = year1.toInt();
  month = month1.toInt();
  date = date1.toInt();
  hour = hour1.toInt();
  minute =  minute1.toInt();
}

//-------------------Receive weather from raspary pi//
void requestWeather(){
  Serial.println('w');
  delay(2000);
  weather = Serial.readString();
}

//-------------------Test leap year//
int isLeapYear(int year){
  if(year % 400 == 0) return 1;
  if(year % 100 == 0) return 0;
  if(year % 4 == 0) return 1;
  return 0;
}

//-------------------Recognize weekday//
int weekday(int d,int m, int y) {
       int weekday = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
    return weekday;
}
//-------------------Calculate time for clock_display//
void updateTime(){
  if(second % 60 == 0){
    second %= 60;
    minute++;
   }
  if(minute == 60){
    minute %= 60;
    hour++;
    requestWeather();
   } 
  if(hour == 24){
    hour %= 24;
    date++;
    dayi++;
   }
  if(dayi == 7) dayi = 0;
  if(month < 8){
     if(month == 2){
       if(isLeapYear(year) && date > 29){
          date = 1;
          month ++;
        }
       else if(date > 28){
          date = 1;
          month++;
        }
     }else if(month % 2 == 1){
        if(date > 31){
          date = 1;
          month++;
        }
     }else if(date > 30){
        date = 1;
        month++;
     }
  }else if(month >= 8){
     if(month % 2 == 0){
        if(date > 31){
          date = 1;
          month++;
        }
     }else if(date > 30){
        date = 1;
        month++;
     }
  }
  if(month > 12){
      month = 1;
      year++;
  }
}

//-------------------//
int temp (double temp1) {
  change = (int)((temp1 - 25) / 5) * 10;
  //Serial.println(change);
  return change;
}

//-------------------//
void measureTemp() {
  tempReading = analogRead(tempPin);
  tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  tempF = (tempC * 9.0) / 5.0 + 32.0; // Convert Celcius to Fahrenheit);
}

//-------------------//
int rightTleft(int change) {
  Serial.println("FROM Right to Left");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  change = change + 5;
  return change;
}

//-------------------//
int leftTright(int change) {
  Serial.println("FROM Left to Right");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  change = change - 5;
  return change;
}

//-------------------//
void push() {
  Serial.println("PUSH");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  flag4 = 1;
  flag2 = 0;
}



//----------------------------------------SETUP LOOP-------------------------------------------//
void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  delay(500);
  Serial.setTimeout(100);
  requestTime();
  requestWeather();
}



//------------------------------------Main Loop------------------------------------------------//
void loop() {
  
  curTimer = millis();
  curTimer3 = millis();

  //--------------------------------------Digital Clock display function part--------------------------------------//
  //Only display time when food recognision is not activated//--when all the flag values are 0--//
if(flag == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0 && flag5 == 0){
   lcd1.clear();        //
   lcd2.clear();        //clear the screens to print time
   
   lcd1.setCursor(10,0);    //
   lcd2.setCursor(0,0);     //Reset LCD cursor for intended visual layout
   
   second += 1;   //keep track of second increment as the arduino is turned on
   delay(1000);   //delay for 1 second so that the "second" variable is incremented correctly and 
                  //the clock is working normally
   
   updateTime();  //the function that helps update minute, hour, day, month, and even year varialbles according to 
                  //the constantly changing variable second

//lcd1 display -- printing algorithm

   if(hour < 10){
    lcd1.print(" ");    //taking care of layout
    lcd1.print(hour);
   }
   else lcd1.print(hour);

   if(second % 2 == 0) lcd1.print(":");     //enabling a blinking ":" that indicates the change in seconds -- mimicing a digital clock dispay
   else lcd1.print(" ");
   
   if(minute < 10){
    lcd1.print(0);    //taking care of layout
    lcd1.print(minute);
   }
   else lcd1.print(minute);

   lcd1.setCursor(0,0);
   lcd1.print(weather);

   lcd1.setCursor(0,1);
   lcd1.print(year);
   lcd1.print("/");
   if(month < 10){
    lcd1.print(0);    //taking care of layout
    lcd1.print(month);
   }else lcd1.print(month);
   lcd1.print("/");
   if(date < 10){
    lcd1.print(0);    //taking care of layout
    lcd1.print(date);
   }else lcd1.print(date);
   lcd1.print(" ");
   lcd1.print(day[weekday(date,month,year)]);

   
// lcd2
   if(hour < 12){
    if(hour < 3){
      lcd2.clear();
      lcd2.print("It's late! Sleep");
      lcd2.setCursor(3,1);
      lcd2.print("is necessary!"); 
    }else if(hour < 6){
      lcd2.clear();
      lcd2.print("Hardworking is");
      lcd2.setCursor(4,1);
      lcd2.print("a virtue..."); 
    }else{
      lcd2.clear();
      lcd2.print("Good morning!");
      lcd2.setCursor(0,1);
      lcd2.print("Come and eat!"); 
    }
   }else{
    if(hour > 22){
      lcd2.clear();
      lcd2.print("Time to bed,"); 
      lcd2.setCursor(3,1);
      lcd2.print("Good night."); 
    }else if(hour > 17){
      lcd2.clear();
      lcd2.print("Wanna have some");
      lcd2.setCursor(0,1);
      lcd2.print("dinner?");  
    }else if(hour > 12){
      lcd2.clear();
      lcd2.print("Good afternoon.");
    }else{
      lcd2.clear();
      lcd2.print("Lunch time!!!");
      lcd2.setCursor(0,1);
      lcd2.print("...You miss me?");
    }
   }
}
//--------------------------------------------Digital Clock dispaly function ends---------------------------------------------------------//
  
//Take serial input from raspberry pi and print it on the LED display
  if (Serial.available() > 1) {
    lcd1.setCursor(0, 0);
    lcd2.setCursor(0, 0);
    
    lcd1.clear();
    lcd2.clear();
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
    flag5 = 0;
    text = "";
    prepTime = microTime;
    //microTime = 0;
  } 
  
  //Gesture Recognition with supersonic sensor. Recognizes swipe left and swipe,
  //adjust time in reponse to your gestures.
  if (flag == 1) {
      //Measure the temperature of surrounding with thermosenser
    if ((curTimer - preTimer) > Interval) { //delay(2000);
      measureTemp();
      lcd2.setCursor(0, 0);
      lcd2.print("Temp         C  ");
      lcd2.setCursor(6, 0);
      lcd2.print(tempC);
      preTimer = millis();
    }
    prepTime = microTime;
    if (flag2 == 1) {
      //Calculate the distance on the left ultrasonic sensor
      digitalWrite(trigPin1, LOW);
      digitalWrite(trigPin1, HIGH);
      digitalWrite(trigPin1, LOW);
      duration1 = pulseIn(echoPin1, HIGH);
      distance1 = (duration1 / 2) / 29.1;
      //Calculate the distance on the right ultrasonic sensor
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
      else if ((distance1 < 18) && (value == 2)) {
        manualChange = rightTleft(manualChange);
        value2 = 0;
      }
      else if ((distance2 < 18) && (value == 1)) {
        manualChange = leftTright(manualChange);
        value2 = 0;
      }
      else if ((distance1 < 18) && (value == 0)) {
        value = 1;
      }
      else if ((distance2 < 18) && (value == 0)) {
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
      if ((curTimer - preTimer) > Interval) { //delay(2000);
        change = temp(tempC);
        preTimer = millis();
      }
      prepTime = microTime - change - manualChange;
      countDown = prepTime;
      if (prepTime < 0) {
        prepTime = 0;
        manualChange = microTime - change;
      }
      if (prepTime >= 1000) {
        lcd1.setCursor(0, 1);
        lcd1.print('!!Temp Sensor!!');
      }
      else if( prepTime>=100){
        lcd1.setCursor(0, 1);
        lcd1.print("Time:");
        lcd1.setCursor(5, 1);
        lcd1.print(prepTime);
      }
      else if (prepTime < 10) {
        lcd1.setCursor(0, 1);
        lcd1.print("Time: ");
        lcd1.setCursor(6, 1);
        lcd1.print('0');
        lcd1.setCursor(7, 1);
        lcd1.print(prepTime);
      }
      else {
        lcd1.setCursor(0, 1);
        lcd1.print("Time: ");
        lcd1.setCursor(6, 1);
        lcd1.print(prepTime);
      }
      lcd1.setCursor(10, 1);
      lcd1.print("sec");
      if (prepTime==0) {
        lcd2.setCursor(0, 1);
        lcd2.print("Pls Increase Time");
      }
      else{
        lcd2.setCursor(0, 1);
        lcd2.print("Swipe to adjust");
      }
    }
    else if ((curTimer3 - preTimer3) > Interval3) {
      lcd2.setCursor(0, 1);
      lcd2.print("Start Cooking!  ");
      countDown--;
      if(countDown>=100){
        lcd1.setCursor(0, 1);
        lcd1.print("Time:");
        lcd1.setCursor(5, 1);
        lcd1.print(countDown);
      }
      else if (countDown < 10) {
        lcd1.setCursor(0, 1);
        lcd1.print("Time: ");
        lcd1.setCursor(6, 1);
        lcd1.print('0');
        lcd1.setCursor(7, 1);
        lcd1.print(countDown );
      }
      else {
        lcd1.setCursor(6, 1);
        lcd1.print(countDown );
      }
      lcd1.setCursor(10, 1);
      lcd1.print("sec");
      preTimer3 = millis();
    }
    if (countDown <= 0 && prepTime != 0) {
      flag = 0;
      flag2=0;
      flag3 = 0;
      flag4=0;
      flag5 = 1; // restart to begining
      preTimer4=millis();
    }
  }
  if (flag5 == 1) {
    lcd2.setCursor(0, 1);
    lcd2.print("Finished Cooking ");
    lcd1.setCursor(0, 0);
    lcd1.print("Enjoy!          ");
        curTimer4=millis();
        if ((curTimer4 - preTimer4) > Interval4) { //delay(10 seconds);
        flag5=0;
        preTimer4 = millis();
      }
  }
}
