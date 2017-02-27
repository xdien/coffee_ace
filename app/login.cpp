#include "login.h"
#include "ui_login.h"
#include <QtSql>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    taiKhoan = new TaiKhoan();
}

login::~login()
{
    delete ui;
    delete taiKhoan;
}

void login::on_buttonBox_accepted()
{
    if(taiKhoan->dangNhap(ui->user->text(),ui->password->text())){
        emit nvdangnhap(ui->user->text());
    }

    qDebug() << taiKhoan->layIDDangNhapHienTai();
}
