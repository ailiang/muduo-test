#include "echo.h"
#include "muduo/base/Logging.h"
#include <functional>

EchoServer::EchoServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr) : _loop( loop ), _server(loop, listenAddr, "EchoServer")
{
	_server.setConnectionCallback( std::bind(&EchoServer::OnConnection, this, std::placeholders::_1) );
	_server.setMessageCallback( std::bind(&EchoServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3) );
}

void EchoServer::start()
{
	_server.start();
}

void EchoServer::OnConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << "conn" << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() ;
}

void EchoServer::OnMessage( const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << "echo" << msg.size() << "bytes, "  << " data receive at" << time.toString();
	conn->send(msg);
}


