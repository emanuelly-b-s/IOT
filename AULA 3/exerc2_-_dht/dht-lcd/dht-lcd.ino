#include <LiquidCrystal.h>
LiquidCrystal lcd(19,23,18,17,16,15);

#include "dht.h"
const int pino=22 ;
dht DHT;

void setup() {
  DHT.read11(pino);
  lcd.begin(16,2);
}
void loop() {
  DHT.read11(pino);
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.print("Umidade: ");
  Serial.println(DHT.humidity);
  lcd.setCursor(0,1);
  lcd.print("Temperatura:");
  lcd.print(DHT.temperature, 0);
  delay(1000);
}  
