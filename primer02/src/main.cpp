#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "kresilnik";
const char* password = "bled2024"; 

void setup() {
  // put your setup code here, to run once:
  // tu zapišemo kodo, ki se izvede le enkrat, ob zagonu, to so nastavitve

  Serial.begin(115200); // komunikacija preko serijskega protokola s hitrostjo 115200 bitov/s

  WiFi.begin(ssid, password); // poženemo WiFi

  while(WiFi.status() != WL_CONNECTED){ // dokler povezava z WiFi routerjem ni vzpostavljena
    delay(500);
    Serial.println("Povezovanje na WiFi omrežje v teku...");
  }

  Serial.println("Povezava z WiFi omrežjem je vzpostavljena.");
  Serial.print("IP naslov modula = ");
  Serial.println(WiFi.localIP()); // izpišemo IP številko modula

  pinMode(2, OUTPUT); // pin 2 definiramo kot izhodi pin oz. nožico
  digitalWrite(2, HIGH);  // na nožico št. 2 zapišemo visoko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
  digitalWrite(2, LOW); // na nožico št. 2. zapišemo nizko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
  digitalWrite(2, HIGH);  // na nožico št. 2 zapišemo visoko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
  digitalWrite(2, LOW); // na nožico št. 2. zapišemo nizko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
}

void loop() {
  // put your main code here, to run repeatedly:
  // tu zapišemo kodo, ki se ponavljajoče izvaja:
}