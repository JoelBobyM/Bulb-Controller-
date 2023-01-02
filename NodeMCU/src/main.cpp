#include <ESP8266WiFi.h>

const char* ssid = "Galaxy M31";
const char* password = "rinf8002";

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);

  pinMode(2, OUTPUT); //2 - DEFAULT PIN FOR INBULIT LED 
  pinMode(16, OUTPUT); //16 - D0 PORT IN NODE MCU (IN TO RELAY MODULE)

  WiFi.begin(ssid, password);
  Serial.print("CONNECTING..");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  server.begin();
  Serial.print("IP ADDRESS : ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  digitalWrite(2, HIGH);
  digitalWrite(16, HIGH);
}

void loop()
{

  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  while (!client.available())
  {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.print(client.remoteIP());
  Serial.print(" : ");
  Serial.println(request);
  client.flush();
  int value = HIGH;
  if (request.indexOf("GET /?LED=ON HTTP/1.1") == 0)
  {
    value = LOW;
  }upload_port = /dev/ttyUSB0
monitor_speed = 115200
  else if (request.indexOf("GET /?LED=OFF HTTP/1.1") == 0)
  {
    value = HIGH;
  }
  digitalWrite(2, value);
  digitalWrite(16, value);
  Serial.println("");
}