#include "toregister.h"
#include "ui_toregister.h"
#include "telecheck.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>

toRegister::toRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::toRegister)
{
    ui->setupUi(this);
}

toRegister::~toRegister()
{
    delete ui;
}

void toRegister::acceptedregister()
{
    this->show();
}

// 注册成功，点击提交到登录页面的槽函数
void toRegister::on_toolButton_clicked()
{
    //数据库操作
    QString nick=ui->lineEditPhoneInput->text().trimmed();
    QString tele =ui->lineEditPhoneInput_2->text().trimmed();
    QString pwd1 =ui->lineEditPhoneInput_3->text().trimmed();
    QString pwd2 =ui->lineEditPhoneInput_4->text().trimmed();
    QString name =ui->lineEditPhoneInput_5->text().trimmed();
    telecheck telephone;
    qDebug()<<nick<<pwd1<<pwd2<<tele<<name;
    if(pwd1!=pwd2||telephone.checkin(tele)||nick.isEmpty()||pwd1.isEmpty()||tele.isEmpty()||name.isEmpty())
    {
        //注册失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
        QMessageBox::warning(this,tr("警告！"),tr("手机号已注册或者两次密码不一致或者您输入不完整！"),QMessageBox::Yes);
        ui->lineEditPhoneInput->clear();//清空用户编辑框
        ui->lineEditPhoneInput_2->clear();
        ui->lineEditPhoneInput_3->clear();
        ui->lineEditPhoneInput_4->clear();
        ui->lineEditPhoneInput_5->clear();
        ui->lineEditPhoneInput->setFocus();//设置光标到用户编辑框
    }
    else
    {
        //数据库操作
        QSqlQuery query;
        query.exec("insert into user(username,password,telephone,name,flag,ridingStatus,subsidy) values('"+nick+"','"+pwd1+"','"+tele+"','"+name+"','N','N','0')");
        qDebug()<<query.lastError();
        this->hide();
        emit registeredsignal();
        QMessageBox::information(this,tr("提示："),tr("注册成功！"),QMessageBox::Yes);
    }
}
