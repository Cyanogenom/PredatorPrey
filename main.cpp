#include <QApplication>
#include <QDateTime>
#include <QVector>
#include <QTimer>

#include "mwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QDateTime::currentMSecsSinceEpoch());
    unsigned int size = 50;

    field mobj;
    mobj.gen_field(size, size);

    mwindow *window = new mwindow(&mobj, size, size);
    window->show();
    window->set_size(size, size);


    return a.exec();
}
