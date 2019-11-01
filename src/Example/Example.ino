// Example: ただのExampleファイルです．
// photoersistor試してみました．

const int LED = 11;
const int SENSOR = 0;
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  val = analogRead(SENSOR);

  Serial.println(val);
  analogWrite(LED, val/4);
  delay(10);
}