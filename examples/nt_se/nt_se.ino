#include "rp2040_pwm_audio.h"
#include "nt_se.h"

// PWMオーディオ出力ピン(デフォルト A3)
#ifndef PIN_BUZZER
#define PIN_BUZZER A3
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