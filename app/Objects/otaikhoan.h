#ifndef OTAIKHOAN_H
#define OTAIKHOAN_H

#include <QObject>
#include <QStandardItemModel>

class OTaiKhoan : public QObject
{
    Q_OBJECT
public:
    explicit OTaiKhoan(QObject *parent = 0);
    ~OTaiKhoan();
    QString username,pass,tenNV,diaChi;
    QStandardItemModel *coQuyen;
    QString getGioiTinh();
    void setGioiTinh(bool gt);
signals:

public slots:
private:
    bool gioiTinh;
};

#endif // OTAIKHOAN_H
