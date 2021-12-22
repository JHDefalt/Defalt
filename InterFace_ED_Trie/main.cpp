#include "trie.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    trie w;
    w.setFixedSize(461,333);
    w.setWindowTitle("DLNU英语词典-Trie版");
    w.show();
    return a.exec();
}
