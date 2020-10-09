#include "mainwindow.h"

#include <QApplication>

// Файл в первозданном виде, как при создании проекта, изменений не вносилось
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
