#ifndef RBT_H
#define RBT_H

#include <QMainWindow>
#include "login.h"
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QClipboard>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include "help.h"
#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class rbt; }
QT_END_NAMESPACE

class rbt : public QMainWindow
{
    Q_OBJECT

public:
    rbt(QWidget *parent = nullptr);
    ~rbt();
    QLabel* time,* inform,* welcome;
    void keyPressEvent(QKeyEvent *event);

private slots:

    void on_pushButton_2_clicked();

    void on_actionInsert_triggered();

    void on_actionDelete_triggered();

    void on_actionModify_triggered();

    void on_pushButton_clicked();

    void on_actionc_triggered();

    void on_actionasd_2_triggered();

    void on_actionasd_triggered();

    void on_actiona_triggered();

    void on_actiona_3_triggered();

    void on_actionyu_triggered();

    void on_actiona_4_triggered();

    void time_update();

private:
    Ui::rbt *ui;
};
#endif // RBT_H





