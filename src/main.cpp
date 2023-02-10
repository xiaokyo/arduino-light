#include "wrapper_header.h"

// blinker 设备 key
const char auth[] = "c1d3d29e7cc4";
// wifi 名称
const char ssid[] = "9-1-10";
// wifi 密码
const char pswd[] = "qw123123";

const char *AP_ssid = "esp8266-wifi";
const char *AP_password = "Zwj.19961118";

ESP8266WebServer server(80);

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

// server handle root
void handleRoot()
{
  server.send(200, "text/plain", "hello from esp8266!");
}

// server handle notfound
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
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

  // 热点wifi
  WiFi.begin();
  Serial.println();
  Serial.print("Setting soft-AP ... ");

  IPAddress softLocal(192, 168, 1, 1);   // 这里最好不改，否则不能DHCP
  IPAddress softGateway(192, 168, 1, 1); // 和这里，修改创建热点的接入IP
  IPAddress softSubnet(255, 255, 255, 0);
  WiFi.softAPConfig(softLocal, softGateway, softSubnet);
  WiFi.softAP(AP_ssid, AP_password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []()
            { server.send(200, "text/plain", "this works as well"); });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  // button_switch_light.print(digitalRead(LIGHT) == 1 ? "on" : "off");
  Blinker.run();
  server.handleClient();
}
