//www.elegoo.com
//2016.12.08
#include "SR04.h"
#include <assert.h>

#define TRIG_PIN1 12
#define ECHO_PIN1 11
#define TRIG_PIN2 13
#define ECHO_PIN2 10

SR04 sr04_1 = SR04(ECHO_PIN1, TRIG_PIN1);
SR04 sr04_2 = SR04(ECHO_PIN2,TRIG_PIN2);

long a;
long b;
long c;
long d;

void setup() {
    Serial.begin(9600);
    delay(500);
    do {
    a = sr04_1.Distance();
    b = sr04_2.Distance();
    } while (a == 0 || b == 0);
    if (a > 50) a = 50;
    if (b > 50) b = 50;
    Serial.print(a);
    Serial.print(b);
}

void loop() {
    delay(60);
    do {
      c = sr04_1.Distance();
      d = sr04_2.Distance();
    } while (c == 0 || d == 0);
    
    if (c < a - 5) {
        for (int i = 0; i < 20; i++) {
            delay(60);
            d = sr04_2.Distance();
            if (d < b - 5){
              Serial.println("FROM RIGHT TO LEFT");
              delay(1000);
              return;
            }
        }
    }

    if (d < b -5) {
        for (int i = 0; i < 20; i++) {
            delay(60);
            c = sr04_1.Distance();
            if (c < a -5) {
              Serial.println("FROM LEFT TO RIGHT");
              delay(1000);
              return;
            }
        }
    }
     
}

