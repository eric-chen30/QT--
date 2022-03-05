#include "carregister.h"
#include "ui_carregister.h"
#include "carcheck.h"
#include "databasedata.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QSqlError>


carRegister::carRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::carRegister)
{
    ui->setupUi(this);
}

carRegister::~carRegister()
{
    delete ui;
}

void carRegister::acceptrecargister()
{
    this->show();
}

// 点击确定按钮，carresgister车主注册页面跳转到carinfo车主信息页面
void carRegister::on_toolButton_clicked()
{
    QString carNumber =ui->lineEditPhoneInput->text().trimmed();
    QString carColor =ui->lineEditPhoneInput_2->text().trimmed();
    QString carType =ui->lineEditPhoneInput_3->text().trimmed();
    carcheck carnumber;

    if(carnumber.checkin(carNumber)||carNumber.isEmpty()||carColor.isEmpty()||carType.isEmpty())
    {
        //注册失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
        QMessageBox::warning(this,tr("警告！"),tr("此车已注册或您填写不完整！"),QMessageBox::Yes);
        ui->lineEditPhoneInput->clear();//清空用户编辑框
        ui->lineEditPhoneInput_2->clear();
        ui->lineEditPhoneInput_3->clear();
        ui->lineEditPhoneInput->setFocus();//设置光标到用户编辑框
    }
    else
    {
        //数据库操作
        QSqlQuery query;
        if(query.exec("SELECT * FROM user"))
        {   while(query.next())
            {   if(query.value(0).toInt()==DatabaseData::currentId)
               {
                    QString sqlquery=QString("insert into car(userid,carNumber,carColor,carType,carRealTimePlace,carStatus,numberOfOrders) values(%1,'%2','%3','%4','A地','空闲','0')").arg(DatabaseData::currentId).arg(carNumber).arg(carColor).arg(carType);
                    QString sqlquery1=QString("update user set flag='Y' where userid=%1").arg(DatabaseData::currentId);
                    query.exec(sqlquery);
                    query.exec(sqlquery1);
                    qDebug()<<query.lastError();
                    this->hide();
                    emit registeredsignal2();
                    QMessageBox::information(this,tr("提示："),tr("注册成功！"),QMessageBox::Yes);
                }
            }
        }
    }
}
