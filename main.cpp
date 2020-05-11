#include "mainwindow.h"
#include <QApplication>
#include <windows.h>
#include "fileapi.h"

int main(int argc, char *argv[])
{
    CreateDirectoryA("data", NULL);
    SetFileAttributesA("data",FILE_ATTRIBUTE_HIDDEN);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
