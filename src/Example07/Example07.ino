// Example07: アナログ入力ピン0の値をコンピュータに送る.
// アップロードの後に，[Serial Monitor]ボタンを押すこと

const int SENSOR = 0;
int val = 0;

void setup() {
  // シリアルポートを開きます．
  // 毎秒9600bitでコンピュータにデータを送信します．
  Serial.begin(9600);
}

void loop() {
  val = analogRead(SENSOR);

  Serial.println(val);
  delay(100);
}