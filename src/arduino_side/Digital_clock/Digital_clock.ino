#include <LiquidCrystal.h>


LiquidCrystal lcd1(7,8,9,10,11,12);
LiquidCrystal lcd2(7,13,9,10,11,12);

//Variables for Real-Time & weather request and display 
int hour;
int minute;
int second = 0;
int year;
int month;
int date;
String day[] = {"Sun","Mon","Tue","Wed","Thurs","Fri","Sat"};
String weather;
int dayi = 0;
//
//Receive real time from raspary pi
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
//

//Receive weather from raspary pi
void requestWeather(){
  Serial.println('w');
  delay(2000);
  weather = Serial.readString();
}
//

//Test leap year
int isLeapYear(int year){
  if(year % 400 == 0) return 1;
  if(year % 100 == 0) return 0;
  if(year % 4 == 0) return 1;
  return 0;
}
//

int weekday(int d,int m, int y) {
       int weekday = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
    return weekday;
}

void setup() {
  lcd1.begin(16,2);
  lcd2.begin(16,2);
  Serial.begin(9600);
  Serial.setTimeout(100);
  requestTime();
  requestWeather();
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
   lcd1.print(weather);

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
//Digital Clock dispaly function ends
   
}

