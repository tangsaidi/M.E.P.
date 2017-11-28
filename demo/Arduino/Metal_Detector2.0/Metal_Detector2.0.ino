// Arduino wiring:
// 220Ohm resistor on D2
// diode (-) on pin A0 and (+) on loop-resistor connection
// 10nF capacitor between A0 and ground
// LED1 on pin 8
// LED2 on pin 9

//Set Number of Pulse per measurement
const byte nOfpulse = 10; 

//Define all the pins
const byte pin_pulse=A4;
const byte pin_cap  =A3;
const byte pin_LED1 =2;
const byte pin_tone =A5;

int count=0; 

//Instead of using delay(), a timer is used to reduce the "update rate" of a block of code  
unsigned long preTimer5;         //Previous Time 
unsigned long curTimer5;         //Current Time
unsigned long Interval5 = 5000;  //Amount of delay
int flag5 =0;
int flag6 =0;
void setup() {
  Serial.begin(9600);
  //Set up all the pins
  pinMode(pin_cap, INPUT);  
  pinMode(pin_pulse, OUTPUT);
  pinMode(pin_LED1, OUTPUT);
  //pinMode(pin_tone, OUTPUT);
  //Set the pins to low 
  digitalWrite(pin_pulse, LOW);
  digitalWrite(pin_LED1, LOW);
  //digitalWrite(pin_tone, LOW);
}

const int nOfMeasure =200;  //measurements to take
long int totalSum=0; //running sum of 64 sums 
long int skip=0;   //number of skipped sums
long int diff=0;   //difference between sum and avgsum
long int flash_period=0; //period (in ms) 
long unsigned int prev_flash=0; //time stamp of previous flash
long unsigned int timestamp =0;

void loop() {
  if(flag6==0){
  int minval=1023;
  int maxval=0;
  //perform measurement
  long unsigned int sum=0; 
  for (int x=0; x<nOfMeasure; x++){
    //reset the capacitor
    pinMode(pin_cap,OUTPUT);
    digitalWrite(pin_cap,LOW);
    delayMicroseconds(20);
    pinMode(pin_cap,INPUT);
    //Send pulses through the coil
    for (int i = 0; i < nOfpulse; i++) {
      digitalWrite(pin_pulse,HIGH); //
      delayMicroseconds(3);
      digitalWrite(pin_pulse,LOW);  //takes 3.5 microseconds
      delayMicroseconds(3);
    }
    //read the charge on the capacitor
    int val = analogRead(pin_cap); 
    minval = min(val,minval);
    maxval = max(val,maxval);
    sum+=val;
 
    timestamp=millis();
    //Determine the state of lad
    
    byte ledstat=0; 
    //determine if LEDs should be on or off
    if (timestamp<prev_flash+10){
      if (diff<0)ledstat=1;
    }
    if (timestamp>prev_flash+flash_period){
      if (diff<0)ledstat=1;
      prev_flash=timestamp;   
    }
    if (flash_period>1000)ledstat=0;

    //Turn on the led if ledstat is 1 
    // Turn off the led if ledstat is 0c
    if (ledstat==0){
      digitalWrite(pin_LED1,LOW);
      noTone(pin_tone);
    }
    if (ledstat==1){
      digitalWrite(pin_LED1,HIGH);
      tone(pin_tone,500);
      count++;
    }
  }
  //subtract minimum and maximum value to remove spikes
  sum-=minval; 
  sum-=maxval;
  
  //Average all 200 measurements 
  if (totalSum==0) totalSum=sum<<6; //set totalSum to expected value
  long int avgsum=(totalSum+32)>>6; 
  diff=sum-avgsum;
  if (abs(diff)< avgsum>>10){    //adjust for small changes
    totalSum=totalSum+sum-avgsum;
    skip=0;
  } else {
    skip++;
  }
  if (skip>64){     // break off in case of prolonged skipping
    totalSum=sum<<6;
    skip=0;
  }

  if (diff==0) flash_period=1000000;
  else flash_period=avgsum/(2*abs(diff));
    curTimer5=millis();                  
    if ((curTimer5 - preTimer5) > Interval5&&flag5==1) { 
        flag5=0;   
        count=0;
        //turn off the indicator of "done cooking"
        //Serial.println("Done"); 
        preTimer5 = millis();
        
    }
    if(count>=3&&flag5==0){ 
    Serial.println("Metal Detected"); 
    count=0;
    flag5=1;
    preTimer5 = millis();
  }
 }
  
  /*
  if (debug){
    Serial.print(minval); 
    Serial.print(" ");
    Serial.print(maxval); 
    Serial.print(" ");
    Serial.print(sum); 
    Serial.print(" ");
    Serial.print(avgsum); 
    Serial.print(" ");
    Serial.print(diff); 
    Serial.print(" ");
    Serial.print(flash_period); 
    Serial.println();
  }
  */
}
