#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiAP.h>

const char* ssid = "esp32_1";
const char* password = "12345678";

IPAddress local_IP(192, 168, 50, 1); // določimo IP naslov eps32 modula, ki deluje kot Access Point
IPAddress gateway(192, 168, 50, 1);
IPAddress subnet (255, 255, 255, 0);

uint8_t LED1pin = 2; // 8 bit integer spremenljivka, kratka celoštevilska spremenljivka (0-255)
bool LED1status = LOW; // LED je lahko ugasnjena (LOW) ali prižgana (HIGH), boolean spremenljivka

const char HTML0[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html lang="sl">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>esp32</title>
  </head>
  <body>
      <h1>Ukaz za izklop LED diode prejet.</h1>
  </body>
  </html>
  )rawliteral";


  const char HTML1[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html lang="sl">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>esp32</title>
    </head>
    <body>
        <h1>Ukaz za vklop LED diode prejet.</h1>
    </body>
    </html>
    )rawliteral";  

const char HTML3[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="sl">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>esp32</title>
</head>
<body>
    <h1>HTTP strežnik zagnan. V brskalnik vpišite http://192.168.50.1/1 ali http://192.168.50.1/0 t.j. /1 ali /0 na koncu.</h1>
</body>
</html>
)rawliteral";

// na portu 80, ki je prednastavljeni port, vzpostavimo spletni strežnik
WebServer server(80); // objekt server razreda WebServer, kot argument konstruktorske funkcije podamo vrednost 80

// določimo, kaj se dogodi, če uporabnik vnese
// korenski ("root") naslov našega spletnega strežnika na modulu esp32
//  t.j. http://192.168.1.142/ (zadnja poševnica označuje "root")
void handle_root(){ // če bo strežnik dobil zahtevo, t.j. "request"
  server.send(200, "text/html", HTML3); // bo vrnil odgovor ("response") "esp32 kot Access Point AP ..."
  // 200 predstavlja kodo za OK oz. vse je v redu
  // kot odgovor vrnemo niz oz. "String" "Pozdravljen svet iz esp32!"
}

void handle_led1on(){
  LED1status = HIGH;
  Serial.println("GPIO2 Status: ON"); // General Purpose Input Output
  server.send(200, "text/html", HTML1); // kot odgovor posredujemo spletno stran, ki je v spremenljivki char [] HTML1
}

void handle_led1off(){
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", HTML0); // kot odgovor posredujemo spletno stran, ki je v spremenljivki HTML0
}

void handle_NotFound(){ // v primeru, da spletne strani ni bilo moč najti na strežniku
  server.send(404, "text/html; charset=utf-8", "Spletne strani ni bilo moč najti na esp32 spletnem strežniku."); // uporabnika obvestimo, da spletne strani nismo uspeli najti na strežniku
}

void setup() {
  // put your setup code here, to run once:
  // tu zapišemo kodo, ki se izvede le enkrat, ob zagonu, to so nastavitve

  Serial.begin(115200); // komunikacija preko serijskega protokola s hitrostjo 115200 bitov/s

  if(!WiFi.softAPConfig(local_IP, gateway, subnet)){
    Serial.println("Neuspešna določitev AP IP!");
  }

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
  server.on("/1", handle_led1on); // če klient v Chrome zapiše /1, se bo sprožila funkcija handle_led1on
  server.on("/0", handle_led1off); // če klient v Chrome zapiše /0, se bo sprožila funkcija handle_led1off
  server.onNotFound(handle_NotFound); // v primeru, da spletne strani ni bilo moč najti sprožimo funkcijo rokovanja NotFound
  server.begin(); // poženemo spletni strežnik na našem modulu esp32
  Serial.println("HTTP strežnik je zagnan, vpišite IP naslov v brskalnik, npr. http://" + WiFi.softAPIP().toString() + "/ http in ne https.");

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

  if(LED1status){ // preverjanje statusa; status se spremeni glede na zahtevo /0 ali /1
    digitalWrite(LED1pin, HIGH); // če je status TRUE, kar pomeni, da smo prejeli zahtevo /1, dig. pin postavimo na HIHG
  }
  else{
    digitalWrite(LED1pin, LOW); // sicer, če smo prejeli zahtevo /0 je status FALSE in digitalni pin postavimo na LOW
  }  

}




