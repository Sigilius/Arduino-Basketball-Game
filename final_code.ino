#include <Simple5641AS.h>
int score = 0; int input;
bool game = false;
bool reset = false;
int ir_sensor = 12;
int LED = 13;
const uint8_t segmentPins[] = { 4, 6, 3, 10, 9, 2, 5, 13 };
const uint8_t digitSelectionPins[] = { 12, 11, 8, 7 };
Simple5641AS component( segmentPins, digitSelectionPins );

void setup() { 
  Serial.begin(9600);
  Serial.println("Program started!");
  pinMode(ir_sensor, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
   //digitalWrite(LED, HIGH);
   component.displayNumber(1, score);
   check_start();
   if(game){
    input = digitalRead(ir_sensor);
    if(input ==0){
      score++;
      tone(LED, 2000);
      delay(500);
      noTone(LED);    
      }
   }
   else if(reset){
     score = 0;
     component.displayNumber(2, score);
     delay(1000);
     reset = false;
   }
   else{
     component.displayNumber(2, score);
     delay(1000);
   }
}

void check_start(){
  if(Serial.available()>0){
    char val = Serial.read();
    if(val == 'S'){
      game = true;
    }
    else if(val == 'O'){
      game = false;
    }
    else if(val == 'R'){
      game = false;
      reset = true;
    }
   }
   
}
