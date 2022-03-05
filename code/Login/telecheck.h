#ifndef TELECHECK_H
#define TELECHECK_H
#include <QSqlDatabase>
#include <QSqlQuery>


//判断手机号是否已经注册，是则返回true，否则返回false
class telecheck
{
public:

    bool checkin(QString tele);
};
bool telecheck::checkin(QString tele)
{
   //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败
   //数据库操作
   QSqlQuery query;//实例一个查询对象;
   if(query.exec("SELECT * FROM user where userid > 0"))
   {
       while(query.next())//遍历数据表格每一行，从第0行到最后一行
       {
           if(tele == query.value(3).toString().trimmed())//trimmed函数表示去除QString两边的空格
           {
               return true;
           }
       }
   }
   return false;
}




#endif // TELECHECK_H

