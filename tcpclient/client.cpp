

// client.cc
#include "client.h"
#include <QHostAddress>

Client::Client(QObject* parent): QObject(parent)
{
  connect(&client, SIGNAL(connected()),
    this, SLOT(startTransfer()));
}

Client::~Client()
{
  client.close();
}

void Client::start(QString address, quint16 port)
{
  QHostAddress addr(address);
  client.connectToHost(addr, port);
  //if(client.waitForConnected())
      //client.write("client send", 12);//连接到服务器之后向服务器发消息
}

void Client::startTransfer()
{
    char buffer[1024] = {0};
    client.read(buffer, client.bytesAvailable());
    cout<<buffer<<endl;
    client.write("Hello, world", 13);
}

