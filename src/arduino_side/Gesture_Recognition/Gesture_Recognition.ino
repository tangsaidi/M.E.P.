#include <assert.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd1(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd2(7, 13, 9, 10, 11, 12);
#define trigPin1 3
#define echoPin1 4
#define trigPin2 5
#define echoPin2 6

int value = 0;
int value2 = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;
/*
  int a1;
  int b1;
  int c;
  int d;
  int aCount;
  int bCount;
  int aSum;
  int bSum;*/

unsigned long preTimer = 0;
unsigned long curTimer;
unsigned long Interval = 1000;


unsigned long preTimer2 = 0;
unsigned long curTimer2;
unsigned long Interval2 = 3000;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  delay(500);
}


void loop() {
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
  //curTimer=millis();
  /*
    if ((curTimer - preTimer) > Interval) {
    Serial.print(value2 );
    preTimer = millis();
    }
  */
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
    rightTleft();
    value2 = 0;
  }
  else if ((distance2 < 20) && (value == 1)) {
    leftTright();
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

void push() {
  Serial.println("PUSH");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
}
void rightTleft() {
  Serial.println("FROM Right to Left");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;

}

void leftTright() {
  Serial.println("FROM Left to Right");
  delay(200);
  value = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
}

////////////////////////
//Old Version 
/*
  void loop() {
  b1 = 0;
  a1 =0;
  aCount =0;
  bCount =0;
  aSum = 0;
  bSum=0;
  c=0;
  d=0;
  for(int i =0; i<6; i++){
    a1 = sr04_1.Distance();
    b1 = sr04_2.Distance();
    delay(10);
    if (a1 > 50||a1==0) a1 = 50;
    if (b1 > 50||b1==0) b1 = 50;
    if  (a1<40) aCount ++;
    else if(b1<40) bCount ++;
    //aSum+=a1;
    //bSum+=b1;
    Serial.print("Pre: " );
    Serial.print(a1);
    Serial.print(" : " );
    Serial.println(b1);
  }

  do {
    a = sr04_1.Distance();
    b = sr04_2.Distance();
   } while (a == 0 || b == 0);
    if (a > 40) a = 40;
    if (b > 40) b = 40;

  //    Serial.print(a);
  //    Serial.println(b);

    do {
      c = sr04_1.Distance();
      d = sr04_2.Distance();
    } while (c == 0 || d == 0);


    if (aCount>1&&aCount<4) {
        for (int i = 0; i < 10; i++) {
            delay(40);
            d = sr04_2.Distance();
            if (d < 30){
              Serial.println("FROM Left to Right");
              i=20;
            }
        }
    }
    else if(bCount>1&&bCount<4) {
        for (int i = 0; i < 20; i++) {
            delay(40);
            c = sr04_1.Distance();
            if (c < 30) {
              Serial.println("FROM Right to Left");
              i=20;
            }
        }
    }
  }
*/

