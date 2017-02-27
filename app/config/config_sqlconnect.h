#ifndef CONFIG_SQLCONNECT_H
#define CONFIG_SQLCONNECT_H
#include <QtSql>
#include <assert.h>


class config_sqlconnect
{
public:

    //khai bao bien chung
    QString nameconnect;//khai bao ten ket noi
    QSqlDatabase db;
    config_sqlconnect();
    //funtion connect to sqlserver;
    void connectsql();
    void disconnectsql();
};

#endif // CONFIG_SQLCONNECT_H
