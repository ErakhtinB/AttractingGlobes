#include <QApplication>
#include "paintwidget.h"
#include "circle.h"

int main(int argc, char *argv[])
{
    int intBalls = 10;
    int updateMs = 10;
    QApplication a(argc, argv);
    PaintWidget wgt(intBalls, updateMs);
    wgt.setStyleSheet("background-color: white");
    wgt.showMaximized();
    return a.exec();
}

