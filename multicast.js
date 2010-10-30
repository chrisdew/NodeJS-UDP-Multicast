var binding = require('./bindings');
var dgram=require("dgram");

var Socket={};
Socket.joinGroup = function(group) {
	if (!this.fd) throw new Error('Not running');
	return binding.joinGroup(this.fd, group+"");
};
Socket.leaveGroup = function(group) {
	if (!this.fd) throw new Error('Not running');
	return binding.leaveGroup(this.fd, group+"");
};
Socket.setMulticastTTL = function(arg) {
  if (!this.fd) throw new Error('Not running');

	var newttl = parseInt(arg,10);
  if (newttl > 0 && newttl < 256) {
    return binding.setTTL(this.fd, newttl);
  } else {
    throw new Error("New MulticastTTL must be between 1 and 255");
  }
};
Socket.setMulticastInterface = function(arg) {
  if (!this.fd) throw new Error('Not running');
	return binding.setInterface(this.fd, arg+"");
};

exports.createSocket = function() {
	var socket = dgram.createSocket("udp4");
	socket.joinGroup = Socket.joinGroup;
	socket.leaveGroup = Socket.leaveGroup;
	socket.setMulticastTTL = Socket.setMulticastTTL;
	socket.setMulticastInterface = Socket.setMulticastInterface;
	return socket;
};
