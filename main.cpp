#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec> // 需要包含头文件

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.show();
    return a.exec();
}
