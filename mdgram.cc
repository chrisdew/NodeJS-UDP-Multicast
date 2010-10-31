#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>

namespace node_mdgram {
	using namespace v8;

#define FD_ARG(a)                                        \
  int fd;                                                \
  if (!(a)->IsInt32() || (fd = (a)->Int32Value()) < 0) { \
    return ThrowException(Exception::TypeError(          \
          String::New("Bad file descriptor argument"))); \
}
	
	static Handle<Value> joinGroup(const Arguments& args) {
		struct ip_mreq mreq;
		char group[16];

		HandleScope scope;
		if (args.Length() < 2) {
			return ThrowException(Exception::TypeError(
				String::New("Must have at least two args"))
			);
		}

		if (!args[1]->IsString()) {
			return ThrowException(Exception::TypeError(
				String::New("Must have at least two args"))
			);
		}

		FD_ARG(args[0])

		String::Utf8Value groupaddr(args[1]->ToString());
		if (groupaddr.length() > 15) {
	    return Exception::Error(String::New("Multicast Group too long"));
	  }
	  memcpy(group, *groupaddr, groupaddr.length());

		mreq.imr_multiaddr.s_addr=inet_addr(group);
	  mreq.imr_interface.s_addr=htonl(INADDR_ANY);

		if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
			return ThrowException(Exception::Error(String::New(strerror(errno))));
		}

		return True();
	}
	static Handle<Value> leaveGroup(const Arguments& args) {
		struct ip_mreq mreq;
		char group[16];

		HandleScope scope;
		if (args.Length() < 2) {
			return ThrowException(Exception::TypeError(
				String::New("Must have at least two args"))
			);
		}

		if (!args[1]->IsString()) {
			return ThrowException(Exception::TypeError(
				String::New("Must have at least two args"))
			);
		}

		FD_ARG(args[0])

		String::Utf8Value groupaddr(args[1]->ToString());
		if (groupaddr.length() > 15) {
	    return Exception::Error(String::New("Multicast Group too long"));
	  }
	  memcpy(group, *groupaddr, groupaddr.length());

		mreq.imr_multiaddr.s_addr=inet_addr(group);
	  mreq.imr_interface.s_addr=htonl(INADDR_ANY);

		if (setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
			return ThrowException(Exception::Error(String::New(strerror(errno))));
		}

		return True();
	}
	static Handle<Value> setTTL(const Arguments& args) {
		HandleScope scope;
		if (args.Length() < 2) {
			return ThrowException(Exception::TypeError(
				String::New("Must have at least two args"))
			);
		}

		FD_ARG(args[0])

		u_char ttl = args[1]->Int32Value();
		if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
			return ThrowException(Exception::Error(String::New(strerror(errno))));
		}

		return True();
	}
	static Handle<Value> setInterface(const Arguments& args) {
		in_addr_t ifaddr;
		char ifnamestr[16];

		HandleScope scope;
		if (args.Length() < 2) {
			return ThrowException(Exception::TypeError(
				String::New("Must have at least two args"))
			);
		}

		FD_ARG(args[0])

		String::Utf8Value ifname(args[1]->ToString());
		if (ifname.length() > 15) {
	    return Exception::Error(String::New("Multicast Interface too long"));
	  }
	  memcpy(ifnamestr, *ifname, ifname.length());
		ifaddr = inet_addr(ifnamestr);
		if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &ifaddr, sizeof(ifaddr)) < 0) {
			return ThrowException(Exception::Error(String::New(strerror(errno))));
		}

		return True();
	}
	
	extern "C" void init(Handle<Object> target) {
	  HandleScope scope;
		NODE_SET_METHOD(target, "joinGroup", joinGroup);
		NODE_SET_METHOD(target, "leaveGroup", leaveGroup);
		NODE_SET_METHOD(target, "setTTL", setTTL);
		NODE_SET_METHOD(target, "setInterface", setInterface);
	}
}