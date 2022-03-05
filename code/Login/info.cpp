#include "info.h"
#include "ui_info.h"
#include "databasedata.h"
//#include "waitingcar.cpp"  //等待上车界面
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QSqlQuery>
info::info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
}

info::~info()
{
    delete ui;
}

void info::acceptLogin()
{
    //设置车主已接单页面显示信息
    ui->label_2->setText(DatabaseData::userName);
    ui->label_4->setText(DatabaseData::telePhone);
    this->show();
}

// 点击按钮成为车主按钮，info页面跳转到车主注册页面的槽函数
void info::on_toolButton_3_clicked()
{
    emit registeredcarsignal();
}

// 即时呼叫按钮的处理槽函数
void info::on_toolButton_clicked()
{
    emit instantCall();

}


// 预约呼叫乘车的处理槽函数
void info::on_toolButton_2_clicked()
{
    emit appointCall();
}


