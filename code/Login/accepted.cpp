#include "accepted.h"
#include "ui_accepted.h"
#include "appointment.h"
#include "databasedata.h"
#include "appinfo.cpp"
#include "instantcall.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

accepted::accepted(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accepted)
{
    ui->setupUi(this);

}

accepted::~accepted()
{
    delete ui;
}

QString accepted::startingPlace;
QString accepted::destination;
QString accepted::carNumber;
QString accepted::carColor;
QString accepted::carType;
int accepted::currentDriverId;

void accepted::acceptReceiveSignal()
{
    //设置车主已接单页面显示信息
    ui->label_3->setText(appointment::startingPlace);
    ui->label_5->setText(appointment::destination);
    ui->label_7->setText(DatabaseData::telePhone);
    ui->label_11->setText("未开始");
    this->show();
    flag = 1;
}

void accepted::acceptReceiveSignal2()
{
    //设置车主已接单页面显示信息
    ui->label_3->setText(instantcall::startingPlace);
    ui->label_5->setText(instantcall::destination);
    ui->label_7->setText(DatabaseData::telePhone);
    ui->label_11->setText("未开始");
    this->show();
    flag = 2;
}

//司机点击乘客已上车按钮
void accepted::on_pushButton_4_clicked()
{
    ui->label_11->setText("正在进行");
    //发送信号
    if(flag == 1)
    {
        startingPlace = appointment::startingPlace;
        destination = appointment::destination;
        carNumber = appointment::carNumber;
        carColor = appointment::carColor;
        carType = appointment::carType;
        currentDriverId = appointment::currentDriverId;
        emit getOnCar();
        emit currentPlace();
    }
    else if(flag == 2)
    {
        startingPlace = instantcall::startingPlace;
        destination = instantcall::destination;
        carNumber = instantcall::carNumber;
        carColor = instantcall::carColor;
        carType = instantcall::carType;
        currentDriverId = instantcall::currentDriverId;
        emit getOnCar();
        emit currentPlace();
    }
    else
    {
        qDebug()<<"flag未赋值！！"<<endl;
    }

}

//司机点击乘客已下车按钮
void accepted::on_pushButton_3_clicked()
{

    QSqlQuery query;
    //用户下车后，更新车辆和用户状态 （忙碌-->空闲  Y-->N
    QString sql_one = QString("update car set carStatus='空闲' where userid=%1").arg(currentDriverId);
    QString sql_two = QString("update user set ridingStatus='N' where userid=%1").arg(DatabaseData::currentId);
    query.exec(sql_one);
    query.exec(sql_two);

    // 将carRealTimePlace改为目的地地点    (此处需要获取到车辆的目的地信息，也就是destination字段)
    QString Sql_three = QString("update car set carRealTimePlace = '%1' where userid = %2")
            .arg(destination).arg(currentDriverId);
    query.exec(Sql_three);
    qDebug() << query.lastError();

    // 修改当前的numberOfOrders
    QString sql0 = QString("update car set numberOfOrders=numberOfOrders+1 where userid=%1").arg(currentDriverId);
    query.exec(sql0);

    this->close();
    emit paySingal();
}
