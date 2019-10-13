#include "BoggleWindow.h"
#include "lexicon.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    qRegisterMetaType<vector<Location>>("vector<Location>");
    qRegisterMetaType<string>("string");
    QApplication a(argc, argv);
    BoggleWindow w;
    w.show();

    return a.exec();
}
