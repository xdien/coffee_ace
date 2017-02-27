#include "quyen.h"

Quyen::Quyen(QObject *parent) : QObject(parent)
{
    query = new QSqlQuery();
}

Quyen::~Quyen()
{
    delete query;
}

bool Quyen::themQuyen()
{

    query->prepare("INSERT INTO NHOM_QUYEN (MO_TA,COQUYEN) "
                  "VALUES (:moTa,:cacQuyen)");
    //query->bindValue(":nhomQuyenId",nhomQuyenId);
    query->bindValue(":moTa",moTa);
    query->bindValue(":cacQuyen",coQuyen);
    if (query->exec()) {
        return true;
    }else{
        qDebug() << "Khong the them nhom quyen moi : "<< query->lastError().text();
         return false;
    }
}

QSqlQueryModel *Quyen::layQuyen(QString username)
{
    QSqlQueryModel *quye = new QSqlQueryModel();
    quye->setQuery("select xem from QUYEN where username = '"+username+"'");
    return quye;
}

bool Quyen::update(const int quyenid)
{
    query->clear();
    query->prepare("update NHOM_QUYEN set MO_TA=:moTa,COQUYEN=:coQuyen where NHOMQUYENID = :nhomQuyenId");
    query->bindValue(":nhomQuyenId",quyenid);
    query->bindValue(":coQuyen",coQuyen);
    query->bindValue(":moTa",moTa);
    if(query->exec()){
        return true;
    }else{
        qDebug() << "Khong the cap nhat nhom quyen: "<< query->lastError().text();
        return false;
    }
}
