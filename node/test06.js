import * as http from "http";
import express from "express";
import ip from "ip";
import path from "path";
import {join, dirname} from "path";
import { fileURLToPath } from "url";
const __dirname = dirname(fileURLToPath(import.meta.url));

import { WebSocketServer } from "ws"; // za permanentno povezavo med strežnikom in klientom

const app = express();

const hostname = "192.168.2.101";
const port = 80;

const server = http.createServer(app).listen(80); // express strežnik

const wss1 = new WebSocketServer({port: 8888}); // Chrome - brskalnik - vrata oz. port 8888 so namenjena prenosu sporočil med brskalnikom (Chrome) in strežnikom node.js

app.get("/",  function(req, res){
    res.sendFile(path.join(__dirname + "/test06.html"));
});

// ***********************************************************
// Brskalnik Chrome na wss1, vrata 8888
// ***********************************************************
wss1.on("connection", function(ws, req){
    console.log("Klient = brskalnik Chrome se je povezzal!");
    ws.on("message", function(msgString){
        console.log("Sporočilo prejeto, vsebina: " + msgString);
    })
}); // konec wss1.on("connection"...)

console.log(`Strežnik teče na http://${hostname}:${port}`);
console.log("IP=" + ip.address());