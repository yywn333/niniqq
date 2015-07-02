#ifndef CLIENT
#define CLIENT
// client.h
#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client: public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = 0);
    ~Client();
    void start(QString address, quint16 port);

    void openFile();
public slots:
    void sendfile();
    void startTransfer();
    void updatefile(qint64);
    void displayError(QAbstractSocket::SocketError);
private:
    QTcpSocket client;
    QFile *localFile;  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QString fileName;  //保存文件路径
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据
};
#endif // CLIENT

