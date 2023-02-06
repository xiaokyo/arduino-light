#include "wrapper_header.h"

// blinker key
char auth[] = "c1d3d29e7cc4";
// wifi 名称
char ssid[] = "9-1-10";
// wifi 密码
char pswd[] = "qw123123";

// 新建组件对象
BlinkerButton Button1((char *)"btn-abc");
BlinkerButton Button2((char *)"btn-cba");

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
void button1_callback(const String &state)
{
  BLINKER_LOG("get button state: ", state);
  openLight();
}

void button2_callback(const String &state)
{
  BLINKER_LOG("get button state: ", state);
  closeLight();
}

void setup()
{
  // 初始化串口
  Serial.begin(115200);

  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);

  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  Button1.attach(button1_callback);
  Button2.attach(button2_callback);
}

void loop()
{
  Blinker.run();
}
