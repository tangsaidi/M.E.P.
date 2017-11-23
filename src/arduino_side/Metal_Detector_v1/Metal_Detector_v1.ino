  #define BUZZER_PIN 3
  #define MIN_FREQUENCY 31
  #define FREQ_READ_PINA 5
  #define BASE (unsigned int)200
  #define SCALE 10 
 unsigned long FRE_DELTA;
 long REF_FRE = NULL;
 long DYN_FRE = 0;
 int rd = 1;
  
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FREQ_READ_PINA, INPUT);
  
  
}

void loop() {
//  tone(BUZZER_PIN, MIN_FREQUENCY + BASE + 400, 3000);
//  delay(4000);
  if(REF_FRE == NULL)
    REF_FRE = analogRead(FREQ_READ_PINA);
    Serial.println(REF_FRE);
//    delay(100);

   if(analogRead(FREQ_READ_PINA) > DYN_FRE + 10){
      DYN_FRE = analogRead(FREQ_READ_PINA);
   }else{
    delay(1000);
    DYN_FRE = REF_FRE;
   }
   
   Serial.print("---");
    Serial.println(DYN_FRE);
   FRE_DELTA = abs(DYN_FRE - REF_FRE);
    Serial.print("DEL");
    Serial.println(FRE_DELTA);
//    tone(BUZZER_PIN, MIN_FREQUENCY);
    
//   if(FRE_DELTA > 30){
//   Serial.println("YES");
//    tone(BUZZER_PIN,MIN_FREQUENCY + FRE_DELTA * SCALE, 1000);
////    delay(3000);
//   }
//   else
//    noTone(BUZZER_PIN);
}
