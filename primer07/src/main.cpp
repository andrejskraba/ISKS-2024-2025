#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiAP.h>

const char* ssid = "esp32_1";
const char* password = "12345678"; 

// na portu 80, ki je prednastavljeni port, vzpostavimo spletni strežnik
WebServer server(80); // objekt server razreda WebServer, kot argument konstruktorske funkcije podamo vrednost 80

// določimo, kaj se dogodi, če uporabnik vnese
// korenski ("root") naslov našega spletnega strežnika na modulu esp32
//  t.j. http://192.168.1.142/ (zadnja poševnica označuje "root")
void handle_root(){ // če bo strežnik dobil zahtevo, t.j. "request"
  server.send(200, "text/html", "esp32 kot Access Point AP"); // bo vrnil odgovor ("response") "esp32 kot Access Point AP ..."
  // 200 predstavlja kodo za OK oz. vse je v redu
  // kot odgovor vrnemo niz oz. "String" "Pozdravljen svet iz esp32!"
}


void setup() {
  // put your setup code here, to run once:
  // tu zapišemo kodo, ki se izvede le enkrat, ob zagonu, to so nastavitve

  Serial.begin(115200); // komunikacija preko serijskega protokola s hitrostjo 115200 bitov/s

  // Vzpostavitev programske dostopne točke - "Soft Access Point AP"
  // "software enabled access point" npr. računalniki, ki ni bil zasnovan kot dostopna točka
  // postane z ustreznim programjem dostopna točka
  // esp32 se spremeni v dostopno točko
  WiFi.softAP(ssid, password); // poženemo esp32 kot dostopno točko (Acces Point AP)

  // izpišemo IP naslov
  Serial.println("Vzpostavitev programske dostopne točke na esp32");
  Serial.print("IP naslov esp32 dostopne točke = ");
  Serial.println(WiFi.softAPIP()); // prednastavljeni IP naslov je: 192.168.4.1

  server.on("/", handle_root); // tu povemo, kaj naj se dogodi, če kot zahtevo prejmemo poševnico "/"
  server.begin(); // poženemo spletni strežnik na našem modulu esp32
  Serial.println("HTTP strežnik je zagnan, vpišite IP naslov v brskalnik, npr. http://192.168.4.1/ http in ne https.");

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
  server.handleClient(); // poslušamo zahteve ("request-e") klientov
}




