#include <dht.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(19,23,18,17,16,15);
const int pinoDht = 22;
int valPot = 0;

dht DHT;
                                               
#define WIFI_SSID "Vivo-Internet-BF17"
#define WIFI_PASSWORD "78814222"


#define FIREBASE_HOST "https://teste-esp-temp-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "CHrXmBPnAFIAZfwBcSLVszBYSv2QMBgmwTL23jQu"

FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  
 
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
  valPot = analogRead(pinoDht);
  
  DHT.read11(pinoDht);

  json.set("/temperatura", DHT.temperature);
  json.set("/umidade", DHT.humidity);
  Firebase.updateNode(firebaseData, "/<Emanuelly>/Sensor", json);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade: ");
  lcd.print(DHT.humidity);
  lcd.setCursor(0,1);
  lcd.print("Temperatura:");
  lcd.print(DHT.temperature, 0);
  delay(1000);
}
