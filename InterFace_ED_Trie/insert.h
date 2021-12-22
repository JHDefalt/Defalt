#ifndef INSERT_H
#define INSERT_H

#include <QWidget>
#include "trie_source.h"

namespace Ui {
class insert;
}

class insert : public QWidget
{
    Q_OBJECT

public:
    explicit insert(QWidget *parent = nullptr);
    ~insert();
    void dowork();

private slots:
    void on_pushButton_insert_clicked();

    void on_pushButton_2_insert_clicked();

private:
    Ui::insert *ui;
};

#endif // INSERT_H
