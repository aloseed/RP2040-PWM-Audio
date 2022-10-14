# RP2040 PWM Audio

raw(8kHz 8bit モノラル)データをRP2040のPWMで再生するライブラリです。

## 対応環境
[RP2040 with Arduino-Pico](https://github.com/earlephilhower/arduino-pico)

## 使い方 How to use

[examples](./examples)にサンプルがあります。

- [nt_se](./examples/nt_se)

  ニ○ータイプ風効果音

- [typewriter](./examples/typewriter)

  ル○ン3世風タイプライター(U8g2ライブラリが必要です)

### 基本的な使い方
```
// PWM出力するピンを指定します。
void pwm_audio_init(uint);

// 8KHz 8bit モノラルのrawデータをセットします。
// 配列(rawデータ)と配列長
void set_sound(uint8_t *s, uint32_t len);

// set_soundでセットしたデータをPWMで再生します。
void play_pwm_audio();
```

### ブログ
https://aloseed.com