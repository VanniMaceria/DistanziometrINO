#include <LiquidCrystal.h>
const int triggerPin = 9; //pin che "spara" gli ultrasuoni
const int echoPin = 10; //pin che riceve gli ultrasuoni rimbalzati su un oggetto
float durata, distanza;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  //inizializzo lo schermo LCD
  lcd.begin(16, 2);
  lcd.print("Inizializzo...");
  delay(1000);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  captaDistanza();
  stampaInLCD(String(distanza));
  accendiSpegniLed();

}

void accendiSpegniLed(){
  if(distanza < 3.0){
    Serial.print("Sei troppo vicino\n");
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
}

void captaDistanza(){
   //prima settiamo il TRIGGER a BASSO per 2 microsecondi
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //poi ad ALTO così il TRIGGER "spara" le onde
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  //quando le onde sonore colpiscono il ricevitore, questo imposta il pin ECHO su ALTO per tutto il tempo in cui le onde hanno viaggiato
  durata = pulseIn(echoPin, HIGH); 
  distanza = (durata * .0343) / 2;  

  Serial.print("Distanza: ");  
	Serial.println(distanza);  
	delay(100);  
}

void stampaInLCD(String data){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distanza: ");
  lcd.setCursor(0, 1);  //imposta il cursore sulla seconda riga per il valore della distanza
  lcd.print(distanza, 1);
  lcd.print(" cm");
}
