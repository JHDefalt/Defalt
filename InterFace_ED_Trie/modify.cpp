#include "modify.h"
#include "ui_modify.h"

modify::modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modify)
{
    ui->setupUi(this);
    this->show();
    this->setFixedSize(408,312);
    this->setWindowTitle("更改单词");
    //设置图标
    this->setWindowIcon(QIcon(":normal_icon/icon/application_form_edit.png"));
    ui->pushButton_mod->setIcon(QIcon(":normal_icon/icon/tick.png"));
    ui->pushButton_2_mod->setIcon(QIcon(":normal_icon/icon/cross.png"));
    ui->pushButton_3_mod->setIcon(QIcon(":normal_icon/icon/arrow_refresh.png"));
    //按钮和快捷键绑定
    ui->pushButton_mod->setShortcut(Qt::Key_Enter);
    ui->pushButton_mod->setShortcut(Qt::Key_Return);
    ui->pushButton_2_mod->setShortcut(Qt::Key_Escape);
    //按钮和槽绑定
    connect(ui->pushButton_mod,SIGNAL(released()),this,SLOT(on_pushButton_mod_clicked));
    connect(ui->pushButton_2_mod,SIGNAL(released()),this,SLOT(on_pushButton_2_mod_clicked));
    connect(ui->pushButton_3_mod,SIGNAL(released()),this,SLOT(on_pushButton_3_mod_clicked));
    connect(ui->radioButton,SIGNAL(released()),this,SLOT(on_radioButton_clicked));
    connect(ui->radioButton_2,SIGNAL(released()),this,SLOT(on_radioButton_2_clicked));
    connect(ui->radioButton_3,SIGNAL(released()),this,SLOT(on_radioButton_3_clicked));
}

modify::~modify()
{
    delete ui;
}

void modify::on_pushButton_mod_clicked()//确认按钮
{
    this->dowork();
    this->on_pushButton_3_mod_clicked();
}

void modify::dowork()//修改主功能
{
    if(ui->lineEdit_4->text() == "") QMessageBox::critical(this,"错误","请先输入内容！");
    else
    {
        trie_source *trie = new trie_source();
        trie->target_word = ui->lineEdit_4->text().toStdString();
        if(trie->checkWord())
        {
            trie->path = trie->pre + trie->target_word[0] + ".txt";
            trie->dict = trie->read();
            trie->ans = trie->search(trie->dict);
            if (trie->ans == NULL)
            {
                QMessageBox::information(NULL, "提示", "该单词不存在");
                trie->updataLack();
            }
            else
            {
                if(whoChecked == 1)
                {
                    if(ui->lineEdit->text() == "") QMessageBox::information(NULL, "提示", "请先输入单词");
                    else
                    {
                        string nword = string((const char *)ui->lineEdit->text().toLocal8Bit());
                        trie->changeWord(nword, trie->ans->translate);
                        QMessageBox::information(NULL, "提示", "更新成功");
                    }
                }
                else if(whoChecked == 2)
                {
                    if(ui->lineEdit_2->text() == "") QMessageBox::information(NULL, "提示", "请先输入单词");
                    else
                    {
                        string nature = string((const char *)ui->lineEdit_5->text().toLocal8Bit());
                        string mean = string((const char *)ui->lineEdit_2->text().toLocal8Bit());
                        trie->changeWord(trie->ans->word, nature + " " + mean);
                        QMessageBox::information(NULL, "提示", "更新成功");
                    }
                }
                else if(whoChecked == 3)
                {
                    if(ui->lineEdit_3->text() == "") QMessageBox::information(NULL, "提示", "请先输入单词");
                    else
                    {
                        string nature = string((const char *)ui->lineEdit_6->text().toLocal8Bit());
                        string mean = string((const char *)ui->lineEdit_3->text().toLocal8Bit());
                        trie->changeWord(trie->ans->word, trie->ans->translate + "@" + nature + " " + mean);
                        QMessageBox::information(NULL, "提示", "更新成功");
                    }
                }
            }
        }
        else
        {
            QMessageBox::critical(this,"错误","单词不合法！");
        }
    }
}

void modify::on_pushButton_2_mod_clicked()//关闭按钮
{
    this->close();
}

void modify::on_pushButton_3_mod_clicked()//清空按钮
{
    ui->radioButton->setCheckable(false);
    ui->radioButton->setCheckable(true);
    ui->radioButton_2->setCheckable(false);
    ui->radioButton_2->setCheckable(true);
    ui->radioButton_3->setCheckable(false);
    ui->radioButton_3->setCheckable(true);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit_4->setEnabled(true);
    ui->lineEdit_5->setEnabled(true);
    ui->lineEdit_6->setEnabled(true);
}

void modify::on_radioButton_clicked()//更该单词选项
{
    whoChecked = 1;
    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(true);
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_6->setEnabled(false);

}

void modify::on_radioButton_2_clicked()//更改释义选项
{
    whoChecked = 2;
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(true);
    ui->lineEdit_5->setEnabled(true);
    ui->lineEdit_6->setEnabled(false);
}

void modify::on_radioButton_3_clicked()//增加释义选项
{
    whoChecked = 3;
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit_4->setEnabled(true);
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_6->setEnabled(true);
}
