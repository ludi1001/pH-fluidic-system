#include <AFMotor.h>
AF_DCMotor motor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  motor.setSpeed(200); // set the speed to 200/255
}

void loop() {
  
  if (Serial.available() > 0) {
      // read the incoming byte:
      int c = Serial.read();

      if(c == 'd') {
        Serial.println("Running forward");
        motor.run(FORWARD);
      }
      else if(c == 'a') {
        Serial.println("Running backward");
        motor.run(BACKWARD);
      }
      else if(c == 's') {
        Serial.println("Stopping motor");
        motor.run(RELEASE);
      }
      else if(c == 'w') {
        long duration = Serial.parseInt();
        Serial.print("Test run for ");
        Serial.println(duration);
        if(confirm()) {
          Serial.println("running...");
          motor.run(FORWARD);
          delay(duration);
          motor.run(RELEASE);
          Serial.println("stopped");
        }
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
