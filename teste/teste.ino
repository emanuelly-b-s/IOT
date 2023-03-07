#include <LiquidCrystal.h>
LiquidCrystal lcd(19,23,18,17,16,15);

#include "dht.h"
const int pinoDHT = 22 ;
dht DHT;

#include "WiFi.h" 
#include "FirebaseESP32.h"
                                               
#define WIFI_SSID "Iphone de Emanuelly"
#define WIFI_PASSWORD "manuzika"


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
  lcd.begin(16,2);
}
void loop() {
  DHT.read11(pinoDHT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("Umidade: ");
  lcd.print(DHT.humidity);
  lcd.setCursor(0,1);
  lcd.print("Temperatura:");
  lcd.print(DHT.temperature, 0);
  json.set("/temperatura", DHT.temperature);
  json.set("/umidade", DHT.humidity);
  Firebase.updateNode(firebaseData, "/<Emanuelly>/Sensor", json);
  delay(2000);
}  
