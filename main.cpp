#include "mainwindow.h"

#include <Encoder.h>
#include <Decoder.h>

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
