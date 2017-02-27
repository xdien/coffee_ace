#ifndef TAIKHOAN_H
#define TAIKHOAN_H

#include <QObject>
#include "Objects/otaikhoan.h"
#include <QSqlQuery>
#include "utils/manageindex.h"
#include "config/common.h"
#define M_NAME_SQLITE "sqlite"

class TaiKhoan : public QObject
{
    Q_OBJECT
public:
    explicit TaiKhoan(QObject *parent = 0);
    ~TaiKhoan();
    bool themTaiKhoan();
    QList<QString> layIDDangNhapHienTai();
    bool dangNhap(const QString userName, const QString pass);
    bool doiMatKhau(QString username, const QString &oldPass, const QString &newPass);
    bool xoa(const QString userName);
    QString userName;
    QString password;
    QString tenNv;
    bool gioiTinh;
    QString diaChiNv;
signals:
    void thongBaoDangNhap(QString str, QString tenNV);
private:
    QString standarModelToStrJson(const QStandardItemModel *model);
signals:

public slots:
};

#endif // TAIKHOAN_H
