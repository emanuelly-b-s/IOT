#define potPin 36
int valPot=0;

void setup() {
  Serial.begin(9600);
}
void loop() {
  valPot=analogRead(potPin);
  Serial.print("Valor original: ");
  Serial.println(valPot);
  delay(1000); //Espera um tempo para continuar o Loop
}
