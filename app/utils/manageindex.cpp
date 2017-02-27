#include "manageindex.h"

ManageIndex::ManageIndex()
{
    num_prefix = "00000000";
}

ManageIndex::~ManageIndex()
{
}

QString ManageIndex::getNextIndexCode(const QString tableName, const QString prefix)
{
    num_prefix = "00000";
    if(!query.exec("select * from "+tableName+" order by 1 desc limit 1")){
       qDebug() << "khong the truy van den bang de tao index " << query.lastError().text();
    }

    if(query.next())
    {
        //lay ma ra, tach so , tang so len 1 va gop so do voi prefix
        index_code = query.value(0).toString();
        idx = index_code.mid(prefix.length()).toInt();
        idx = idx +1;
        str_num = QString::number(idx);//doi thanh string lay so ky tu
        index_code = prefix +num_prefix.mid(str_num.length())+str_num;
    }else{
        str_num = "1";
        index_code = prefix +num_prefix.mid(str_num.length())+str_num;
    }
    return index_code;
}

QString ManageIndex::getNextIndexCode(const QString tableName)
{
    query.exec("select * from "+tableName+" order by 1 desc limit 1");
    if(query.next())
    {
        //lay ma ra, tach so , tang so len 1 va gop so do voi prefix
        return QString::number(query.value(0).toInt() + 1);
    }else{
        return "0";
    }
    return NULL;
}

QString ManageIndex::getNextIndexCode(const QString tableName, const QString prefix, const QString columeName)
{
    num_prefix = "00000";
    query.exec("select "+columeName+" from "+tableName+" order by 1 desc limit 1");
    if(query.next())
    {
        //lay ma ra, tach so , tang so len 1 va gop so do voi prefix
        index_code = query.value(0).toString();
        idx = index_code.mid(prefix.length()).toDouble();
        idx = idx +1;
        str_num = QString::number(idx);//doi thanh string lay so ky tu
        index_code = prefix +""+num_prefix.mid(str_num.length())+str_num;
    }else{
        str_num = "0";
        index_code = prefix +""+num_prefix.mid(str_num.length())+str_num;
    }
    return index_code;
}
