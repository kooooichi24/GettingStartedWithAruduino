// Example: ただのExampleファイルです．
// シリアルプロッタで2個以上のデータを表示させる

const int SENSOR = 0;
int val = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(SENSOR);

  Serial.println(val);
  delay(10);
}