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
int pointer = 0;
char buffer[7];
byte inByte = 0;

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

  if (Serial.available() > 0) {
    // 受信したデータを読み取る
    inByte = Serial.read();

    // マーカ(#)が見つかったら，続く6文字が色情報
    while (pointer < 6) {
      buffer[pointer] = Serial.read();
      pointer++;
    }

    // 3つの16進数の数字が揃ったので，RGBの3バイトにデコードする．
    r = hex2dec(buffer[1]) + hex2dec(buffer[0]) * 16;
    g = hex2dec(buffer[3]) + hex2dec(buffer[2]) * 16;
    b = hex2dec(buffer[5]) + hex2dec(buffer[4]) * 16;

    pointer = 0; // 次にバッファを使うときのためにクリア．
  }

  btn = digitalRead(BUTTON);
  if (btn==HIGH && old_btn==LOW) {
    state = 1 - state;
  }
  old_btn = btn;
  
  if (state == 1) {
    analogWrite(R_LED, r);
    analogWrite(G_LED, g);
    analogWrite(B_LED, b);
  } else {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
  }
  delay(100);
}

// 16進数を整数に変換
int hex2dec(byte c) {
  if (c>='0' && c<='9') {
    return c - '0';
  } else if (c>='A' && c<='F') {
    return c - 'A' + 10;
  }
}