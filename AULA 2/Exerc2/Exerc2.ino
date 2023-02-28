int led1 = 18;
int led2 = 19;
int led3 = 21;

void setup() {
  // Definir os pinos como saída
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  // Acender LED1
  digitalWrite(led1, HIGH);
  delay(500); // Esperar 0,5 segundos
  digitalWrite(led1, LOW); // Apagar LED1

  // Acender LED2
  digitalWrite(led2, HIGH);
  delay(500); // Esperar 0,5 segundos
  digitalWrite(led2, LOW); // Apagar LED2

  // Acender LED3
  digitalWrite(led3, HIGH);
  delay(500); // Esperar 0,5 segundos
  digitalWrite(led3, LOW); // Apagar LED3
}
