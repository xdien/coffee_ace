#include "dialognhomquyen.h"
#include "ui_dialognhomquyen.h"

DialogNhomQuyen::DialogNhomQuyen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNhomQuyen)
{
    ui->setupUi(this);
}

DialogNhomQuyen::~DialogNhomQuyen()
{
    delete ui;
}
