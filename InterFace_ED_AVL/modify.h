#ifndef MODIFY_H
#define MODIFY_H

#include <QWidget>
#include <avl_source.h>

namespace Ui {
class modify;
}

class modify : public QWidget
{
    Q_OBJECT

public:
    explicit modify(QWidget *parent = nullptr);
    ~modify();
    int whoChecked;
    void dowork();

private slots:
    void on_pushButton_mod_clicked();

    void on_pushButton_2_mod_clicked();

    void on_pushButton_3_mod_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

private:
    Ui::modify *ui;
};

#endif // MODIFY_H
