

// client.cc
#include "client.h"
#include <iostream>
#include<QDebug>
#include <QFileDialog>
#include <QHostAddress>
using namespace std;


Client::Client(QObject* parent): QObject(parent)
{
    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    connect(&client, SIGNAL(connected()), this, SLOT(sendfile()));
    //当连接服务器成功时，发出connected()信号，我们开始传送文件
    connect(&client,SIGNAL(bytesWritten(qint64)),this,SLOT(updatefile(qint64 )));
    //当有数据发送成功时，我们更新进度条
    connect(&client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}

Client::~Client()
{
    client.close();
}

void Client::start(QString address, quint16 port)
{
    QHostAddress addr(address);
    client.connectToHost(addr, port);

}

void Client::startTransfer()
{
    client.write("Hello, server\n");
    char buffer[1024] = {0};
    client.read(buffer, client.bytesAvailable());
    cout<<buffer<<endl;

}

void Client::sendfile()
{
    qDebug() << client.readAll();
    qDebug() << "start send!"<<endl;
    bytesWritten = 0;
    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }
    totalBytes = localFile->size();
    //文件总大小
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_4);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    qDebug() << "start currentFileName!"<<currentFileName<<endl;
    sendOut << qint64(0) << qint64(0) << currentFileName;
    //依次写入总大小信息空间，文件名大小信息空间，文件名---仅是文件名不含路径，没必要含路径
    totalBytes += outBlock.size();
    //这里的总大小是文件名大小等信息和实际文件大小的总和
    sendOut.device()->seek(0);
    sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));
    //totalBytes是文件总大小，即两个quint64的大小+文件名+文件实际内容的大小
    //qint64((outBlock.size() - sizeof(qint64)*2))得到的是文件名大小
    bytesToWrite = totalBytes - client.write(outBlock);
    qDebug() << "start bytesToWrite!"<<bytesToWrite<<endl;
    //发送完头数据后剩余数据的大小，即文件实际内容的大小

    outBlock.resize(0);
}
void Client::updatefile(qint64 numBytes)
{
    qDebug() << "start numBytes!"<<numBytes<<endl;
    bytesWritten += (int)numBytes;
    //已经发送数据的大小
    if(bytesToWrite > 0) //如果已经发送了数据
    {
        outBlock = localFile->read(qMin(bytesToWrite,loadSize));
        //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
        //就发送剩余数据的大小
        bytesToWrite -= (int)client.write(outBlock);
        qDebug() << "start numBytes!"<<numBytes<<endl;

        //发送完一次数据后还剩余数据的大小
        outBlock.resize(0);
        //清空发送缓冲区
    }
    else
    {
        localFile->close(); //如果没有发送任何数据，则关闭文件
    }

    //更新进度条
    if(bytesWritten >= totalBytes) //发送完毕
    {
        localFile->close();
        client.close();
    }
}
void Client::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug()<<"error\n";
    qDebug() << client.errorString();
    client.close();

}
void Client::openFile()   //打开文件
{
    fileName = QFileDialog::getOpenFileName(NULL);
    qDebug()<<fileName;
}
