#include "instantcall.h"
#include "ui_instantcall.h"
#include "databasedata.cpp"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QSqlQuery>

instantcall::instantcall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instantcall)
{
    ui->setupUi(this);
}

instantcall::~instantcall()
{
    delete ui;
}

void instantcall::acceptInstantCall()
{
    this->show();
}

QString instantcall::startingPlace;
QString instantcall::destination;
QString instantcall::carNumber;
QString instantcall::carColor;
QString instantcall::carType;
QString instantcall::userName;
int instantcall::currentDriverId;

void instantcall::on_submit_clicked()
{
    //前端输入：startingPlace(出发地点),destination(目的地),userId(用户id)
    startingPlace = ui->comboBox_2->currentText();
    destination = ui->comboBox_3->currentText();

    qDebug()<<startingPlace<<destination<<endl;

    //后端返回：carNumber(车牌号),carColor(车辆颜色),ownerName(车主姓名),ownerTelephone(车主电话),
    //         startingTime(出发时间),ownerId(车主id)
    QSqlQuery query;
    QString sql = QString("select u.name,u.telephone,c.userid,c.carNumber,c.carColor,c.carType from user u,car c where u.userid=c.userid and c.carRealTimePlace='%1' and c.carStatus='空闲'").arg(startingPlace);
    query.exec(sql);
    //查询空闲车辆成功
    if(query.next())
    {
        carNumber = query.value("carNumber").toString();
        carColor = query.value("carColor").toString();
        carType = query.value("carType").toString();
        userName = query.value("name").toString();
        currentDriverId = query.value("userid").toInt();
        QMessageBox::StandardButton result = QMessageBox::information(NULL,"提示：","呼叫成功，请尽快前往上车点！");
        if(result==QMessageBox::Ok)
        {
            //车主点击"Ok"后，用户跳转车辆信息界面，输出车辆信息
            this->close();  //关闭当前页面
            emit waitingCar2();   //发送等待上车信号，展示等待上车页面
            emit receiveSignal2();   //发送车主已接单信号，展示车主已接单界面
        }
        //用户上车后，更新车辆和用户状态
        QString sql_1 = QString("update car set carStatus='忙碌' where userid=%1").arg(currentDriverId);
        QString sql_2 = QString("update user set ridingStatus='Y' where userid=%1").arg(DatabaseData::currentId);
        query.exec(sql_1);
        query.exec(sql_2);

        //获取里程，计算订单价格
        QSqlQuery query_1;
        QString sql_3 = QString("select distance from place where startingPlace='%1' and destination='%2'").arg(startingPlace).arg(destination);
        query_1.exec(sql_3);
        //根据上下车地点查询里程成功
        if(query_1.next())
        {
            int discount;
            double distance = query_1.value("distance").toDouble()/1000;
            //根据里程确定优惠价格
            if(distance>0&&distance<=5) //里程小于5公里的无优惠
            {
                discount = 0;
            }
            else if(distance>5&&distance<=10) //里程在5公里到10公里的优惠3元
            {
                discount = 3;
            }
            else //里程大于10公里的优惠5元
            {
                discount = 5;
            }
            //价格以每公里3元计算，还需减去优惠价格
            QString money = QString::number(3*distance-discount,'f',2); //double类型转为QString类型，参数2表示保留两位小数
            //平台按照20%的比例收取运营费用
            QString plat_earning = QString::number((3*distance-discount)*0.2,'f',2);
            //向订单表中插入当前订单信息
            QString sql_4 = QString("insert into orders(userid,money,discount,distance,Evaluation,plat_earning) values(%1,'%2','%3',%4,'0','%5')")
                    .arg(DatabaseData::currentId).arg(money).arg(QString::number(discount,10)).arg(query_1.value("distance").toInt()).arg(plat_earning);
            query_1.exec(sql_4);
        }
        else
        {
            QMessageBox::warning(this,"警告：","地点不在乘车范围内！");
        }
    }
    else
    {
        QMessageBox::warning(this,"提示：","车辆忙碌中，请稍后再试！");
    }
}


