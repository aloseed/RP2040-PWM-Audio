/* ル○ン三世風タイプライター U8g2ライブラリ使用 */
#include <Wire.h>
#include <U8g2lib.h>
#include "rp2040_pwm_audio.h"

#include "type_se.h"
#include "type_sound.h"

// ボードの定義
// Grove Shield for Pi PicoのI2C0ポート(SDA G8, SCL G9)を使用する場合は以下をコメントを外してください
//#define GROVE_SHIELD_FOR_PI_PICO

// RP2040-0.42LCD【01Space】は以下のコメントを外してください
//#define RP2040_0_42LCD

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

// Wire定義
#ifndef WIRE
#ifdef RP2040_0_42LCD
// RP2040-0.42LCD【01Space】のWire定義
#define WIRE Wire1
#define PIN_SDA 22
#define PIN_SCL 23
#else
#define WIRE Wire
// I2Cのピン定義
#ifdef GROVE_SHIELD_FOR_PI_PICO
// Grove Shield for Pi PicoのI2C0ポート
#define PIN_SDA 8
#define PIN_SCL 9
#elif defined(ARDUINO_CYTRON_MAKER_NANO_RP2040)
// Cytron Maker Nano RP2040(Qwiic互換ポート(PORT0)使用)
#define PIN_SDA 0
#define PIN_SCL 1
#endif
#endif
#endif

// OLED(SSD1306)定義
#ifdef RP2040_0_42LCD
#define SCREEN_WIDTH 70
#define SCREEN_HEIGHT 40
#define FONT u8g2_font_b10_t_japanese1
#define FONT_SIZE 10
U8G2_SSD1306_72X40_ER_F_2ND_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // EastRising 0.42" OLED
#else
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define FONT u8g2_font_b12_t_japanese1
#define FONT_SIZE 12
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
#endif

// タイプライター表示文字列
const char *str[] = {"あろしーど", "よろしく", "お願いします"};
const uint16_t strLen = sizeof(str) / sizeof(str[0]);

void setup()
{
  Serial.begin(115200);

  // PWM出力するピンを指定します。
  pwm_audio_init(PIN_BUZZER);
#ifdef PIN_SDA
  WIRE.setSDA(PIN_SDA);
#endif
#ifdef PIN_SCL
  WIRE.setSCL(PIN_SCL);
#endif
  u8g2.begin();
}

void loop()
{
  u8g2.setFont(u8g2_font_b16_t_japanese1);

  // 8KHz 8bit モノラルのrawデータをセットします。
  // 配列(タイプ音)と配列長
  set_sound(type_se, sizeof(type_se) / sizeof(type_se[0]));

  for (uint8_t i = 0; i < strLen; i++)
  {
    for (uint8_t j = 0; j < strlen(str[i]) / 3; j++)
    {
      u8g2.clearBuffer();
      const char c[4] = {*(str[i] + (j * 3)), *(str[i] + (j * 3 + 1)), *(str[i] + (j * 3 + 2)), '\0'};
      u8g2.drawUTF8(SCREEN_WIDTH / 2 - 8, SCREEN_HEIGHT / 2 + 8, c);
      u8g2.sendBuffer();

      // set_soundでセットしたデータ(タイプ音)をPWMで再生します。
      play_pwm_audio();
    }
  }

  // 文字列表示
  u8g2.clearBuffer();
  u8g2.setFont(FONT);
  for (uint8_t i = 0; i < strLen; i++)
  {
    u8g2.drawUTF8((SCREEN_WIDTH - (strlen(str[i]) / 3) * FONT_SIZE) / 2, (SCREEN_HEIGHT - (sizeof(str) / sizeof(str[0])) * FONT_SIZE) / 2 + FONT_SIZE * (i + 1), str[i]);
  }
  u8g2.sendBuffer();

  // 8KHz 8bit モノラルのrawデータをセットします。
  // 配列(サウンド)と配列長
  set_sound(type_sound, sizeof(type_sound) / sizeof(type_sound[0]));
  play_pwm_audio();

  delay(2000);
}