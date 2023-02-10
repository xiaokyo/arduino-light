#include "wrapper_header.h"
#include "server.h"

// blinker key
const char auth[] = "c1d3d29e7cc4";
// wifi 名称
const char ssid[] = "9-1-10";
// wifi 密码
const char pswd[] = "qw123123";

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

// 小爱同学配置
void miotPowerState(const String &state)
{
  BLINKER_LOG("need set power state: ", state);

  if (state == BLINKER_CMD_ON)
  {
    digitalWrite(LIGHT, HIGH);

    BlinkerMIOT.powerState("on");
    BlinkerMIOT.print();
  }
  else if (state == BLINKER_CMD_OFF)
  {
    digitalWrite(LIGHT, LOW);

    BlinkerMIOT.powerState("off");
    BlinkerMIOT.print();
  }
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
  BlinkerMIOT.attachPowerState(miotPowerState);

  server_start();
}

void loop()
{
  button_switch_light.print(digitalRead(LIGHT) == 1 ? "on" : "off");
  server_loop();
  Blinker.run();
}
