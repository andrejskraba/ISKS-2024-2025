#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "kibernetika";
const char* password = "norbert1948"; 

// na portu 80, ki je prednastavljeni port, vzpostavimo spletni strežnik
WebServer server(80); // objekt server razreda WebServer, kot argument konstruktorske funkcije podamo vrednost 80

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="sl">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>esp32</title>
</head>
<body>
    <h1>Pozdravljen svet iz modula esp32! Tokrat modul vrne spletno stran.</h1>
</body>
</html>
)rawliteral";

// določimo, kaj se dogodi, če uporabnik vnese
// korenski ("root") naslov našega spletnega strežnika na modulu esp32
//  t.j. http://192.168.1.142/ (zadnja poševnica označuje "root")
void handle_root(){ // če bo strežnik dobil zahtevo, t.j. "request"
  server.send(200, "text/html", HTML); // bo vrnil odgovor ("response") spletno stran
  // katere vsebina je tokrat v spremenljivki z imenom HTML
  // 200 predstavlja kodo za OK oz. vse je v redu
  // kot odgovor vrnemo niz oz. "String" "Pozdravljen svet iz esp32!"
}


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

  server.on("/", handle_root); // tu povemo, kaj naj se dogodi, če kot zahtevo prejmemo poševnico "/"
  server.begin(); // poženemo spletni strežnik na našem modulu esp32
  Serial.println("HTTP strežnik je zagnan, vpišite IP naslov v brskalnik, npr. http://192.168.1.142/ http in ne https.");

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




