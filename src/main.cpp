#include "wrapper_header.h"

// blinker key
char auth[] = "c1d3d29e7cc4";
// wifi 名称
char ssid[] = "9-1-10"; // "9-1-10";
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
  digitalWrite(LIGHT, !digitalRead(LIGHT));
  Serial.print("当前灯状态:");
  Serial.println(digitalRead(LIGHT));
}

// 小爱同学配置
void miotPowerState(const String &state)
{
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

/**
 * 心跳返回状态
 */
void blinker_heartbeat()
{
  button_switch_light.print(digitalRead(LIGHT) == 1 ? "on" : "off");
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
  Blinker.attachHeartbeat(blinker_heartbeat);
}

void loop()
{
  Blinker.run();
  Blinker.delay(2);
}
