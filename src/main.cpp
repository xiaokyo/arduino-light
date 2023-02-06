#include "wrapper_header.h"

// blinker key
char auth[] = "c1d3d29e7cc4";
// wifi 名称
char ssid[] = "9-1-10";
// wifi 密码
char pswd[] = "qw123123";

// 新建组件对象
BlinkerButton Button_open_light((char *)"open-light");
BlinkerButton Button_close_light((char *)"close-light");

/**
 * 开灯
 */
void openLight()
{
  digitalWrite(D2, HIGH);
}

/**
 * 关灯
 */
void closeLight()
{
  digitalWrite(D2, LOW);
}

// 按下按键即会执行该函数
void button_open_light_handle(const String &state)
{
  BLINKER_LOG("get button state: ", state);
  openLight();
}

void button_close_light_handle(const String &state)
{
  BLINKER_LOG("get button state: ", state);
  closeLight();
}

void setup()
{
  // 初始化串口
  Serial.begin(115200);

  // 初始化
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);

  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  Button_open_light.attach(button_open_light_handle);
  Button_close_light.attach(button_close_light_handle);
}

void loop()
{
  Blinker.run();
}
