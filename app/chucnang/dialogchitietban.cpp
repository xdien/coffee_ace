#include "dialogchitietban.h"
#include "ui_dialogchitietban.h"

DialogChiTietBan::DialogChiTietBan(QString banid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChiTietBan)
{
    ui->setupUi(this);
    ban = new Ban();
    phieuXuat = new PhieuXuat(this);
    m_banid = banid;
    ban->layThongTinBan(banid);
    tenhangHoaModel = new QSqlQueryModel();
    idhangHoaModel = new QSqlQueryModel();
    tenComplete = new QCompleter();
    idComplete = new QCompleter();
    tenhangHoaModel->setQuery("select TEN,HANGHOAID,GIA_BAN from HANG_HOA");
    idhangHoaModel->setQuery("select HANGHOAID,TEN,GIA_BAN from HANG_HOA");
    tenComplete->setModel(tenhangHoaModel);
    idComplete->setModel(idhangHoaModel);
    ui->lineEditTenHang->setCompleter(tenComplete);
    ui->lineEditMaHang->setCompleter(idComplete);
    //ket noi voi QCompleter de lay du lieu can thiet
    connect(tenComplete,SIGNAL(activated(QModelIndex)),this,SLOT(layGiaTriTuTenQCompleter(QModelIndex)));
    connect(idComplete,SIGNAL(activated(QModelIndex)),this,SLOT(layGiaTriTuIdQCompleter(QModelIndex)));
    //complete->currentIndex().row()
    danhSachHangModel = new QStandardItemModel();
    ui->tableView->setModel(danhSachHangModel);
    //kiem tra xem ban do co pc hay khong
    query.clear();
    if(ban->idPhieuXuatHt !=""){
        //lay thong tin phieu xuat
        ui->pushButtonVaoban->setText("Rời bàn");

    }
}

DialogChiTietBan::~DialogChiTietBan()
{
    delete ui;
    delete tenComplete;
    delete idComplete;
    delete danhSachHangModel;
    delete tenhangHoaModel;
    delete idhangHoaModel;
    delete ban;
}
QList<QStandardItem *> DialogChiTietBan::add(const QString hangHoaID,
                                          const QString ten,
                                             const QString soLuong,
                                             const QString donGia,
                                             const QString tongTien,
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
                                     QString::number(ui->spinBoxSoluong->value()),
                                      QString::number(ui->spinBoxDonGia->value()),
                                     QString::number( ui->spinBoxSoTien->value()),
                                     false));
}

void DialogChiTietBan::on_pushButtonVaoban_clicked()
{
    if(ban->idPhieuXuatHt == ""){
    phieuXuat->tongTien = ui->spinBoxTongSoTien->value();
    phieuXuat->chiecKhau = ui->doubleSpinBoxChiecKhau->value();
    phieuXuat->daThanhToan = false;
    phieuXuat->gioVao = QTime::currentTime().toString("H:m:s");
    if(!phieuXuat->taoPhieu(m_banid))
        QMessageBox::warning(this,"Lỗi không thêm phiếu","Không thể thêm phiếu xuất lúc này, bạn hãy tắt chương trình rồi mở lại or kiểm tra mạng",QMessageBox::Ok,QMessageBox::NoButton);
    }else{
        //cap nhat lai pc or roi ban

    }
}

void DialogChiTietBan::layGiaTriTuIdQCompleter(const QModelIndex index)
{
    //setdongia cho spinbox
    ui->spinBoxDonGia->setValue(idhangHoaModel->index(index.row(),2).data().toInt());
    ui->lineEditTenHang->setText(idhangHoaModel->index(index.row(),1).data().toString());
}

void DialogChiTietBan::layGiaTriTuTenQCompleter(const QModelIndex index)
{
    ui->spinBoxDonGia->setValue(tenhangHoaModel->index(index.row(),2).data().toInt());
    ui->lineEditTenHang->setText(tenhangHoaModel->index(index.row(),1).data().toString());
}

void DialogChiTietBan::on_spinBoxSoluong_valueChanged(int arg1)
{
    ui->spinBoxSoTien->setValue(arg1 * ui->spinBoxDonGia->value());
}

void DialogChiTietBan::on_spinBoxDonGia_valueChanged(int arg1)
{
    ui->spinBoxSoTien->setValue(arg1 * ui->spinBoxSoluong->value());
}

void DialogChiTietBan::on_pushButton_4_clicked()
{

}
