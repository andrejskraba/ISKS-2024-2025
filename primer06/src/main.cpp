#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "kibernetika";
const char* password = "norbert1948"; 

uint8_t LED1pin = 2; // 8 bit integer spremenljivka, kratka celoštevilska spremenljivka (0-255)
bool LED1status = LOW; // LED je lahko ugasnjena (LOW) ali prižgana (HIGH), boolean spremenljivka

// na portu 80, ki je prednastavljeni port, vzpostavimo spletni strežnik
WebServer server(80); // objekt server razreda WebServer, kot argument konstruktorske funkcije podamo vrednost 80

const char HTML0[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="sl">
<head>
    <meta charset="UTF-8">
    <style>
        html  {font-family: Helvetica; text-align: center;}
        body  {margin-top: 50px;}
        h1    {color: #444444; margin: 50px auto 30px;}
        h3    {color: #444444; margin-bottom: 50px;}
        .gumb {
        background-color: #3499db; /* določimo barvo ozadja (svetlo modra) */
        display: block; /* ustvarimo element blok - cela širina */
        width: 200px; /* širino nastavimo na 200px, da povezava ni čez celo stran */ 
        color: white; /* barva besedila je bela */
        padding: 13px 30px; /* dodamo oblazinjenje (top-bottom 13px, left-rigth 30px) */
        text-decoration: none; /* umaknemo podčrtanje povezave (uporabno, če povezavo oblikujemo kot gumb) */
        font-size: 25px; /* velikost besedila je 25px */
        margin: 0px auto 35px; /* gumb postavimo sredinsko in ddoamo 35px robu na spodnji strani */
        border-radius: 4px; /* rahlo zaoblimo vogale gumba */
        }
        p {font-size: 20px; color: #222222; margin-bottom: 10px;}
    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>esp32</title>
</head>
<body>
    <h1>esp32 spletni strežnik</h1>
    <h3>Priklop na WiFi usmerjevalnik</h3>
    <a class="gumb" href="/1">Prižgi LED</a>
    <a class="gumb" href="/0">Ugasni LED</a>
    <p>Prejet ukaz za izklop LED diode.</p>
</body>
</html>
)rawliteral";


const char HTML1[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="sl">
<head>
    <meta charset="UTF-8">
    <style>
        html  {font-family: Helvetica; text-align: center;}
        body  {margin-top: 50px;}
        h1    {color: #444444; margin: 50px auto 30px;}
        h3    {color: #444444; margin-bottom: 50px;}
        .gumb {
        background-color: #3499db; /* določimo barvo ozadja (svetlo modra) */
        display: block; /* ustvarimo element blok - cela širina */
        width: 200px; /* širino nastavimo na 200px, da povezava ni čez celo stran */ 
        color: white; /* barva besedila je bela */
        padding: 13px 30px; /* dodamo oblazinjenje (top-bottom 13px, left-rigth 30px) */
        text-decoration: none; /* umaknemo podčrtanje povezave (uporabno, če povezavo oblikujemo kot gumb) */
        font-size: 25px; /* velikost besedila je 25px */
        margin: 0px auto 35px; /* gumb postavimo sredinsko in ddoamo 35px robu na spodnji strani */
        border-radius: 4px; /* rahlo zaoblimo vogale gumba */
        }
        p {font-size: 20px; color: #222222; margin-bottom: 10px;}
    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>esp32</title>
</head>
<body>
    <h1>esp32 spletni strežnik</h1>
    <h3>Priklop na WiFi usmerjevalnik</h3>
    <a class="gumb" href="/1">Prižgi LED</a>
    <a class="gumb" href="/0">Ugasni LED</a>
    <p>Prejet ukaz za vklop LED diode.</p>
</body>
</html>
)rawliteral";  

const char HTML3[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="sl">
<head>
    <meta charset="UTF-8">
    <style>
        html  {font-family: Helvetica; text-align: center;}
        body  {margin-top: 50px;}
        h1    {color: #444444; margin: 50px auto 30px;}
        h3    {color: #444444; margin-bottom: 50px;}
        .gumb {
        background-color: #3499db; /* določimo barvo ozadja (svetlo modra) */
        display: block; /* ustvarimo element blok - cela širina */
        width: 200px; /* širino nastavimo na 200px, da povezava ni čez celo stran */ 
        color: white; /* barva besedila je bela */
        padding: 13px 30px; /* dodamo oblazinjenje (top-bottom 13px, left-rigth 30px) */
        text-decoration: none; /* umaknemo podčrtanje povezave (uporabno, če povezavo oblikujemo kot gumb) */
        font-size: 25px; /* velikost besedila je 25px */
        margin: 0px auto 35px; /* gumb postavimo sredinsko in ddoamo 35px robu na spodnji strani */
        border-radius: 4px; /* rahlo zaoblimo vogale gumba */
        }
        p {font-size: 20px; color: #222222; margin-bottom: 10px;}
    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>esp32</title>
</head>
<body>
    <h1>esp32 spletni strežnik</h1>
    <h3>Priklop na WiFi usmerjevalnik</h3>
    <a class="gumb" href="/1">Prižgi LED</a>
    <a class="gumb" href="/0">Ugasni LED</a>
    <p>http strežnik je zagnan.</p>
</body>
</html>
)rawliteral";

// določimo, kaj se dogodi, če uporabnik vnese
// korenski ("root") naslov našega spletnega strežnika na modulu esp32
//  t.j. http://192.168.1.170/ (zadnja poševnica označuje "root")
void handle_root(){ // če bo strežnik dobil zahtevo, t.j. "request"
  server.send(200, "text/html", HTML3); // bo vrnil odgovor ("response") spletno stran
  // katere vsebina je tokrat v spremenljivki z imenom HTML
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

  WiFi.begin(ssid, password); // poženemo WiFi

  while(WiFi.status() != WL_CONNECTED){ // dokler povezava z WiFi routerjem ni vzpostavljena
    delay(500);
    Serial.println("Povezovanje na WiFi omrežje v teku...");
  }

  Serial.println("Povezava z WiFi omrežjem je vzpostavljena.");
  Serial.print("IP naslov modula = ");
  Serial.println(WiFi.localIP()); // izpišemo IP številko modula

  server.on("/", handle_root); // tu povemo, kaj naj se dogodi, če kot zahtevo prejmemo poševnico "/"
  server.on("/1", handle_led1on); // če klient v Chrome zapiše /1, se bo sprožila funkcija handle_led1on
  server.on("/0", handle_led1off); // če klient v Chrome zapiše /0, se bo sprožila funkcija handle_led1off
  server.onNotFound(handle_NotFound); // v primeru, da spletne strani ni bilo moč najti sprožimo funkcijo rokovanja NotFound
  server.begin(); // poženemo spletni strežnik na našem modulu esp32
  Serial.println("HTTP strežnik je zagnan, vpišite IP naslov v brskalnik, npr. http://192.168.1.142/ http in ne https.");

  pinMode(LED1pin, OUTPUT); // pin 2 definiramo kot izhodi pin oz. nožico
  digitalWrite(LED1pin, HIGH);  // na nožico št. 2 zapišemo visoko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
  digitalWrite(LED1pin, LOW); // na nožico št. 2. zapišemo nizko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
  digitalWrite(LED1pin, HIGH);  // na nožico št. 2 zapišemo visoko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
  digitalWrite(LED1pin, LOW); // na nožico št. 2. zapišemo nizko vrednost
  delay(750); // zakasnitev v milisekundah [ms]
}

void loop() {
  // put your main code here, to run repeatedly:
  // tu zapišemo kodo, ki se ponavljajoče izvaja:
  server.handleClient(); // poslušamo zahteve ("request-e") klientov

  if(LED1status){
    digitalWrite(LED1pin, HIGH);
  }
  else{
    digitalWrite(LED1pin, LOW);
  }
}




