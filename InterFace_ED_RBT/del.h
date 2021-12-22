#ifndef DEL_H
#define DEL_H

#include <QWidget>
#include "rbt_source.h"

namespace Ui {
class del;
}

class del : public QWidget
{
    Q_OBJECT

public:
    explicit del(QWidget *parent = nullptr);
    ~del();
    void dowork();

private slots:

    void on_pushButton_del_clicked();

    void on_pushButton_2_del_clicked();

private:
    Ui::del *ui;
};

#endif // DEL_H
