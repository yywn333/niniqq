
// main.cc
#include "client.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Client client;
    client.openFile();
    client.start("222.20.58.103", 8888);

    return app.exec();
}
