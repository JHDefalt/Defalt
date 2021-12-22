#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setFixedSize(343,191);
}

login::~login()
{
    delete ui;
}

void login::Show()
{
    this->setWindowTitle("身份验证");
    //设置图标
    this->setWindowIcon(QIcon(":normal_icon/icon/user.png"));
    ui->pushButton->setIcon(QIcon(":normal_icon/icon/tick.png"));
    ui->pushButton_2->setIcon(QIcon(":normal_icon/icon/cross.png"));
    //按钮和按键绑定
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->pushButton->setShortcut(Qt::Key_Enter);
    ui->pushButton->setShortcut(Qt::Key_Return);
    ui->pushButton_2->setShortcut(Qt::Key_Escape);
    //按钮和槽绑定
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(on_pushButton_clicked));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(on_pushButton_2_clicked));
    this->show();
    ui->lineEdit->setFocus();
}

void login::setCall(int calling)//获取呼叫者
{
    whoCalling = calling;
}

void login::on_pushButton_clicked()//简单的身份验证
{
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "") QMessageBox::critical(this,"错误","请输入完整信息");
    else
    {
        if(ui->lineEdit->text() != "test") QMessageBox::critical(this,"错误","用户名错误"),ui->lineEdit->setText("");
        else
        {
            if(ui->lineEdit_2->text() != "test") QMessageBox::critical(this,"错误","密码错误"),ui->lineEdit_2->setText("");
            else
            {
                this->close();
                if(whoCalling == 1) new insert();
                else if(whoCalling == 2) new del();
                else if(whoCalling == 3) new modify();
                else if(whoCalling == 4) QDesktopServices::openUrl(QUrl::fromLocalFile("file:///C:\\CurriculumDesign\\ElectronicDictionary-trie\\Dictionary"));
                else if(whoCalling == 5) QDesktopServices::openUrl(QUrl::fromLocalFile("file:///C:\\CurriculumDesign\\ElectronicDictionary-trie\\ElectronicDictionary-trie"));
            }
        }
    }
}

void login::on_pushButton_2_clicked()//关闭按钮
{
    this->close();
}
