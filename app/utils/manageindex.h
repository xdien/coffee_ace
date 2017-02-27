#ifndef MANAGEINDEX_H
#define MANAGEINDEX_H
#include <QtSql>
#include <QDebug>
 #include <QVarLengthArray>

class ManageIndex
{
public:
    ManageIndex();
    ~ManageIndex();
private:
    QSqlQuery query;
    QString table_name, index_code,num_prefix,str_num;
    QVarLengthArray<QString, 10> array;
    qint32 idx;
    //QString prefix;
public:
    void setPrefix(QString Prefix);
    QString getNextIndexCode(const QString tableName, const QString prefix);
    QString getNextIndexCode(const QString tableName);
    QString getNextIndexCode(const QString tableName, const QString prefix, const QString columeName);
};

#endif // MANAGEINDEX_H
