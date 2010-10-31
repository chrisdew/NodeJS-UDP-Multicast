var binding = require('./bindings');
var dgram=require("dgram");

var Socket=dgram.Socket;
exports.Socket = Socket;
exports.createSocket = function (type, listener) {
	if (type != 'udp4') {
		throw new TypeError("Invalid Multicast Socket-Type: "+type);
	}
  return new Socket(type, listener);
};

Socket.prototype.joinGroup = function(group) {
	if (!this.fd) throw new Error('Not running');
	if(binding.joinGroup(this.fd, group+"")) return;
	throw new Error("Could not joinGroup: "+group);
};
Socket.prototype.leaveGroup = function(group) {
	if (!this.fd) throw new Error('Not running');
	if (binding.leaveGroup(this.fd, group+"")) return;
	throw new Error("Could not leaveGroup: "+group);
};
Socket.prototype.setMulticastTTL = function(arg) {
  if (!this.fd) throw new Error('Not running');

	var newttl = parseInt(arg,10);
  if (newttl > 0 && newttl < 256) {
    if(binding.setTTL(this.fd, newttl)) return;
		throw new Error("Could not setMulticastTTL: "+group);
  } else {
    throw new Error("New MulticastTTL must be between 1 and 255");
  }
};
Socket.prototype.setMulticastInterface = function(arg) {
  if (!this.fd) throw new Error('Not running');
	if (binding.setInterface(this.fd, arg+"")) return;
	throw new Error("Could not setMulticastInterface: "+group);
};
