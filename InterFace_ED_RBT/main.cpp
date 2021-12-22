#include "rbt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rbt w;
    w.setFixedSize(475,333);
    w.setWindowTitle("DLNU英语词典-RBT版");
    w.show();
    return a.exec();
}
