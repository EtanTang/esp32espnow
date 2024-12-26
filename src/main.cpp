#include <Arduino.h>
#include <Ticker.h>
#include "WiFi.h"
#include <BleGamepad.h>


Ticker ticker; // 建立Ticker用于实现定时功能
uint32_t tickerCount = 0;

BleGamepad bleGamepad;
BleGamepadConfiguration bleGamepadConfig;

extern void OTA_setup(void);
extern void IMU_setup(void);
extern void PLN_setup(void);

extern void IMU_loop(void);
extern void PLN_loop(void);

void tickerCallback(void)
{
  // Serial.println("tickerCallback");
  tickerCount++;
}

void setup()
{
  Serial.begin(115200);
  ticker.attach_ms(10, tickerCallback);
  PLN_setup();

  // IMU_setup();
  // OTA_setup();

}

void loop()
{
  // put your main code here, to run repeatedly:
  static uint32_t lastTime = 0;

  if (lastTime != tickerCount) // 每10ms执行一次
  {
    /* code */
    lastTime = tickerCount;

    PLN_loop();

    // IMU_loop();

    // if (tickerCount % 100 == 0) // 每1000ms执行一次
    // {
    //   /* code */
    //   Serial.println(WiFi.macAddress());
    //   Serial.println(tickerCount);

    // }
    // else
    // {
    //   /* code */
    // }
  }
  else
  {
    /* code */
  }

}
