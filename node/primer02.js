import http from "http";
import fs from "fs"; // uvozimo "file system - fs"
import { fileURLToPath } from "url";
import { dirname, join } from "path";

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename); // dvojni podčrtaj je uporabljen po dogovoru, da ločimo filename = "abc.txt" - uporabnik __filename - od node.js "code convention"
// želimo imeti definirano ime datoteke s polno potjo

const hostname = "192.168.2.101";
const port = 80;

const server = http.createServer((req, res) => {
    // funkcija readFile sprejme ime datoteke (skupaj s potjo)
    // npr. /home/andrejskraba/node/primer02.html
    // če je vse v redu funkcija vrne podatke v spremenljivki data (v tej spr. je vsebina html strani)
    // če gre za napako pri branju, npr. datoteke ni na disku
    // vrne err - error
    fs.readFile(join(__dirname, "primer02.html"), (err, data) => {
        if(err){
            res.writeHead(500, {"Content-Type": "text/plain; charset=utf-8"});
            return res.end("Napaka pri nalaganju html strani. Branje datoteke primer02.html iz diska ni bilo uspešno.");
        }
        res.writeHead(200); // koda OK
        res.end(data);
    });
});

server.listen(port, hostname, () => {
    // v oklepaju zapišemo narekovaje z Alt+Gr + 7
    // da dobimo izpis IP naslova in vrat
    console.log(`Strežnik teče na http://${hostname}:${port}`);
    console.log(join(__dirname, "primer02.html"));
});