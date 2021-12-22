#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "insert.h"
#include "del.h"
#include "modify.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    int whoCalling;
    void setCall(int num);
    void Show();
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
