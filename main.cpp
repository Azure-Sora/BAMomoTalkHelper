#include "BAMomoTalkHelper.h"
#include"windows.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BAMomoTalkHelper w;
    AllocConsole();
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    w.show();
    return a.exec();
}
