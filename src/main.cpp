#include "OccDemoMainWindow.h"
#include <QtWidgets/QApplication>
#include <qdesktopwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OccDemoMainWindow w;
    w.show();
    w.move((a.desktop()->width() - w.width()) / 2, (a.desktop()->height() - w.height()) / 2);

    return a.exec();

}
