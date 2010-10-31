var mdgram=require("../mdgram");

var socket=mdgram.createSocket("udp4");
function send() {
	var msg = new Buffer(JSON.stringify(new Date()));
	socket.send(msg,0,msg.length,1811,"225.0.0.73");
};
setInterval(send,1000);
