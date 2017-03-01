#include "dialogchitietban.h"
#include "ui_dialogchitietban.h"

DialogChiTietBan::DialogChiTietBan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChiTietBan)
{
    ui->setupUi(this);
}

DialogChiTietBan::~DialogChiTietBan()
{
    delete ui;
}
