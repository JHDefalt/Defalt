#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    this->setWindowTitle("操作指南");
    this->show();
    //设置图标
    this->setWindowIcon(QIcon(":normal_icon/icon/help.png"));
    //绑定按键
    ui->pushButton->setShortcut(Qt::Key_Escape);
}

help::~help()
{
    delete ui;
}

void help::on_pushButton_clicked()//关闭按钮
{
    this->close();
}
