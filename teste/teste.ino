#include <LiquidCrystal.h>
LiquidCrystal lcd(19,23,18,17,16,15);

#define led1 = 21
#define led2 = 1
#define led3 = 3

#include "dht.h"
const int pinoDHT = 22 ;
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
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);
   DHT.read11(pinoDHT);
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
  if (DHT.temperature <= 25) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);

    }
  /*else if (t > 25 & t < 27) {
      digitalWrite(pinos[1], HIGH);
    }
  else if (t <= 27) {
      digitalWrite(pinos[1], LOW);
      digitalWrite(pinos[2], HIGH);*/
  }
  json.set("/temperatura", DHT.temperature);
  json.set("/umidade", DHT.humidity);
  Firebase.updateNode(firebaseData, "/<Emanuelly>/Sensor", json);
  delay(2000);
}  
