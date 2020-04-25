#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QCoreApplication::setOrganizationName(QLatin1String("Google"));
    QCoreApplication::setApplicationName(QLatin1String("Chrome"));
    QCoreApplication::setApplicationVersion(QLatin1String("37.0.2062.120 "));

    w.show();
    //w.hide();
    
    return a.exec();
}
