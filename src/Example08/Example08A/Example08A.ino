// Example08A: Arduinoネットワークランプ

import processing.serial.*;
import java.net.*;
import java.io.*;
import java.util.*;

// 図書のホームページが見つからないため，変更した．
String feed = "https://blog.arduino.cc/feed/";

int interval = 10; // フィードを取得する時間
int lastTime;
int n;

Serial port;
color c;
String cs;

int light = 0;

int window = 0;
int make = 0;
int arduino = 0;

String buffer = ""; // arduinoから送られてきた文字を溜めるところ

void setup() {
  size(640, 480);
  frameRate(5);

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
  lastTime = 0;
  fetchData();
}

void draw() {
  background(c);
  n = (interval - (millis()-lastTime)/1000);

  // 3つの値を基に色を組み立てる
  c = color(make, window, arduino);
  cs = "#" + hex(c, 6);

  displayBasicInfo();
  
  if (n <= 0) {
    fetchData();
    lastTime = millis();
  }

  // Arduinoへデータを送る
  port.write(cs);

  // データが待っているかチェック
  if (port.available() > 0) {
    int inByte = port.read(); // 1バイト読み込む
    
    // newline(LF)か確認
    if (inByte != 10) {
      buffer += char(inByte);
    } else {
      // newlineが届いたので，データを処理する

      if (buffer.length() > 1) {
        // 最後の文字は改行コードなので切り落とす
        buffer = buffer.substring(0, buffer.length() - 1);

        // バッファの文字を数値(int)に変換
        light = int(buffer);

        // 次の読み込みサイクルのためにバッファを掃除
        buffer = "";

        // Arduinoからはセンサの値がどんどんと送られてくるため，
        // 最新のデータを得るために溜まってしまったものを削除
        port.clear();
      }
    }
  }
}


void displayBasicInfo() {
  text("Arduino Networked Lamp", 10, 40);
  text("Reading feed:", 10, 100);
  text(feed, 10, 140);

  text("Next update in " + n + " seconds", 10, 450);
  
  text("make", 10, 200);
  text(" " + make, 130, 200);
  rect(200, 172, make, 28);

  text("window ", 10, 240);
  text(" " + window, 130, 240);
  rect(200, 212, window, 28);

  text("arduino", 10, 280);
  text(" " + arduino, 130, 280);
  rect(200, 252, arduino, 28);

  // 画面に色情報を表示
  text("sending", 10, 340);
  text(cs, 200, 340);
  text("light level", 10, 380);
  rect(200, 352, light/10.23, 28); // 最大1023から最大100へ
}

void fetchData() {
  // フィードのパースにこれらの文字列を使用
  String data;
  String chunk;

  // カウンタをゼロに
  make = 0;
  window = 0;
  arduino = 0;

  try {
    URL url = new URL(feed); // URLを表すオブジェクト
    URLConnection conn = url.openConnection(); // 接続を準備
    conn.connect(); // Webサイトに接続完了

    // 接続先からやってくるデータを1行ずつバッファするための
    // 仮想的なパイプ
    BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));

    // フィードを1行ずつ読む
    while ((data = in.readLine()) != null) {
    
      StringTokenizer st = new StringTokenizer(data, "\"<>,.()[] "); // それを分解
      while (st.hasMoreTokens()) {
        chunk = st.nextToken().toLowerCase(); // 小文字に変換

        if (chunk.indexOf("make") >= 0) make++;
        if (chunk.indexOf("window") >= 0) window++;
        if (chunk.indexOf("arduino") >= 0) arduino++;
      }
    }

    // 各語を参照した回数の64を上限とする
    if (make > 64) make = 64;
    if (window > 64) window = 64;
    if (arduino > 64) arduino = 64;

    // 4を掛けて最大値を255にしておくと
    // 色を4byteで表現するのに便利
    //   ↑4byteとはRGBAのことかな？？
    //   でもでも，hex(c,6)で6桁にしてるのに4byte???
    //   わかった：color(r,g,b)にした時は，自動的にa=1となる．
    //           そのため，AAAAAAAARRRRRRRRGGGGGGGGBBBBBBBBの4byteとなり，その後16進数表現するためにhex()した際に6桁と指定している．(AAの2桁を含まない)
    make *= 4;
    window *= 4;
    arduino *= 4;
  } catch (Exception e) {
    // errorの場合はスケッチを停止．
    e.printStackTrace();
    System.out.println("ERROR: "+e.getMessage());
  }
}