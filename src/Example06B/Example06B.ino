// Example06B: アナログ入力の値に応じてLEDの明るさを変える

const int LED = 13;
int val = 0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  val = analogRead(3);

  analogWrite(LED, val/4);
  delay(10);
}