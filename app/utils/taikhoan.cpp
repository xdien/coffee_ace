#include "taikhoan.h"

TaiKhoan::TaiKhoan(QObject *parent) : QObject(parent)
{

}

TaiKhoan::~TaiKhoan()
{
    qDebug() << "Xoa doi tuong taikhoan";
}

bool TaiKhoan::themTaiKhoan()
{
    QSqlQuery query;
    query.prepare("INSERT INTO TAI_KHOAN (USERNAME, PASSWORD, TEN_NV, GIOI_TINH,DIA_CHI_NV) "
                  "VALUES (:userName,:password,:tenNv,:gioiTinh,:diaChiNv)");
    query.bindValue(":userName",userName);
    query.bindValue(":password",password);
    query.bindValue(":tenNv",tenNv);
    query.bindValue(":gioiTinh",gioiTinh);
    query.bindValue(":diaChiNv",diaChiNv);

    if(query.exec()){
        return true;
    }else{
        qDebug() <<"Khong the tao tai khoan: "<< query.lastError().text();
        return false;
    }
}

QList<QString> TaiKhoan::layIDDangNhapHienTai()
{
    QSqlDatabase db = QSqlDatabase::database(M_NAME_SQLITE,true);
    db.setDatabaseName("app.log");
    QList<QString> list;
    if(db.open()){
        QSqlQuery query(db);
        query.exec("select username,thoi_gian,ten from dang_nhap ORDER BY thoi_gian desc");
        if(query.next()){
            list<<  query.value(0).toString();
            list<<query.value(2).toString();
            db.close();
            return list;
        }else{
            db.close();
            return list;
        }
    }else{
        qDebug() << "Chu mo ket noi sqlite!";
        return list;
    }
}

bool TaiKhoan::dangNhap(const QString userName, const QString pass)
{
    /*Mo ket noi sqlite*/
    QSqlDatabase db = QSqlDatabase::database(M_NAME_SQLITE);
    if(!db.isOpen())
        db = QSqlDatabase::addDatabase("QSQLITE",M_NAME_SQLITE);
    db.setDatabaseName("app.log");
    if(db.open()){
        QSqlQuery queryl(db);
        queryl.exec("create table if not exists  dang_nhap (id INTEGER PRIMARY KEY AUTOINCREMENT,username varchar(30) not null,ten TEXT, "
                       "thoi_gian TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL)");
        QSqlQuery query;
        query.exec("select TAI_KHOAN.USERNAME,TEN_NV,COQUYEN from TAI_KHOAN right join THUOC_NHOM"
                   " on THUOC_NHOM.USERNAME = TAI_KHOAN.USERNAME right join NHOM_QUYEN"
                   " on NHOM_QUYEN.NHOMQUYENID = THUOC_NHOM.NHOMQUYENID where PASSWORD = '"+pass+"' and TAI_KHOAN.USERNAME = '"+userName+"'");
        if(query.next()){
            queryl.exec("insert into dang_nhap(username,ten) values('"+userName+"','"+query.value("TEN_NV").toString()+"')");
            //chuyen tat ca gia tri coquyen thanh json
            query.previous();
            Common::coQuyen.reset(new QJsonArray);
            while (query.next()) {
                QSharedPointer<QJsonObject> obj(new QJsonObject(QJsonDocument::fromJson(query.value(2).toByteArray()).object()));
                Common::coQuyen->append(*obj.data());
            }
            emit thongBaoDangNhap("Dang nhap thanh cong", query.value(1).toString());

            db.close();
            return true;
        }else{
            qDebug() << "Login failed" << query.lastError().text();
            db.removeDatabase(M_NAME_SQLITE);
            db.close();
            return false;
        }
    }else{
        qDebug() << "KHong the ket noi toi sqlite: "<<db.lastError().text();
        return false;
    }

}

bool TaiKhoan::doiMatKhau(QString username, const QString &oldPass, const QString &newPass)
{
    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare("update TAI_KHOAN set PASSWORD = :newPass where PASSWORD = :oldPass and USERNAME=:username");
    query.bindValue(":oldPass",oldPass);
    query.bindValue(":newPass",newPass);
    query.bindValue(":username",username);
    if(query.execBatch()){
        return true;
    }else{
        qDebug() << "Khong the thay doi mat khau: " << query.lastError().text();
        return false;
    }
}

bool TaiKhoan::xoa(const QString userName)
{
    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare("delete from TAI_KHOAN where USERNAME=:userName");
    query.bindValue(":userName",userName);
    ///TODO giai quyet cho nay luon return true trong moi truong hop do ham delete luon dung
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Khong the thay doi mat khau: " << query.lastError().text();
        return false;
    }
}

QString TaiKhoan::standarModelToStrJson(const QStandardItemModel *model)
{
    int soDong;
    QJsonArray ar;
    soDong = model->rowCount();
    for(int i = 0;i < soDong; i++){
        QJsonObject dongDuLieuJSON;
        dongDuLieuJSON["ten_thuoc"] = model->index(i,0).data().toString();
        dongDuLieuJSON["ten_ncc"] = model->index(i,1).data().toString();
        dongDuLieuJSON["ten_nsx"] = model->index(i,2).data().toString();
        dongDuLieuJSON["ma_ncc"] = model->index(i,3).data().toString();
        dongDuLieuJSON["ma_nsx"] = model->index(i,4).data().toString();
        ar.append(dongDuLieuJSON);
    }
    QJsonDocument doc(ar);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson;
}
