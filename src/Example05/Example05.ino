// Example05: ボタンを押すとLEDが点灯し，ボタンから指を離したあとも着いたままにする．
// ハウジング対策
// ボタンを押し続ける動作で明るさが変化する．

const int LED = 9;
const int BUTTON = 13;

int val = 0;
int old_val = 0;
int state = 0;

int brightness = 128;
unsigned long int pushStartTime = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  val = digitalRead(BUTTON);

  if (val==HIGH && old_val==LOW) {
    state = 1 - state;
    pushStartTime = millis();
    delay(10);
  }

  if (val==HIGH && old_val==HIGH) {
    if (state==1 && (millis()-pushStartTime)>500) {
      brightness++;
      delay(10);
      if (brightness > 255) {
        brightness = 0;
      }
    }
  }

  old_val = val;

  if (state == 1) {
    analogWrite(LED, brightness);
  } else {
    analogWrite(LED, 0);
  }
}