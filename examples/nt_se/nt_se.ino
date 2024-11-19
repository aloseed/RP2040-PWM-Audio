/* ニ○ータイプ風効果音 */
#include "rp2040_pwm_audio.h"
#include "nt_se.h"

// PWMオーディオの出力先を定義
// デフォルト定義
// Raspberry Pi Pico A2(G28)
// Seeed XIAO RP2350 D3
// 上記以外はA3
// 任意のピンを定義するには以下のコメントを外しオーディオ出力先GPIO番号を指定してください
//#define PIN_BUZZER A0
#ifndef PIN_BUZZER
#ifdef ARDUINO_RASPBERRY_PI_PICO
#define PIN_BUZZER A2
#elif ARDUINO_SEEED_XIAO_RP2350
#define PIN_BUZZER D3
#else
#define PIN_BUZZER A3
#endif
#endif

// 再生間隔(ms)
#define PLAY_INTERVAL 3000

void setup()
{
  // PWMオーディオ初期化(引数に出力ピンを指定)
  pwm_audio_init(PIN_BUZZER);
  // データ(rawデータ配列)をセット
  set_sound(nt_se, sizeof(nt_se) / sizeof(nt_se[0]));
}

void loop()
{
  play_pwm_audio();
  delay(PLAY_INTERVAL);
}