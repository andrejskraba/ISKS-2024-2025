import * as http from "http";
import express from "express";
import ip from "ip";
import path from "path";
import {join, dirname} from "path";
import { fileURLToPath } from "url";
const __dirname = dirname(fileURLToPath(import.meta.url));

const app = express();

const hostname = "192.168.2.101";
const port = 80;

const server = http.createServer(app).listen(80); // express strežnik

app.get("/",  function(req, res){
    res.sendFile(path.join(__dirname + "/test04.html"));
});

console.log(`Strežnik teče na http://${hostname}:${port}`);
console.log("IP=" + ip.address());