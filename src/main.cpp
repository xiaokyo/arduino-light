#include "wrapper_header.h"

// blinker key
char auth[] = "c1d3d29e7cc4";
// wifi 名称
char ssid[] = "9-1-10";
// wifi 密码
char pswd[] = "qw123123";

/**
 * 台灯
*/
int LIGHT = D2;

// 新建组件对象
BlinkerButton button_switch_light((char *)"switch-light");

// 按下按键即会执行该函数
void button_switch_light_handle(const String &state)
{
  BLINKER_LOG("get switch state: ", state);

  button_switch_light.print(state == BLINKER_CMD_ON ? "on" : "off");
  digitalWrite(LIGHT, !digitalRead(LIGHT));
}

/**
 * 初始化台灯blinker状态
*/
void read_button_switch_state() {
  button_switch_light.print(digitalRead(LIGHT) == 0 ? "off" : "on");
}

void setup()
{
  // 初始化串口
  Serial.begin(115200);

  // 初始化
  pinMode(LIGHT, OUTPUT);
  digitalWrite(LIGHT, LOW);

  read_button_switch_state();

  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  button_switch_light.attach(button_switch_light_handle);
}

void loop()
{
  Blinker.run();
}
