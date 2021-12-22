#include "rbt.h"
#include "ui_rbt.h"

rbt::rbt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::rbt)
{
    ui->setupUi(this);

    //创建时间
    time = new QLabel;
    ui->statusBar->addWidget(time);
    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this,SLOT(time_update()));
    //创建基础信息
    welcome = new QLabel("欢迎 ");
    ui->statusBar->addWidget(welcome);
    inform = new QLabel("作者:Defalt  版本号:1.0.0");
    ui->statusBar->addWidget(inform);

    //设置主界面图标
    this->setWindowIcon(QIcon(":normal_icon/icon/sign.png"));
    ui->pushButton->setIcon(QIcon(":normal_icon/icon/magnifier.png"));
    ui->pushButton_2->setIcon(QIcon(":normal_icon/icon/arrow_refresh.png"));
    //设置菜单栏-文件图标
    ui->actiona->setIcon(QIcon(":normal_icon/icon/folder.png"));
    ui->actionasd->setIcon(QIcon(":normal_icon/icon/folder.png"));
    //设置菜单栏-其他图标
    ui->actionInsert->setIcon(QIcon(":normal_icon/icon/application_form_add.png"));
    ui->actionDelete->setIcon(QIcon(":normal_icon/icon/application_form_delete.png"));
    ui->actionModify->setIcon(QIcon(":normal_icon/icon/application_form_edit.png"));
    //设置菜单栏-帮助图标
    ui->actionc->setIcon(QIcon(":normal_icon/icon/help.png"));
    ui->menu_4->setIcon(QIcon(":normal_icon/icon/status_online.png"));
    ui->actiona_3->setIcon(QIcon(":normal_icon/icon/world.png"));
    ui->actionyu->setIcon(QIcon(":normal_icon/icon/email.png"));
    ui->actiona_4->setIcon(QIcon(":normal_icon/icon/phone.png"));
    ui->actionasd_2->setIcon(QIcon(":normal_icon/icon/information.png"));
    //设置子菜单显示位置
    ui->menu_2->move(722,380);
    ui->menu->move(777,380);
    ui->menu_3->move(836,380);
    //主界面快捷键绑定
    ui->pushButton->setShortcut(Qt::Key_Enter);
    ui->pushButton->setShortcut(Qt::Key_Return);
    //所有信号与槽的连接
    connect(ui->actionasd,SIGNAL(released()),this,SLOT(on_actionasd_triggered));
    connect(ui->actiona,SIGNAL(released()),this,SLOT(on_actiona_triggered));
    connect(ui->actionyu,SIGNAL(released()),this,SLOT(on_actiona_3_triggered));
    connect(ui->actiona_3,SIGNAL(released()),this,SLOT(on_actiona_3_triggered));
    connect(ui->actiona_4,SIGNAL(released()),this,SLOT(on_actiona_3_triggered));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(on_pushButton_clicked));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(on_pushButton_2_clicked));
    connect(ui->actionInsert,SIGNAL(released()),this,SLOT(on_actionInsert_triggered));
    connect(ui->actionDelete,SIGNAL(released()),this,SLOT(on_actionDelete_triggered));
    connect(ui->actionModify,SIGNAL(released()),this,SLOT(on_actionModify_triggered));
}

rbt::~rbt()
{
    delete ui;
}

