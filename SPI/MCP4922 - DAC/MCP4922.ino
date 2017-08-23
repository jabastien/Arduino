#include "pins_arduino.h"
#include <SPI.h>

#define LDAC   9              // ラッチ動作出力ピン

void setup() {
     // 制御するピンは全て出力に設定する
     pinMode(LDAC,OUTPUT) ;
     // SPIの初期化処理を行う
     SPI.begin() ;                        // ＳＰＩを行う為の初期化
     SPI.setBitOrder(MSBFIRST) ;          // ビットオーダー
     SPI.setClockDivider(SPI_CLOCK_DIV8) ;// クロック(CLK)をシステムクロックの1/8で使用(16MHz/8)
     SPI.setDataMode(SPI_MODE0) ;         // クロック極性０(LOW)　クロック位相０
}
void loop() {
     int i ;
     int s = 10;
     int l = 4096-64;
     for (i=0 ; i < l ; i+=s) {
          digitalWrite(LDAC,HIGH) ;
          digitalWrite(SS,LOW) ;
          SPI.transfer((i >> 8)|0x30) ;     // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(i & 0xff) ;          // Lowバイトの出力
          digitalWrite(SS,HIGH) ;
          digitalWrite(LDAC,LOW) ;      // ラッチ信号を出す
     }

     for (i=l ; i > 0 ; i-=s) {
          digitalWrite(LDAC,HIGH) ;
          digitalWrite(SS,LOW) ;
          SPI.transfer((i >> 8)|0x30) ;     // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
          SPI.transfer(i & 0xff) ;          // Lowバイトの出力
          digitalWrite(SS,HIGH) ;
          digitalWrite(LDAC,LOW) ;      // ラッチ信号を出す
     }
}
