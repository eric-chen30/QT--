#include "pay.h"
#include "ui_pay.h"
#include "oncar.h"
#include "accepted.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

pay::pay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pay)
{
    ui->setupUi(this);
}

pay::~pay()
{
    delete ui;
}

int pay::orderId;

void pay::acceptPaySingal()
{
    double distance_km = oncar::distance/1000;
    QString distance = QString::number(distance_km,'f',1);
    ui->label_5->setText(accepted::startingPlace);
    ui->label_6->setText(accepted::destination);
    ui->label_8->setText(distance);

    QSqlQuery query;
    QString sql = QString("select orderid,money from orders order by orderid desc limit 1");
    query.exec(sql);
    if(query.next())
    {
        QString money = QString("支付:" + query.value("money").toString() + "元");
        orderId = query.value("orderid").toInt();
        ui->pushButton->setText(money);
    }
    this->show();
}

void pay::on_pushButton_clicked()
{
    QMessageBox::StandardButton result = QMessageBox::information(NULL,"提示：","支付成功！");
    if(result==QMessageBox::Ok)
    {
        //用户点击"Ok"后，跳转评价界面
        this->close();  //关闭当前页面

        emit evaluationSignal();
    }

}
