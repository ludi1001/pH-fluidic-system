#include <AFMotor.h>

#define MEASURE     A5
#define RED         A0
#define GREEN       A1
#define BLUE        A2
#define NUM_SAMPLES 20

#define VALVE_REAGENT A4
#define VALVE_WATER   A3

#define TRIALS 1

AF_DCMotor sampleMotor(1, MOTOR12_64KHZ);
AF_DCMotor reagentMotor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor drainMotor(3, MOTOR12_1KHZ); //will only run at 1 kHz

class Valve {
  private:
    int pin;
  public:
    Valve(int pin) : pin(pin) {}
    void init();
    void open();
    void close();
};

void Valve::init() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Valve::open() {
  digitalWrite(pin, HIGH);
  delay(2000);
}

void Valve::close() {
  digitalWrite(pin, LOW);
  delay(1000);
}

Valve valveReagent(VALVE_REAGENT);
Valve valveWater(VALVE_WATER);

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps

  //setup motors
  sampleMotor.setSpeed(120); // set the speed to 200/255
  reagentMotor.setSpeed(120);
  drainMotor.setSpeed(255);
  
  //setup LEDs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
  //setup valves
  valveReagent.init();
  valveWater.init();
  
  Serial.println("Ready!");
}

void loop() {
  
  if (Serial.available() > 0) {
      Serial.println("===");
      // read the incoming byte:
      int c = Serial.read();
      if(c == 'm') {
        int motorNum = Serial.parseInt();
        
        Serial.print("Motor selected: ");
        Serial.println(motorNum);
        
        AF_DCMotor* motor;
        
        if(motorNum == 0) {
          motor = &sampleMotor;
        }
        else if(motorNum == 1) {
          motor = &reagentMotor;
        }
        else if(motorNum == 2) {
          motor = &drainMotor;
        }
        else {
          Serial.println("bad motor number");
          return;
        }
        
        if(!Serial.available()) {
          Serial.println("bad motor command format");
          return;
        }
        
        c = Serial.read();
        
        if(c == 'd') {
          Serial.println("Running forward");
          motor->run(FORWARD);
        }
        else if(c == 'a') {
          Serial.println("Running backward");
          motor->run(BACKWARD);
        }
        else if(c == 's') {
          Serial.println("Stopping motor");
          motor->run(RELEASE);
        }
        else if(c == 'w') {
          long duration = Serial.parseInt();
          Serial.print("Run for ");
          Serial.println(duration);
          if(confirm()) {
            Serial.println("running...");
            motor->run(FORWARD);
            delay(duration);
            motor->run(RELEASE);
            Serial.println("stopped");
        }
        else if(c == 'x') {
          int spd = Serial.parseInt();
          Serial.print("Setting speed to ");
          Serial.println(spd);
          if(spd <= 0 || spd >= 256) {
            Serial.println("Invalid speed");
            return;
          }
          motor->setSpeed(spd);
        }
      }
    }
    else if(c == 'r') {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
    }
    else if(c == 'b') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
      delay(500);
    }
    else if(c == 'g') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      delay(500);
    }
    else if(c == 'o') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
    }
    else if(c == 'a') {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
      double red = doRead(NUM_SAMPLES);
      
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      delay(500);
      double green = doRead(NUM_SAMPLES);
      
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
      delay(500);
      double blue = doRead(NUM_SAMPLES);
      
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
      double background = doRead(NUM_SAMPLES);
      
      String str = "back: ";
      str = str + background + ", R: " + red + ", G: " + green + ", B: " + blue;
      Serial.println(str);
    }
    else if(c == 'q') {
      int on = Serial.parseInt();
      if(on == 1) {
        valveReagent.open();
        Serial.println("Reagent valve opened");
      }
      else {
        valveReagent.close();
        Serial.println("Reagent valve closed");
      }
    }
    else if(c == 'e') {
      int on = Serial.parseInt();
      if(on == 1) {
        valveWater.open();
        Serial.println("Water valve opened");
      }
      else {
        valveWater.close();
        Serial.println("Water valve closed");
      }
    }
    else if(c == 's') {
      int seq = Serial.parseInt();
      Serial.print("Sequence chosen: ");
      Serial.println(seq);
      if(!confirm()) return;
      if(seq == 0) {
        Serial.println("Initiating full sequence...");
        doMeasure();
      }
      else {
        Serial.println("undefined sequence");
      }
    }
    else if(c == 't') {
      int val = analogRead(MEASURE);
      Serial.print("Measurement: ");
      Serial.println(val);
    }
    else {
        Serial.print("Unrecognized command: ");
        Serial.println(c, DEC);
    }
  }
}

int confirm() {
  Serial.println("ok? (y/n)");
  while(!Serial.available())
    ;
  int response = Serial.read();
  return response == 'y';
}

double doRead(int samples) {
  unsigned long s = 0;
  for(int i = 0; i < samples; ++i) {
    s += analogRead(MEASURE);
    delay(50);
  }
  double avg = s;
  avg /= samples;
  return avg;
}

void doColorimetry() {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
      double red = doRead(NUM_SAMPLES);
      
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      delay(500);
      double green = doRead(NUM_SAMPLES);
      
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
      delay(500);
      double blue = doRead(NUM_SAMPLES);
      
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
      double background = doRead(NUM_SAMPLES);
      
      String str = "back: ";
      str = str + background + ", R: " + red + ", G: " + green + ", B: " + blue;
      Serial.println(str);
}

#define PAUSE(x) { Serial.println(x); if(!confirm()) return; }
void doMeasure() {
  PAUSE("Filling sample tube...");
  fillSampleTube();
  for(int i = 0; i < TRIALS; ++i) {
    PAUSE("Filling reagent tube...");
    fillReagentTube();
    PAUSE("Pumping sample and reagent...");
    pumpSample();
    PAUSE("Doing reading...");
    doColorimetry();
    PAUSE("Emptying reagent tube...");
    emptyReagentTube();
    
    if(i == TRIALS - 1) {
      PAUSE("Emptying sample tube...");
      emptySampleTube();
    }
    PAUSE("Draining...");
    drain(48000);
    PAUSE("Flusing with water...");
    flushWater();
    PAUSE("Emptying reagent tube...");
    emptyReagentTube();
    PAUSE("Draining...");
    drain(48000);
  }
  Serial.println("DONE");
}

void pumpSample() {
  //pump reagent first
  valveReagent.open();
  reagentMotor.run(FORWARD);
  delay(19000);
  reagentMotor.run(RELEASE);
  valveReagent.close();
  
  //pump sample in
  sampleMotor.run(FORWARD);
  delay(45000);
  sampleMotor.run(RELEASE);
}

void drain(long drainTime) {
  drainMotor.run(FORWARD);
  delay(drainTime);
  drainMotor.run(RELEASE);
}


void fillReagentTube() {
  valveReagent.open();
  reagentMotor.run(FORWARD);
  delay(8750);
  reagentMotor.run(RELEASE);
  valveReagent.close();
}

void emptyReagentTube() {
  reagentMotor.run(FORWARD);
  delay(8000);
  reagentMotor.run(RELEASE);
}

void fillSampleTube() {
  sampleMotor.run(FORWARD);
  delay(11000);
  sampleMotor.run(RELEASE);
}

void emptySampleTube() {
  sampleMotor.run(FORWARD);
  delay(13000);
  sampleMotor.run(RELEASE);
}

void flushWater() {
  reagentMotor.setSpeed(255);
  valveWater.open();
  reagentMotor.run(FORWARD);
  delay(20000);
  reagentMotor.run(RELEASE);
  valveWater.close();
  reagentMotor.setSpeed(120);
}
