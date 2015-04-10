void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Turning LED on...");
  digitalWrite(13, HIGH);
  delay(500);
  printVal();
  delay(500);
  
  Serial.println("Turning LED off...");
  digitalWrite(13, LOW);
  delay(500);
  printVal();
  delay(500);
}

void printVal() {
  int val = analogRead(A0);
  Serial.print("Value: ");
  Serial.println(val);
}
