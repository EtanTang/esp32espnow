#include <Arduino.h>
#include <Ticker.h>
#include "WiFi.h"


Ticker ticker;// 建立Ticker用于实现定时功能
uint32_t tickerCount = 0;


extern void OTA_setup(void);


void tickerCallback(void)
{
  // Serial.println("tickerCallback");
  tickerCount++;
}

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
  
  ticker.attach_ms(10, tickerCallback);
  // Serial.println("Hello ota!");
  // OTA_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t lastTime = 0;

  if (lastTime != tickerCount && tickerCount % 1000 == 0)
  {
    /* code */
    lastTime = tickerCount;

    Serial.println(WiFi.macAddress());
    Serial.println(tickerCount);
    // Serial.println("Hello ota!");
  }
  else
  {
    /* code */
  }
  
}
