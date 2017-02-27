#include "config_sqlconnect.h"
#include <QDebug>
#include <QSettings>
config_sqlconnect::config_sqlconnect()
{
}
void config_sqlconnect::connectsql()
{
    //doc file connect,conf va lay du lieu ket noi
    QSettings settings("connect.conf",QSettings::IniFormat);
    settings.beginGroup("Default");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(settings.value("ip").toString());
    db.setUserName(settings.value("user").toString());
    db.setPassword(settings.value("pass").toString());
    db.setDatabaseName(settings.value("db").toString());
    db.setPort(3306);
    qDebug()<<"Connected?:" << db.open();
}

void config_sqlconnect::disconnectsql()
{
    db.close();
}
