#include "del.h"
#include "ui_del.h"

del::del(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::del)
{
    ui->setupUi(this);
    this->show();
    this->setFixedSize(353,132);
    this->setWindowTitle("删除单词");
    //设置图标
    this->setWindowIcon(QIcon(":normal_icon/icon/application_form_delete.png"));
    ui->pushButton_del->setIcon(QIcon(":normal_icon/icon/tick.png"));
    ui->pushButton_2_del->setIcon(QIcon(":normal_icon/icon/cross.png"));
    //绑定按键
    ui->pushButton_del->setShortcut(Qt::Key_Enter);
    ui->pushButton_del->setShortcut(Qt::Key_Return);
    ui->pushButton_2_del->setShortcut(Qt::Key_Escape);
    //连接槽
    connect(ui->pushButton_del,SIGNAL(released()),this,SLOT(on_pushButton_del_clicked));
    connect(ui->pushButton_2_del,SIGNAL(released()),this,SLOT(on_pushButton_2_del_clicked));
    ui->lineEdit->setFocus();
}

del::~del()
{
    delete ui;
}

void del::on_pushButton_del_clicked()//确认按钮
{
    this->dowork();
}

void del::dowork()//删除主功能
{
    if(ui->lineEdit->text() == "") QMessageBox::critical(this,"错误","请先输入内容！");
    else
    {
        rbt_source *rbt = new rbt_source();
        rbt->target_word = ui->lineEdit->text().toStdString();
        if(rbt->checkWord())
        {
            rbt->path = rbt->pre + rbt->target_word[0] + ".txt";
            rbt->dict = rbt->read();
            rbt->ans = rbt->search(rbt->dict);
            if (rbt->ans == NULL) QMessageBox::information(NULL, "提示", "该单词不存在");
            else
            {
                rbt->del();
                QMessageBox::information(NULL, "提示", "删除成功！");
            }
        }
        else
        {
            QMessageBox::critical(this,"错误","单词不合法！");
        }
    }
}

void del::on_pushButton_2_del_clicked()//取消按钮
{
    this->close();
}
