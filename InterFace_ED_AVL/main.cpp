#include "avl.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AVL w;
    w.setFixedSize(471,333);
    w.setWindowTitle("DLNU英语词典-AVL版本");
    w.show();
    return a.exec();
}
