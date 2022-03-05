#ifndef CARCHECK_H
#define CARCHECK_H
#include <QSqlDatabase>
#include <QSqlQuery>


//判断车牌号是否已经注册，是则返回true，否false
class carcheck
{
public:

    bool checkin(QString carNumber);
};
bool carcheck::checkin(QString carNumber)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败
    //数据库操作
    QSqlQuery query;//实例一个查询对象;
    {   if(query.exec("SELECT * FROM car where userid >= 0"))
        {   while(query.next())//遍历数据表格每一行，从第0行到最后一行
            {   if(carNumber == query.value(1).toString().trimmed())//trimmed函数表示去除QString两边的空格
                {   return true;}
            }
        }
    }
    return false;
}

#endif // CARCHECK_H
