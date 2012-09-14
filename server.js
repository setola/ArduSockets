var ws = require("websocket-server");

var server = ws.createServer();

server.addListener("connection", function(connection){
	console.log("ASD");
	connection.addListener("message", function(msg){
		console.log(connection);
		connection.send(msg);
		
		
	});
	setTimeout(function() {
		console.log("BROAD");
		server.broadcast("Everyone welcome" +connection.id);
	}, 1500)
});
server.listen(80);
/*
var WebSocketServer = require('websocket').server;
var http = require('http');

var server = http.createServer(function(request, response) {
    console.log((new Date()) + ' Received request for ' + request.url);
    response.writeHead(404);
    response.end();
});
server.listen(80, function() {
    console.log((new Date()) + ' Server is listening on port 80');
});

wsServer = new WebSocketServer({
    httpServer: server,
    // You should not use autoAcceptConnections for production
    // applications, as it defeats all standard cross-origin protection
    // facilities built into the protocol and the browser.  You should
    // *always* verify the connection's origin and decide whether or not
    // to accept it.
    autoAcceptConnections: false
});

wsServer.on('connection', function(connection) {
	console.log("ASD");
});

wsServer.on('request', function(request) {

    var connection = request.accept(null, request.origin);
    console.log((new Date()) + ' Connection accepted.');
    connection.on('message', function(message) {
        if (message.type === 'utf8') {
            console.log('['+request.remoteAddress +'] Received Message: ' + message.utf8Data);
            connection.sendUTF(message.utf8Data);
        }
        else if (message.type === 'binary') {
            console.log('['+request.remoteAddress +'] Received Binary Message of ' + message.binaryData.length + ' bytes');
            connection.sendBytes(message.binaryData);
        }
    });
    connection.on('close', function(reasonCode, description) {
        console.log((new Date()) + ' Peer ' + connection.remoteAddress + ' disconnected.');
    });
});
 */