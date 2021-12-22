#include "insert.h"
#include "ui_insert.h"

insert::insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insert)
{
    ui->setupUi(this);
    this->show();
    this->setFixedSize(352,232);
    this->setWindowTitle("插入单词");
    //设置图标
    this->setWindowIcon(QIcon(":normal_icon/icon/application_form_add.png"));
    ui->pushButton_insert->setIcon(QIcon(":normal_icon/icon/tick.png"));
    ui->pushButton_2_insert->setIcon(QIcon(":normal_icon/icon/cross.png"));
    //绑定按键
    ui->pushButton_insert->setShortcut(Qt::Key_Enter);
    ui->pushButton_insert->setShortcut(Qt::Key_Return);
    ui->pushButton_2_insert->setShortcut(Qt::Key_Escape);
    //连接槽
    connect(ui->pushButton_insert,SIGNAL(released()),this,SLOT(on_pushButton_insert_clicked));
    connect(ui->pushButton_2_insert,SIGNAL(released()),this,SLOT(on_pushButton_2_insert_clicked));
    ui->lineEdit->setFocus();
}

insert::~insert()
{
    delete ui;
}

void insert::on_pushButton_insert_clicked()//确认按钮
{
    this->dowork();
}

void insert::dowork()//插入主功能
{
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "") QMessageBox::critical(this,"错误","请先输入内容！");
    else
    {
        trie_source *trie = new trie_source();
        trie->target_word = ui->lineEdit->text().toStdString();
        if(trie->checkWord())
        {
            trie->path = trie->pre + trie->target_word[0] + ".txt";
            trie->dict = trie->read();
            trie->ans = trie->search(trie->dict);
            if (trie->ans != NULL)
            {
                QMessageBox::information(NULL, "提示", "该单词已存在");
            }
            else
            {
                trie->target_nature = string((const char *)ui->lineEdit_2->text().toLocal8Bit());
                trie->target_mean = string((const char *)ui->lineEdit_3->text().toLocal8Bit());
                trie->insert();
                QMessageBox::information(NULL, "提示", "插入成功！");
            }
        }
        else
        {
            QMessageBox::critical(this,"错误","单词不合法！");
        }
    }
}

void insert::on_pushButton_2_insert_clicked()//关闭按钮
{
    this->close();
}
