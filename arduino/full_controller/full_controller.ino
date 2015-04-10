#include <AFMotor.h>

#define RED 8
#define GREEN 9
#define BLUE 10

AF_DCMotor sampleMotor(1, MOTOR12_64KHZ);
AF_DCMotor reagentMotor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor drainMotor(3, MOTOR12_1KHZ); //will only run at 1 kHz

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps

  //setup motors
  sampleMotor.setSpeed(200); // set the speed to 200/255
  reagentMotor.setSpeed(200);
  drainMotor.setSpeed(200);
  
  //setup LEDs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
  Serial.println("Ready!");
}

void loop() {
  
  if (Serial.available() > 0) {
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
    }
    else if(c == 'b') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
    }
    else if(c == 'g') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
    }
    else if(c == 'o') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
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
