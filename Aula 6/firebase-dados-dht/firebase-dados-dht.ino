#include "dht.h"
const int pinoDht = 22;
dht DHT;

#include "WiFi.h" 
#include "FirebaseESP32.h"
                                               
#define WIFI_SSID "Vivo-Internet-BF17"
#define WIFI_PASSWORD "78814222"


#define FIREBASE_HOST "https://teste-esp-temp-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "CHrXmBPnAFIAZfwBcSLVszBYSv2QMBgmwTL23jQu"

FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.begin(9600);

    while(WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    Firebase.setReadTimeout(firebaseData, 1000 * 60);
    Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    
    Firebase.reconnectWiFi(true);
    Firebase.setReadTimeout(firebaseData, 1000 * 60);
    Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop() {
  DHT.read11(pinoDht);

  json.set("/temperatura", DHT.temperature);
  json.set("/umidade", DHT.humidity);
  Firebase.updateNode(firebaseData, "/<Emanuelly>/Sensor", json);
}
