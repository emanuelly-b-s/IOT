int bttPin = 23;

void setup() {
  Serial.begin(9600);
  pinMode(bttPin, INPUT);
}

void loop() {
  if(bttPin = HIGH){
      Serial.write('H');
    }
    else{
       Serial.write('L');
    }
}
