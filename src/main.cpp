#include "wrapper_header.h"

// blinker key
char auth[] = "c1d3d29e7cc4";
// wifi 名称
char ssid[] = "9-1-10";
// wifi 密码
char pswd[] = "qw123123";

int LIGHT = D2;

// 新建组件对象
BlinkerButton button_switch_light((char *)"open-light");

// 按下按键即会执行该函数
void button_switch_light_handle(const String &state)
{
  digitalWrite(LIGHT, !digitalRead(LIGHT));
}

void setup()
{
  // 初始化串口
  Serial.begin(115200);

  // 初始化
  pinMode(LIGHT, OUTPUT);
  digitalWrite(LIGHT, LOW);

  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  button_switch_light.attach(button_switch_light_handle);
}

void loop()
{
  Blinker.run();
}
