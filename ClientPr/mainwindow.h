
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

// Описание класса, его функций и аргументов
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleReadyRead();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    QString *serverAddr;
    quint16 *serverPort;
};

#endif // MAINWINDOW_H
