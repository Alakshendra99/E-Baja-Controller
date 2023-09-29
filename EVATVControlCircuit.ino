#include<Wire.h>
#include<LiquidCrystal_I2C.h>

/*- Inputs -*/
const int N = 13;
const int R = 12;
const int B = 8;
const int A = 10;
const int Key  = 9;
const int Kill = 11;

/*- Outputs -*/
const int TSAL = 7;
const int RTDS = 6;
const int Reverse = 5;
const int Contact = 4;

/*- Parameters -*/
bool Latch = false;
bool KeyState = false;
const int Timeout = 250;
float Entry;
float Time;

/*- LCD -*/
LiquidCrystal_I2C LCD(0x27, 16, 2);

void setup() {
  /*- Setting-Up-GPIO -*/
  pinMode(N, INPUT);
  pinMode(R, INPUT);
  pinMode(B, INPUT);
  pinMode(A, INPUT);
  pinMode(Kill, INPUT);
  pinMode(Key,  INPUT);
  
  pinMode(TSAL, OUTPUT);
  pinMode(RTDS, OUTPUT);
  pinMode(Reverse, OUTPUT);
  pinMode(Contact, OUTPUT);

  /*- Parking-Everything -*/
  digitalWrite(TSAL, HIGH);
  digitalWrite(RTDS, HIGH);
  digitalWrite(Reverse, HIGH);
  digitalWrite(Contact, HIGH);

  Serial.begin(9600);
  LCD.begin();
  LCD.backlight();
  Serial.println("Alright, Lets Do This!");
}

void loop() {
  LCD.clear();
  /*- Kill-Switch-ON -*/
  if(digitalRead(Kill)==HIGH){
    /*- Parking-Everything -*/
    Serial.println("Killed");
    digitalWrite(TSAL, HIGH);
    digitalWrite(RTDS, HIGH);
    digitalWrite(Reverse, HIGH);
    digitalWrite(Contact, HIGH);
    Latch = false;
    KeyState = digitalRead(Key);
  }
  /*- Kill-Switch-OFF -*/
  else{
    /*- HV-OFF -*/
    if(Latch==false){
      digitalWrite(RTDS   , !digitalRead(R));
      digitalWrite(Reverse, !digitalRead(R));
      KeyState = digitalRead(Key);
      /*- Starting-Condition -*/
      if(!digitalRead(A)&&digitalRead(N)&&!digitalRead(Kill)&&!digitalRead(B)&&!digitalRead(R)){
        Serial.println("Startup Sequence");
        /*- Checking-Key-Switch -*/
        if(KeyState==false){
          Serial.println("Ready To Start");
          /*- Key-Switch-ON -*/
          if(digitalRead(Key)==HIGH){
            Serial.println("\nLatched\nHV Circuit ON");
            KeyState = true;
            Latch = true;

            /*- HV-Relay-ON -*/
            digitalWrite(Contact, LOW);

            Serial.println("RTDS");
            /*- RTDS-ON -*/
            digitalWrite(RTDS,LOW);
            for (int i=0;i<4;i++){
              /*- TSAL-While-ON -*/
              Entry = millis();
              Time  = millis();
              while((Time-Entry)<Timeout){
                digitalWrite(TSAL,LOW);
                digitalWrite(Reverse,!digitalRead(R));
                Time = millis();
              }

              /*- TSAL-While-OFF -*/
              Entry = millis();
              Time  = millis();
              while((Time-Entry)<Timeout){
                digitalWrite(TSAL,HIGH);
                digitalWrite(Reverse,!digitalRead(R));
                Time = millis();
              }    
            }
            /*- Parking-The-RTDS -*/
            digitalWrite(RTDS,HIGH);
          }
        }
      }
    }
    /*- HV-ON -*/
    else if(Latch==HIGH&&digitalRead(Key)==HIGH){
      digitalWrite(Contact, LOW);
      /*- TSAL-Blink -*/
      Entry = millis();
      Time  = millis();
      while((Time-Entry)<Timeout){
        digitalWrite(TSAL,LOW);
        digitalWrite(RTDS,!digitalRead(R));
        digitalWrite(Reverse,!digitalRead(R));    
        Time = millis();
      }
      
      Entry = millis();
      Time  = millis();
      while((Time-Entry)<Timeout){
        digitalWrite(TSAL,HIGH);
        digitalWrite(RTDS,!digitalRead(R));
        digitalWrite(Reverse,!digitalRead(R));
        Time = millis();
      }        
    }
    else{
      digitalWrite(Contact, HIGH);
      Latch = false;
      KeyState = false;
      Serial.println("\nKey OFF\nHV Circuit OFF");
    }
  }
}
