#define RED 8
#define GREEN 9
#define BLUE 10
#define NUM_SAMPLES 20

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void loop() {
  if(Serial.available() > 0) {
    int command = Serial.read();
    
    if(command == 'r') {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
    }
    else if(command == 'b') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
      delay(500);
    }
    else if(command == 'g') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      delay(500);
    }
    else if(command == 'o') {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(500);
    }
    else if(command == 'a') {
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
  }
  // put your main code here, to run repeatedly:
  //int val = analogRead(A0);
  //Serial.println(val);
  //delay(100);
  Serial.println(doRead(20));
}

double doRead(int samples) {
  unsigned long s = 0;
  for(int i = 0; i < samples; ++i) {
    s += analogRead(A0);
    delay(50);
  }
  double avg = s;
  avg /= samples;
  return avg;
}

