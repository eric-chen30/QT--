#ifndef DATABASEDATA_H
#define DATABASEDATA_H
#include <QString>


class DatabaseData
{
public:
    QString Username;
    QString Password;

    //当前用户的ID号
    static int currentId;
    //当前用户的用户名
    static QString userName;
    //当前用户的手机号
    static QString telePhone;


    static bool VerificationLogin(QString Username,QString Password);
};

#endif // DATABASEDATA_H
