#include "evaluation.h"
#include "ui_evaluation.h"
#include "databasedata.h"
#include "accepted.h"
#include "pay.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


evaluation::evaluation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::evaluation)
{
    ui->setupUi(this);
}

void evaluation::acceptEvaluationSignal()
{
    this->show();
}

/*评价*/
void evaluation::on_submit_clicked()
{
   //当前用户和车主的ID号
   int userId_1 = accepted::currentDriverId;

   int userId_2 = pay::orderId;
   QSqlQuery query;

   // 获取评价分数和评价内容
   QString Evaluation = ui->comboBox->currentText();
   QString Context = ui->textEdit->toPlainText();
   qDebug() << Evaluation << Context;
   qDebug() << userId_1 << userId_2;

   // 更新订单数据  更新多个字段不能使用and来连接，要用是逗号分开
   QString sql = QString("update orders set Evaluation='%1',context='%2' where orderid=%3")
           .arg(Evaluation).arg(Context).arg(userId_2);
   query.exec(sql);
   // 更新subsidy字段
   QString sql_subsidy1 = QString("select subsidy from user where userid = %1").arg(userId_1);
   query.exec(sql_subsidy1);
   while(query.next())
   {
       int subsidy = query.value("subsidy").toInt();
       qDebug() << "评价前的subsidy" << subsidy;

       if("☆" == Evaluation)
       {
           QString sql_1 = QString("update user set user.subsidy = %1 where userid= %2")
                   .arg(subsidy - 8).arg(userId_1);
           query.exec(sql_1);
       }
       else if("☆☆" == Evaluation)
       {
           QString sql_2 = QString("update user set user.subsidy = %1 where userid= %2")
                   .arg(subsidy - 5).arg(userId_1);
           query.exec(sql_2);
       }
       else if("☆☆☆" == Evaluation)
       {
           QString sql_3 = QString("update user set user.subsidy = %1 where userid= %2")
                   .arg(subsidy).arg(userId_1);
           query.exec(sql_3);
       }
       else if("☆☆☆☆" == Evaluation)
       {
           QString sql_4 = QString("update user set user.subsidy = %1 where userid= %2")
                   .arg(subsidy + 5).arg(userId_1);
           query.exec(sql_4);
       }
       else
       {
           QString sql_5 = QString("update user set user.subsidy = %1 where userid= %2")
                   .arg(subsidy + 8).arg(userId_1);
           query.exec(sql_5);
       }
   }
   QMessageBox::StandardButton result = QMessageBox::information(NULL,"提示：","评价提交成功，欢迎下次乘坐！");
   if(result==QMessageBox::Ok)
   {
       ui->textEdit->clear();
       //车主点击"Ok"
       this->close();  //关闭当前页面
   }
}

evaluation::~evaluation()
{
    delete ui;
}


