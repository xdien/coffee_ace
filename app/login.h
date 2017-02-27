#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include "utils/taikhoan.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
signals:
    void nvdangnhap(QString manv);
    void setThongBao(QString thongBao);
private slots:
    void on_buttonBox_accepted();

private:
    QSqlQuery query;
    Ui::login *ui;
    QString ma_nv;
    TaiKhoan *taiKhoan;
};

#endif // LOGIN_H
