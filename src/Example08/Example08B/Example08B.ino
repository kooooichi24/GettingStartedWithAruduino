// Example08B: Arduino ネットワークランプ

const int SENSOR = 0;
const int BUTTON = 8;
const int R_LED = 9;
const int G_LED = 10;
const int B_LED = 11;

int val = 0; // センサから読みとった値を格納する変数

int btn = LOW;
int old_btn = LOW;
int state = 0;

byte r = 0;
byte g = 0;
byte b = 0;

void setup() {
  Serial.begin(9600); // シリアルポートを開く
  pinMode(BUTTON, INPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  // Note: アナログピンは自動的に入力として設定される．
}

void loop() {
  val = analogRead(SENSOR); // センサから値を読む
  Serial.println(val);

  // if (Serial.available() > 0) {

  // }

  btn = digitalRead(BUTTON);
  if (btn==HIGH && old_btn==LOW) {
    state = 1 - state;
  }
  old_btn = btn;
  
  if (state == 1) {
    analogWrite(R_LED, 255);
    analogWrite(G_LED, 255);
    analogWrite(B_LED, 255);
  } else {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
  }
}