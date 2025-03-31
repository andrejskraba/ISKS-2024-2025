#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "kibernetika";
const char* password = "norbert1948"; 

// na portu 80, ki je prednastavljeni port, vzpostavimo spletni strežnik
WebServer server(80); // objekt server razreda WebServer, kot argument konstruktorske funkcije podamo vrednost 80

// na vratih 81 ustvarimo strežnik spletnih vtičnikov - WebSocketsServer
WebSocketsServer webSocket = WebSocketsServer(81);

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="sl">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WebSocket</title>
</head>
<body>
<h2>Primer s spletnim vtičnikom WebSocket</h2>
<button onclick="pošljiSporočilo()">pošljiSporočilo</button>
<script>
let povezava = new WebSocket("ws://192.168.1.170:81/"); // vzpostavitev povezave preko spletnega vtičnika
function pošljiSporočilo(){
    povezava.send("abcčdefghi"); // na strežnik (esp32) pošljemo sporočilo
}
</script>
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

// *****************************************************************************************
// Definicija funkcije onWebSocketEvent, ki se izvede kadarkoli dobimo sporočilo preko
// spletnega vtičnika - preko WebSocket-a (na vtičniku se dogodi dogodek - "event")
// *****************************************************************************************
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  // določimo funkcionalnost glede na tip dogodka na spletnem vtičniku (WebSocket-u)
  switch (type)
  {
  case WStype_DISCONNECTED:
    {
      Serial.printf("[%u] Klient odklopljen!\n", num);
    }
    break;

  case WStype_CONNECTED:
    {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Vzpostavljena WebSocket povezava iz IP naslova!\n", num);
      Serial.println(ip.toString());
    }
    break;    
  
  case WStype_TEXT:
    {
      Serial.printf("[%u] Besedilo sporočila: %s\n", num, payload); // izpis vsebine sporočila v serijski monitor
    }

  default:
    break;
  } // KONEC switch stavka
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
  Serial.println("HTTP strežnik je zagnan, vpišite IP naslov v brskalnik, npr. http://192.168.1.170/ http in ne https.");

  // poženemo WebSocket strežnik in določimo "callback"
  webSocket.begin(); // zagon WebSocket strežnika
  webSocket.onEvent(onWebSocketEvent); // kadarkoli se bo dogoil določen dogodek preko spletnega vtičnika
                                       // WebSocket bomo izvedli funkcijo onWebSocketEvent, ki smo jo def. zgoraj

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

  webSocket.loop(); // poslušamo na spletnem vtičnikku - WebSocket za podatke in dogodke
}




