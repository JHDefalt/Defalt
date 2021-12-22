#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->show();
    this->setFixedSize(521,265);
    this->setWindowTitle("关于");
    //设置图标
    this->setWindowIcon(QIcon(":normal_icon/icon/sign.png"));
    //绑定按键
    ui->pushButton->setShortcut(Qt::Key_Escape);
    //连接槽
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(on_pushButton_clicked));
}

about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()//close按钮
{
    this->close();
}
