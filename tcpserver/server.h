#ifndef SERVER
#define SERVER

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server: public QObject
{
    Q_OBJECT
public:
    Server(QObject * parent = 0);
    ~Server();
    //void sendfile();

public slots:
    void updaesave();
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError);
    void startRead();
    void receivefile();

private:
    QTcpServer server;
    QTcpSocket* client;
    qint64 totalBytes;  //存放总大小信息
    qint64 bytesReceived;  //已收到数据的大小
    qint64 fileNameSize;  //文件名的大小信息
    QString fileName;   //存放文件名
    QFile *localFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区
};


#endif // SERVER

