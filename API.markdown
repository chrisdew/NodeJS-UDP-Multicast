NodeJS UDP-Multicast - API
==========================

	var mdgram=require("mdgram");

Socket
------
	var Socket = mdgram.Socket;

This is the same as for the standard [Datagram Sockets](http://www.nodejs.org/api.html#dgram-267), except the prototype has been enriched by 4 methods:

* joinGroup(<Multicast-IP as a String>)
* leaveGroup(<Multicast-IP as a String>)
* setMulticastTTL(<TTL as an Integer between 0 and 255 (inclusive)>)
* setMulticastInterface(<IP of a local non-looping interface as a String>)

createSocket()
--------------
	var mdgram.createSocket("udp4",[<Listener Function>]);

This is the again the same as for the standard [Datagram Sockets](http://www.nodejs.org/api.html#dgram-267), except it creates a socket that has been enhanced by the mutlicast functions.
