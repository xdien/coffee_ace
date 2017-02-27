#include "otaikhoan.h"

OTaiKhoan::OTaiKhoan(QObject *parent) : QObject(parent)
{
    coQuyen = new QStandardItemModel();
}

OTaiKhoan::~OTaiKhoan()
{
    delete coQuyen;
}

QString OTaiKhoan::getGioiTinh()
{
    if(gioiTinh){
        return "true";
    }else{
        return "false";
    }
}

void OTaiKhoan::setGioiTinh(bool gt)
{
    gioiTinh = gt;
}

