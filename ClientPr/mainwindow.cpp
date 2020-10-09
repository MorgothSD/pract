#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startupdialog.h"

MainWindow::MainWindow(QWidget *parent) : // Конструктор окна обмена сообщениями с сервером
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    serverAddr = new QString;
    serverPort = new quint16;
    startupDialog start(serverAddr,serverPort,this);
    start.setModal(true);
    start.exec();
    socket = new QUdpSocket(0);
    socket->bind(QHostAddress::Any,1234);
    ui->setupUi(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
}

MainWindow::~MainWindow() // Деструктор
{
    socket->close(); // Закрытие подключения
    delete socket;   // и удаление всех
    delete ui;       // переменных
    delete serverAddr;
    delete serverPort;
}

void MainWindow::handleReadyRead()
{
    char str[100]; // Массив для хранения отправленного и полученного сообщения
    QString tempString; // буфер для сообщения
    qint64 size; // размер буфера
    QByteArray temp; // Буфер в байтах
    quint16 tempPort; // Порт хоста
    QHostAddress tempAddr; // Адрес хоста
    ui->lineEdit_2->clear(); // Очистка окна ввода
    size = socket->pendingDatagramSize(); // Получаем размер сообщения
    socket->readDatagram(str,size,&tempAddr,&tempPort); // Считывание сообщения
    tempString.clear(); // Чистим буфер для сообщения
    for(int i=0;i<size;i++)
    {
        tempString.append(str[i]); // Анализ буфера с полученным сообщением, перезапись данных в str
    }
    //tempString.append(str);
    ui->lineEdit_2->clear();
    ui->lineEdit_2->setText(tempString);
}

void MainWindow::on_pushButton_clicked() // Действия кнопки
{
    QString temp;
    QHostAddress tempAddr(*serverAddr);
    temp = ui->lineEdit->text();
    QByteArray data(temp.toUtf8());
    ui->lineEdit->clear();
    socket->writeDatagram(data,tempAddr,*serverPort); // Отправка сообщения
    socket->flush();
}
