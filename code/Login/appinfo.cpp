#include "appinfo.h"
#include "ui_appinfo.h"
#include "appointment.h"
#include "instantcall.h"

appinfo::appinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appinfo)
{
    ui->setupUi(this);
}

appinfo::~appinfo()
{
    delete ui;
}

void appinfo::acceptWaitingCar()
{
    //设置用户等待上车页面显示信息
    ui->label_6->setText(appointment::carNumber);
    ui->label_7->setText(appointment::userName);
    ui->label_8->setText(appointment::carColor);
    ui->label_9->setText(appointment::carType);
    this->show();    //展示等待上车页面
}

void appinfo::acceptWaitingCar2()
{
    //设置用户等待上车页面显示信息
    ui->label_6->setText(instantcall::carNumber);
    ui->label_7->setText(instantcall::userName);
    ui->label_8->setText(instantcall::carColor);
    ui->label_9->setText(instantcall::carType);
    this->show();    //展示等待上车页面
}
