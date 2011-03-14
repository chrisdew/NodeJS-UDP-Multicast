NodeJS UDP-Multicast
====================

Multicast UDP Sockets for NodeJS

[Node.js]: http://nodejs.org/
[Github repo]: http://github.com/phidelta/NodeJS-UDP-Multicast.git
[module site]: http://github.com/phidelta/NodeJS-UDP-Multicast

Installation
------------
	$ cd ~/.node_libraries
	$	git clone http://github.com/phidelta/NodeJS-UDP-Multicast.git mdgram
	$ cd mdgram
	$ node-waf configure build
	$ ln -s ./build/default/bindings.node bindings.node

OR

	$ git clone http://github.com/phidelta/NodeJS-UDP-Multicast.git mdgram
	$ cd mdgram
	$ npm install

OR SIMPLY

	$ npm install mdgram


Synopsis
--------

Create a Listening Socket:

	var mdgram=require('mdgram');
	var socket=mdgram.createSocket('udp4');
	socket.bind(1234);
	socket.joinGroup("225.0.0.73");

Setting the Multicast TimeToLive:

	socket.setMulticastTTL(5);

Setting the Multicast Interface:

	socket.setMulticastInterface("192.168.0.3"); // Where 192.168.0.3 is the IP of the interface you want to use Multicast on
	socket.setMulticastInterface(); // If you want the system to figure out which to use (commonly the first non-loopback interface)


Ubuntu/Debian specific notes on setMulticastInterface():

Add something like the lines below to /etc/network/interfaces to control which interface is the default for multicast.  By default, multicast uses the default route, not the first non-loopback interface.

    up route add -net 224.0.0.0 netmask 224.0.0.0 eth0
    down route del -net 224.0.0.0 netmask 224.0.0.0 eth0


Leaving a Multicast Group:

	socket.leaveGroup("225.0.0.73");


Authors
-------
Philipp Dunkel (phidelta at phideltacity.net)

License
-------

MIT license. See license text in file [LICENSE](http://github.com/phidelta/NodeJS-UDP-Multicast/blob/master/LICENSE).
