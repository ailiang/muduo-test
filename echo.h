

#include "muduo/net/TcpServer.h"

class EchoServer
{
public:
	EchoServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr);
	void start();
private:
	void OnConnection(const muduo::net::TcpConnectionPtr& conn);
	void OnMessage( const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);
	muduo::net::EventLoop* _loop;
	muduo::net::TcpServer _server;
};
