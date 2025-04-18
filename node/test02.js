import * as http from "http";
import express from "express";

const app = express();

const hostname = "192.168.2.101";
const port = 80;

const server = http.createServer(app).listen(80); // express strežnik

app.get("/",  function(req, res){
    res.send("Pozdravljen Express svet!");
});

console.log(`Strežnik teče na http://${hostname}:${port}`);