#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasedata.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //链接
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("cars");
    //设置qt的字符集
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //打开数据库
    if(!db.open()){
         QMessageBox::warning(this,"warning",db.lastError().text());
         return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// login登录按钮到info页面的槽函数
void MainWindow::on_toolButton_2_clicked()
{
        //判断用户名和密码是否正确
        //如果错误则弹出警告对话框
        //读取数据库的用户名和密码
        if(DatabaseData::VerificationLogin(ui->lineEditPhoneInput->text().trimmed(),ui->lineEditPhoneInput_2->text().trimmed()))
        {
           //登录成功，则触发accept函数
           QMessageBox::information(this,"提示：","登录成功！",QMessageBox::Yes);
           this->hide();
           emit loginsignal();

        }
        else
        {
           //登录失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
           QMessageBox::warning(this,"警告！","用户名或者密码错误！",QMessageBox::Yes);
           ui->lineEditPhoneInput->clear();//清空用户编辑框
           ui->lineEditPhoneInput_2->clear();
           ui->lineEditPhoneInput->setFocus();//设置光标到用户编辑框
        }
}

// reginster注册按钮到toRegister注册页面的槽函数
void MainWindow::on_toolButton_clicked()
{
    this->hide();
    emit registersignal();
}

void MainWindow::acceptedlogin()
{
    this->show();
}
