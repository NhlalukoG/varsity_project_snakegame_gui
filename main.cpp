#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <qthread.h>

class I : public QThread
{
public:
    static void sleep(unsigned long secs) { QThread::sleep(secs); }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap splashimage(":/images/Splash.png");
    QSplashScreen splash(splashimage);

    splash.showMessage(QObject::tr("Initiating your program now..."),
                    Qt::AlignLeft | Qt::AlignTop, Qt::black);  //This line represents the alignment of text, color and position

    splash.show();

    MainWindow w;
    w.setWindowTitle("Snake Game");


    //splash.finish(&w);



    w.showMaximized();

    return a.exec();
}
