#include <LiquidCrystal.h>


LiquidCrystal lcd1(7,8,9,10,11,12);
LiquidCrystal lcd2(7,2,9,10,11,12);

//clock

int hour = 12;
int minute = 0;
int second = 0;
String weather[] = {"Sunny","Cloudy","Windy","Rainy"};
int year = 2017;
int month = 10;
int date = 25;
String day[] = {"Mon","Tue","Wed","Thurs","Fri","Sat","Sun"};
int dayi = 0;

int isLeapYear(int year){
  if(year % 400 == 0) return 0;
  if(year % 100 == 0) return 1;
  if(year % 4 == 0) return 0;
  return 1;
}
//

//print scan result
int recomTime;
String text;
//

//timer
//

void setup() {
  // put your setup code here, to run once:
  lcd1.begin(16,2);
  lcd2.begin(16,2);
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {
  
//Digital Clock display function part
   
   lcd1.setCursor(10,0);
   lcd2.setCursor(0,0);
   
   second += 1;
   delay(1000);
   
   if(second % 60 == 0){
    second %= 60;
    minute++;
   }
   if(minute == 60){
      minute %= 60;
      hour++;
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

//lcd1

   if(hour < 10){
    lcd1.print(" ");
    lcd1.print(hour);
   }
   else lcd1.print(hour);

   if(second % 2 == 0) lcd1.print(":");
   else lcd1.print(" ");
   
   if(minute < 10){
    lcd1.print(0);
    lcd1.print(minute);
   }
   else lcd1.print(minute);

   lcd1.setCursor(0,0);
   lcd1.print(weather[0]);

   lcd1.setCursor(0,1);
   lcd1.print(year);
   lcd1.print("/");
   if(month < 10){
    lcd1.print(0);
    lcd1.print(month);
   }else lcd1.print(month);
   lcd1.print("/");
   if(date < 10){
    lcd1.print(0);
    lcd1.print(date);
   }else lcd1.print(date);
   lcd1.print(" ");
   lcd1.print(day[dayi]);

   
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
//Digital Clock dispaly function ends

//Timer function part starts
//Timer function part ends

//Read serial input about what food it is and a recommended time to heat
    if(Serial.available() > 1){
      text = Serial.readStringUntil(';');
      recomTime = Serial.parseInt();
    }




   
   
}

