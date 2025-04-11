import http from "http";

const hostname = "192.168.2.101";
const port = 80;

const server = http.createServer((req, res) => {
    res.statusCode = 200; // vse je OK
    res.setHeader("Content-Type", "text/plain");
    res.end("Pozdravljen svet VSC v aprilu!");
});

server.listen(port, hostname, () => {
    // v oklepaju zapišemo narekovaje z Alt+Gr + 7
    // da dobimo izpis IP naslova in vrat
    console.log(`Strežnik teče na http://${hostname}:${port}`);
});