void rbt::on_pushButton_clicked()//查询操作
{
    if(ui->lineEdit->text() == "") QMessageBox::critical(this,"错误","请先输入内容！");
    else
    {
        ui->textBrowser->setText("");
        rbt_source *rbt = new rbt_source();
        rbt->target_word = ui->lineEdit->text().toStdString();
        if(rbt->checkWord())
        {
            rbt->path = rbt->pre + rbt->target_word[0] + ".txt";
            rbt->dict = rbt->read();
            rbt->ans = rbt->search(rbt->dict);
            if (rbt->ans == NULL)
            {
                QMessageBox::information(NULL, "提示", "该单词不存在");
                rbt->updataLack();
            }
            else
            {
                QString translate;
                string nows = rbt->ans->translate;
                int pos = 0;
                int start = 0;
                while (pos != nows.npos) {
                    pos = nows.find('@', start);
                    string sub = nows.substr(start, pos);
                    translate = QString(QString::fromLocal8Bit(sub.c_str()));
                    ui->textBrowser->append(translate);
                    if (pos != nows.npos) start = pos + 1,nows = nows.substr(start,nows.length() - pos - 1);
                    start = 0;
                }
            }
        }
        else
        {
            QMessageBox::critical(NULL, "错误", "单词不合法！");
        }
    }
}

void rbt::on_pushButton_2_clicked()//清空按钮
{
    if(ui->lineEdit->text() == "") QMessageBox::critical(this,"错误","请先输入内容！");
    else ui->lineEdit->setText(""),ui->textBrowser->setText("");
}

void rbt::on_actionInsert_triggered()//插入按钮
{
    login *ret = new login();
    ret->setCall(1);
    ret->Show();
}

void rbt::on_actionDelete_triggered()//删除按钮
{
    login *ret = new login();
    ret->setCall(2);
    ret->Show();
}

void rbt::on_actionModify_triggered()//修改按钮
{
    login *ret = new login();
    ret->setCall(3);
    ret->Show();
}

void rbt::on_actionc_triggered()//帮助按钮
{
    new help();
}

void rbt::on_actionasd_triggered()//打开词典按钮
{
    login *ret = new login();
    ret->setCall(4);
    ret->Show();
}

void rbt::on_actionasd_2_triggered()//关于按钮
{
    new about();
}

void rbt::on_actionyu_triggered()//作者邮箱按钮
{
    QString source = ui->actionyu->text();
    QString number = source.mid(3,21);
    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = clipboard->text();
    clipboard->setText(number);
    QMessageBox::information(this,"提示","内容已复制");
}

void rbt::on_actiona_triggered()//打开源码按钮
{
    login *ret = new login();
    ret->setCall(5);
    ret->Show();
}

void rbt::on_actiona_3_triggered()//作者qq按钮
{
    QString source = ui->actiona_3->text();
    QString number = source.mid(3,12);
    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = clipboard->text();
    clipboard->setText(number);
    QMessageBox::information(this,"提示","内容已复制");
}

void rbt::on_actiona_4_triggered()//作者电话按钮
{
    QString source = ui->actiona_4->text();
    QString number = source.mid(3,16);
    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = clipboard->text();
    clipboard->setText(number);
    QMessageBox::information(this,"提示","内容已复制");
}

void rbt::time_update() //更新时间
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString("当前时间:yyyy年MM月dd日 hh:mm:ss");
    time->setText(timestr); //设置label的文本内容为时间
}

void rbt::keyPressEvent(QKeyEvent *event)//键盘绑定按钮
{
    if(event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_F)//打开文件子菜单
    {
        ui->menu_2->showNormal();
    }
    else if(event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_H)////打开帮助子菜单
    {
        ui->menu_3->showNormal();
    }
    else if(event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_W)//打开操作子菜单
    {
        ui->menu->showNormal();
    }
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_I)//打开插入操作
    {
        on_actionInsert_triggered();
    }
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_D)//打开删除操作
    {
        on_actionDelete_triggered();
    }
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_M)//打开修改操作
    {
        on_actionModify_triggered();
    }
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_F1)//打开字典目录
    {
        on_actionasd_triggered();
    }
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_F2)//打开源码目录
    {
        on_actiona_triggered();
    }
    else if(event->key() == Qt::Key_F1)//打开操作指南
    {
        on_actionc_triggered();
    }
    else if(event->key() == Qt::Key_F2)//打开关于
    {
        on_actionasd_2_triggered();
    }
}
