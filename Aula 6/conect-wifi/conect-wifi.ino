#include <WiFi.h>                                                 
#define WIFI_SSID "Vivo-Internet-BF17"
#define WIFI_PASSWORD "78814222"


void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
