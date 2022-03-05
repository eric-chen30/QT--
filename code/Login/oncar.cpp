#include "oncar.h"
#include "ui_oncar.h"
#include "appointment.h"
#include "appinfo.h"
#include "instantcall.h"
#include "accepted.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>

oncar::oncar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::oncar)
{
    ui->setupUi(this);

}

oncar::~oncar()
{
    delete ui;
}

double oncar::distance;

void oncar::acceptgetOnCar()
{
    emit closeAppinfo();
    ui->label_9->setText(accepted::carNumber);
    ui->label_10->setText(accepted::carColor);
    ui->label_11->setText(accepted::carType);
    ui->label_12->setText(accepted::destination);
    this->show();
}

void oncar::acceptCurrentPlace()
{
    QString startingPlace = accepted::startingPlace;
    QString destination = accepted::destination;

    QSqlQuery query;
    QString sql = QString("select distance from place where startingPlace='%1' and destination='%2'").arg(startingPlace).arg(destination);
    query.exec(sql);
    if(query.next())
    {
        distance = query.value("distance").toDouble();
    }

    qDebug() << distance;    // 两地距离


    //设置一个定时器，每隔一段时间对距离进行一个更改  比如：每隔一秒，distFromDesination = distFromDesination - 2
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setText(QString::number(distance));

    timer = new QTimer();

    timer->setProperty("property", distance);   // 将查询的两地距离distance通过这个函数传递到槽函数

    // singal的参数必须和slot参数要一致   QPrivateSignal私有信号是被动的，不能由用户发射
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDist()));

    timer->start(2000);     //设置时间间隔为2000毫秒
}

// 定时器触发的槽函数   1.要求dist为查询获取的两地的距离（如何传进来:timer->setProperty("property", dist_int);）   2.当dist降低到一定程度后，我们需要提示用户的同时，将定时器stop
void oncar::updateDist()
{
    // 问题：每次都会获取并初始化一次
    QString dist = sender()->property("property").toString();  // 获取保存的distance值

    qint16 dist_int = dist.toInt();

    if(dist_int > 100)
    {
        dist_int = dist_int - 100;
        ui->lineEdit->setText(QString::number(dist_int));
        timer->setProperty("property", dist_int);
    }else
    {
        QMessageBox::information(this, "提示", "您已到达目的地附近，请携带好您的随身物品，准备下车!");
        timer->stop();
    }

}

