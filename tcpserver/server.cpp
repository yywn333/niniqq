
// server.cc
#include "server.h"
#include <iostream>
#include<QFileDialog>
#include<QDebug>
using namespace std;

Server::Server(QObject* parent): QObject(parent)
{

    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    server.listen(QHostAddress::Any, 8888);

}

Server::~Server()
{
    server.close();
}

void Server::acceptConnection()
{
    qDebug() << "acceptConnection!";
    client = server.nextPendingConnection();
    client->write("welcome to server");         //向客户端发送信息
    connect(client,SIGNAL(readyRead()),this,SLOT(updaesave()));
    connect(client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void Server::startRead()
{
    char buffer[1024] = {0};
    client->read(buffer, client->bytesAvailable());
    cout<<buffer<<endl;
    client->write("wellcom to server\n");
    client->close();
}
void Server::receivefile()
{
    char buffer[1024] = {0};
    client->read(buffer, client->bytesAvailable());
    cout<<buffer<<endl;
    client->write("file from server\n");
}
void Server::updaesave()
{
    qDebug() << "start save file !";
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_4);

    if(bytesReceived <= sizeof(qint64)*2)
    {
        if((client->bytesAvailable() >= sizeof(qint64)*2)&& (fileNameSize == 0))
        { //接收数据总大小信息和文件名大小信息
            in >> totalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
            qDebug() << "get total bytes :"<<totalBytes<<"bytesReceived"<<bytesReceived<<endl;
        }
        if((client->bytesAvailable() >= fileNameSize) && (fileNameSize != 0))
        {  //接收文件名，并建立文件
            in >> fileName;

            bytesReceived += fileNameSize;
            localFile = new QFile(fileName);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug() << "open file error!";
                return;
            }
            qDebug() << "get file name  :"<<fileName<<"bytesReceived"<<bytesReceived<<endl;
        }
        else return;
    }

    if(bytesReceived < totalBytes)
    {  //如果接收的数据小于总数据，那么写入文件
        bytesReceived += client->bytesAvailable();
        inBlock = client->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
        qDebug() << "received "<<(int)(bytesReceived/totalBytes)<<"%";
    }

    if(bytesReceived >= totalBytes)
    {
        //接收数据完成时
        client->close();
        localFile->close();
        QFileDialog::getOpenFileName(
                    NULL,
                    "Open Document",
                    QDir::currentPath(),
                    "Document files (*.txt *.rtf);;All files(*.*)");
        qDebug() << "receive over ";

    }
}
void Server::displayError(QAbstractSocket::SocketError)
{
    qDebug() << server.errorString();
    client->close();
}
