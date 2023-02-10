#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

void handleRoot()
{
    server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();

    for (int i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void server_setup()
{

    if (MDNS.begin("esp8266"))
    {
        Serial.println("MDNS responder started");
    }

    server.begin();
    Serial.println("HTTP server started");
}

void server_init_router()
{
    // init router
    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);
}

void server_loop()
{
    server.handleClient();
}