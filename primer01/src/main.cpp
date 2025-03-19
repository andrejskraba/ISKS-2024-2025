#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  // tu zapišemo kodo, ki se izvede le enkrat, ob zagonu, to so nastavitve
  pinMode(2, OUTPUT); // pin 2 definiramo kot izhodi pin oz. nožico
}

void loop() {
  // put your main code here, to run repeatedly:
  // tu zapišemo kodo, ki se ponavljajoče izvaja:
  digitalWrite(2, HIGH);  // na nožico št. 2 zapišemo visoko vrednost
  delay(250); // zakasnitev v milisekundah [ms]
  digitalWrite(2, LOW); // na nožico št. 2. zapišemo nizko vrednost
  delay(250); // zakasnitev v milisekundah [ms]
}