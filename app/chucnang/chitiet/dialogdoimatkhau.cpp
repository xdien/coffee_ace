#include "dialogdoimatkhau.h"
#include "ui_dialogdoimatkhau.h"

DialogDoiMatKhau::DialogDoiMatKhau(QString username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDoiMatKhau)
{
    ui->setupUi(this);
    m_username=username;
}

DialogDoiMatKhau::~DialogDoiMatKhau()
{
    delete ui;
}

void DialogDoiMatKhau::on_buttonBox_accepted()
{
    QScopedPointer<TaiKhoan> taiKhoan;
    taiKhoan.reset(new TaiKhoan());
    if(ui->lineEditNewPass->text() == ui->lineEditRepass->text()){
        if(!taiKhoan->doiMatKhau(m_username,ui->lineEditOldPass->text(),ui->lineEditNewPass->text()))
            QMessageBox::warning(this,"Loi khong the cap nhat mat khau.","Khong the cap nhat mat khau luc nay. xin kiem tra lai sau ",QMessageBox::NoButton,QMessageBox::Ok);
        else{
            this->close();
        }
    }else{
        QMessageBox::warning(this,"Loi","mau khau moi khong khop! Xin kiem tra lai",QMessageBox::Ok,QMessageBox::NoButton);
    }
}
