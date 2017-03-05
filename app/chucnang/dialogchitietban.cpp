#include "dialogchitietban.h"
#include "ui_dialogchitietban.h"

DialogChiTietBan::DialogChiTietBan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChiTietBan)
{
    ui->setupUi(this);
    hangHoaModel = new QSqlQueryModel();
    complete = new QCompleter();
    hangHoaModel->setQuery("select * from HANG_HOA");
    complete->setModel(hangHoaModel);

    ui->lineEditTenHang->setCompleter(complete);
    //complete->currentIndex().row()
    danhSachHangModel = new QStandardItemModel();
    ui->tableView->setModel(danhSachHangModel);
}

DialogChiTietBan::~DialogChiTietBan()
{
    delete ui;
    delete complete;
    delete danhSachHangModel;
    delete hangHoaModel;
}
QList<QStandardItem *> DialogChiTietBan::add(const QString hangHoaID,
                                          const QString ten,
                                             const int soLuong,
                                             const int donGia,
                                             const int tongTien,
                                             const bool daThanhToan)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(hangHoaID);
    rowItems << new QStandardItem(ten);
    rowItems << new QStandardItem(soLuong);
    rowItems << new QStandardItem(donGia);
    rowItems << new QStandardItem(tongTien);
    rowItems << new QStandardItem(daThanhToan);
    return rowItems;
}
void DialogChiTietBan::on_pushButton_4_released()
{
    danhSachHangModel->appendRow(add(ui->lineEditMaHang->text(),
                                     ui->lineEditTenHang->text(),
                                     ui->spinBoxSoluong->value(),
                                     ui->spinBoxDonGia->value(),
                                     ui->spinBoxSoTien->value(),
                                     false));
}
