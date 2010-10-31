var mdgram=require("../mdgram");

var socket=mdgram.createSocket("udp4");
socket.on("message",function(data, remote) { console.log("MSG: "+data); });
socket.on("listening",function() { this.joinGroup("225.0.0.73"); });
socket.bind(1811);
