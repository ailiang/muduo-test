#include "echo.h"
#include "muduo/net/EventLoop.h"
int main()
{
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr( 9999 );
	EchoServer server( &loop, listenAddr );
	server.start();
	loop.loop();
	return 0;
}


