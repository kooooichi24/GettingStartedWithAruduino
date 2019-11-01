// Example08A: Arduinoネットワークランプ

import processing.serial.*;

// 図書のホームページが見つからないため，xml+ホームページで検索して一番上位のxmlページを利用する．
String feed = "http://www.xmlmaster.org/murata/index.xml";

Serial port;
color c = color(0,0,0);

void setup() {
  size(640, 480);
  frameRate(10);

  PFont font = loadFont("HelveticaNeue-Bold-32.vlw");
  fill(255);
  textFont(font, 16);

  // Note:
  // 以下のコードはSerial.list()で得られるポートの0番目の要素がArduinoであることを前提としています．
  // そうでない場合は，次の1行(println)をコメントアウトして再度スケッチを実行してシリアルポートのリストを表示し，
  // Arduinoのポートを確認してください．
  // println(Serial.list());
  String arduinoPort = Serial.list()[1];

  // Arduinoに接続
  port = new Serial(this, arduinoPort, 9600);
}

void draw() {
  background(c);
  displayBasicInfo();


  // Arduinoへデータを送る
  port.write("cs");

  // データが待っているかチェック
  if (port.available() > 0) {

  } else {

  }
}


void displayBasicInfo() {
  text("Arduino Networked Lamp", 10, 40);
  text("Reading feed:", 10, 100);
  text(feed, 10, 140);

  text("Next update in " + "xxx" + " seconds", 10, 450);
  // probably continue...
}