#include "udpserver.h"
#include <QString>
#include <QTextStream>
QTextStream cout(stdout);
QTextStream cin(stdin);

UDPserver::UDPserver(QObject *parent)
    : QUdpSocket(parent)
{

}

UDPserver::~UDPserver()
{
    socket->close();
    delete socket;
}

void UDPserver::openConnection()
{
    socket = new QUdpSocket;
    if(!socket->bind(QHostAddress::LocalHost,27016))
    {
        qDebug() << "Could not start server.";

    }
    else
    {
        qDebug() << "Listening on port 27016.";
        connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    }


}

void UDPserver::handleReadyRead()
{
    QHostAddress *userAddr;
    quint16 *userPort;
    char str[100];
    for(int i=1;i<100;i++)
        str[i]='\0';
    qint64 dataSize;
    userAddr=new QHostAddress;
    userPort = new quint16;
    dataSize = socket->pendingDatagramSize();
    socket->readDatagram(str,dataSize,userAddr,userPort);

    qDebug() << "Client said: " << str;

    QString answear;
    qDebug() << "Enter an answear to client: ";
    answear = cin.readLine();
    const char* sendline=answear.toUtf8().constData();


    socket->writeDatagram(sendline,*userAddr,*userPort);
    delete userAddr;
    delete userPort;
}
