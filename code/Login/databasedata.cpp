#include "databasedata.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QDebug>

int DatabaseData::currentId;
QString DatabaseData::userName;
QString DatabaseData::telePhone;

bool DatabaseData::VerificationLogin(QString Username,QString Password)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败
    QSqlQuery query;//实例一个查询对象;
    if(query.exec("SELECT * FROM user where userid >= 0"))//代表选择id=3的一行内容
    {
        while(query.next())//遍历数据表格每一行，从第0行到最后一行
        {
            QString tele= query.value("telephone").toString().trimmed();//trimmed函数表示去除QString两边的空格
            QString password=query.value(2).toString().trimmed();
            if((Username.trimmed() == tele)&&(Password == password))
            {
                currentId = query.value("userid").toInt();
                userName = query.value("username").toString();
                telePhone = query.value("telephone").toString();
                qDebug()<<"currentId:"<<currentId<<endl;
                qDebug()<<"userName:"<<userName<<endl;
                qDebug()<<"telePhone:"<<telePhone<<endl;
                return true;
            }
         }
    }
    return false;
}
