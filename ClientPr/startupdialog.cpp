#include "startupdialog.h"
#include "ui_startupdialog.h"

// Конструктор окна подключения
startupDialog::startupDialog(QString *server, quint16 *port,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startupDialog) // Получаем IP и порт из диалогового окна
{
    serverAddr = server;
    serverPort = port;
    ui->setupUi(this);
}

startupDialog::~startupDialog() // Деструктор окна подключения
{
    delete ui;
}

void startupDialog::on_pushButton_clicked() // При нажатии на кнопку выполняем подключение к серверу
{
    *serverAddr = ui->lineEdit->text();
    *serverPort = (quint16)ui->lineEdit_2->text().toUShort();
    startupDialog::close();

}
