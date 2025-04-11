let http = require('http');
http.createServer(function(req, res){
res.writeHead(200, {'Content-Type': 'text/plain'});
res.end('Pozdravljen svet!\n');
}).listen(8080);
console.log('start');