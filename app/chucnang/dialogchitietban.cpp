#include "dialogchitietban.h"
#include "ui_dialogchitietban.h"

DialogChiTietBan::DialogChiTietBan(QString banid, PhieuXuat *phieuXuatModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChiTietBan)
{
    ui->setupUi(this);
    ban = new Ban();
    phieuXuat = phieuXuatModel;
    action_xoa = new QAction(this);
    action_xoa->setText("Xóa");
    contextMenu.reset(new QMenu());
    contextMenu->addAction(action_xoa);
    ui->tableView->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    //ui->tableView->verticalHeader()->setContextMenuPolicy(Qt::ContextMenuPolicy);
    connect(ui->tableView->verticalHeader(),SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customMenuRequested(QPoint)));
    connect(action_xoa,SIGNAL(triggered(bool)),this,SLOT(xoaMotMatHang()));
    m_banid = banid;
    ban->layThongTinBan(banid);
    tenhangHoaModel = new QSqlQueryModel();
    idhangHoaModel = new QSqlQueryModel();
    chiTietPhieuXuat = new ChiTietPhieuXuat();
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
    connect(danhSachHangModel,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(tinhTongTienHangChuaTT()));
    if(query.exec("SELECT PHIEUXUATID,HANGHOAID,SO_LUONG,CHIEC_KHAU,TONG_TIEN,TEN_HANG,GIA_BAN_HIEN_TAI,DA_THANH_TOAN "
               "FROM CHI_TIET_PHIEU_XUAT where PHIEUXUATID = '"+ban->idPhieuXuatHt+"'"))
        while(query.next()){
            danhSachHangModel->appendRow(add(query.value("HANGHOAID").toString(),
                                             query.value("TEN_HANG").toString(),
                                             query.value("SO_LUONG").toString(),
                                             query.value("GIA_BAN_HIEN_TAI").toString(),
                                             query.value("TONG_TIEN").toString(),
                                             query.value("DA_THANH_TOAN").toString()));
        }
    connect(danhSachHangModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(tinhTongTienHangChuaTT()));
    connect(danhSachHangModel,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(tinhTongTienHangChuaTT()));
    connect(danhSachHangModel,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(tinhTongTienHangChuaTT()));
    connect(danhSachHangModel,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(themMoiMatHang()));
    connect(danhSachHangModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(capNhatMatHang()));

    ui->spinBoxSoTienDaTra->setValue(ban->traTruoc);
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
    delete chiTietPhieuXuat;
    delete action_xoa;
}
QList<QStandardItem *> DialogChiTietBan::add(const QString hangHoaID,
                                          const QString ten,
                                             const QString soLuong,
                                             const QString donGia,
                                             const QString tongTien,
                                             const QString daThanhToan)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(hangHoaID);//0
    rowItems << new QStandardItem(ten);//1
    rowItems << new QStandardItem(soLuong);//2
    rowItems << new QStandardItem(donGia);//3
    rowItems << new QStandardItem(tongTien);//4
    rowItems << new QStandardItem(daThanhToan);//5
    return rowItems;
}
void DialogChiTietBan::on_pushButton_4_released()
{
    int index = Common::findIndex(danhSachHangModel,ui->lineEditMaHang->text(),0);
    if( index == -1){
    danhSachHangModel->appendRow(add(ui->lineEditMaHang->text(),
                                     ui->lineEditTenHang->text(),
                                     QString::number(ui->spinBoxSoluong->value()),
                                      QString::number(ui->spinBoxDonGia->value()),
                                     QString::number( ui->spinBoxSoTien->value()),
                                     "0"));
    }else{
        //cong so luong hang
        int soLuongHT,soTienHt,donGia;
        soLuongHT = danhSachHangModel->index(index,2).data().toInt();
        donGia =  danhSachHangModel->index(index,3).data().toInt();
        soLuongHT+= ui->spinBoxSoluong->value();
        soTienHt = soLuongHT*donGia;
        danhSachHangModel->item(index,2)->setData(QVariant(soLuongHT),Qt::EditRole);
        danhSachHangModel->item(index,4)->setData(QVariant(soTienHt),Qt::EditRole);//so tien
    }

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
        else{
            ban->idPhieuXuatHt = phieuXuat->phieuXuatID;
            themMoiMatHang();
            setWindowTitle(ban->ten + " có khách");
            ui->pushButtonVaoban->setText("Roi ban");
            this->done(0);

        }

    }else{
        //cap nhat lai pc or roi ban
        qDebug() << "Cap nhat phieu xuat or roi ban";
        phieuXuat->chiecKhau = ui->doubleSpinBoxChiecKhau->value();
        phieuXuat->tongTien = ui->spinBoxTongSoTien->value();
        if(phieuXuat->roiBan(ban->idPhieuXuatHt,false)){
            ui->pushButtonVaoban->setText("Vao Ban");
            danhSachHangModel->clear();
            ui->spinBoxDonGia->setValue(0);
            ui->spinBoxSoluong->setValue(0);
            ui->spinBoxSoTien->setValue(0);
            ui->spinBoxSoTienChieckhau->setValue(0);
            ui->spinBoxSoTienConTra->setValue(0);
            ui->spinBoxSoTienDaTra->setValue(0);
            ui->spinBoxTongSoTienTruocCK->setValue(0);
            ui->doubleSpinBoxChiecKhau->setValue(0);
            ui->lineEditMaHang->setText("");
            ui->lineEditTenHang->setText("");
            setWindowTitle(ban->ten + " đang trống");
            this->done(0);
        }
        else
            QMessageBox::warning(this,"Lỗi roi ban","Khong the thao tac nay, bạn hãy tắt chương trình rồi mở lại or kiểm tra mạng",QMessageBox::Ok,QMessageBox::NoButton);

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
    ui->lineEditMaHang->setText(tenhangHoaModel->index(index.row(),1).data().toString());
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

void DialogChiTietBan::tinhTongTienHangChuaTT()
{
    tongTienChuaThanhToan = 0;
    //soTienDaTra = 0;
    //chay vong lap for cho den het danh sach hang
    for (int i = 0; i < danhSachHangModel->rowCount(); ++i) {
        if(!danhSachHangModel->index(i,5).data().toBool())
            tongTienChuaThanhToan += danhSachHangModel->index(i,4).data().toInt();
        else
            soTienDaTra += danhSachHangModel->index(i,4).data().toInt();
    }
    ui->spinBoxSoTienConTra->setValue(tongTienChuaThanhToan);
    //ui->spinBoxSoTienDaTra->setValue(soTienDaTra);
}

void DialogChiTietBan::on_doubleSpinBoxChiecKhau_valueChanged(double arg1)
{
    ui->spinBoxSoTienChieckhau->setValue(arg1 * ui->spinBoxSoTienConTra->value()/100);
}

void DialogChiTietBan::on_spinBoxSoTienDaTra_valueChanged(int arg1)
{
    ui->spinBoxTongSoTienTruocCK->setValue( ui->spinBoxSoTienConTra->value() - arg1);

}

void DialogChiTietBan::on_spinBoxSoTienConTra_valueChanged(int arg1)
{
    ui->spinBoxTongSoTienTruocCK->setValue(arg1 + ui->spinBoxSoTienDaTra->value());
}

void DialogChiTietBan::on_spinBoxSoTienChieckhau_valueChanged(int arg1)
{
    ui->spinBoxTongSoTien->setValue(ui->spinBoxTongSoTienTruocCK->value() - arg1);
}

void DialogChiTietBan::on_spinBoxTongSoTienTruocCK_valueChanged(int arg1)
{
    ui->spinBoxTongSoTien->setValue(arg1 - ui->spinBoxSoTienChieckhau->value());
}

void DialogChiTietBan::themMoiMatHang()
{
    //chay vong lap for
    for (int i = 0; i < danhSachHangModel->rowCount(); ++i) {
        //chiTietPhieuXuat = phieuXuat->chiTietPhieuXuat;
        chiTietPhieuXuat->banid = ban->banID;
        chiTietPhieuXuat->daThanhToan = false;
        chiTietPhieuXuat->giaBanHienTai = danhSachHangModel->index(i,3).data().toInt();
        chiTietPhieuXuat->hanghoaid = danhSachHangModel->index(i,0).data().toString();
        chiTietPhieuXuat->pcid = ban->idPhieuXuatHt;
        chiTietPhieuXuat->soLuong = danhSachHangModel->index(i,2).data().toInt();
        chiTietPhieuXuat->tenHang = danhSachHangModel->index(i,1).data().toString();
        chiTietPhieuXuat->tongTien = danhSachHangModel->index(i,4).data().toInt();
        chiTietPhieuXuat->insert();
    }
}

void DialogChiTietBan::capNhatMatHang()
{
    for (int i = 0; i < danhSachHangModel->rowCount(); ++i) {
        //chiTietPhieuXuat = phieuXuat->chiTietPhieuXuat;
        chiTietPhieuXuat->banid = ban->banID;
        chiTietPhieuXuat->daThanhToan = danhSachHangModel->index(i,5).data().toBool();
        chiTietPhieuXuat->giaBanHienTai = danhSachHangModel->index(i,3).data().toInt();
        chiTietPhieuXuat->hanghoaid = danhSachHangModel->index(i,0).data().toString();
        chiTietPhieuXuat->pcid = ban->idPhieuXuatHt;
        chiTietPhieuXuat->soLuong = danhSachHangModel->index(i,2).data().toInt();
        chiTietPhieuXuat->tenHang = danhSachHangModel->index(i,1).data().toString();
        chiTietPhieuXuat->tongTien = danhSachHangModel->index(i,4).data().toInt();
        chiTietPhieuXuat->capNhat();
    }
}
void DialogChiTietBan::customMenuRequested(QPoint pos)
{
    contextMenu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void DialogChiTietBan::xoaMotMatHang()
{
    if(chiTietPhieuXuat->xoa(ban->idPhieuXuatHt,danhSachHangModel->index(ui->tableView->currentIndex().row(),0).data().toString())){
        danhSachHangModel->removeRow(ui->tableView->currentIndex().row());
    }
}

void DialogChiTietBan::on_spinBoxSoTienDaTra_editingFinished()
{
    phieuXuat->traTruoc = ui->spinBoxSoTienDaTra->value();
    if(phieuXuat->capNhatSoTienTraTruoc(ban->idPhieuXuatHt)){

    }else{
        QMessageBox::warning(this,"Loi cap nhat","Không thể cập nhật số tiền trả trước lúc này xin thử lại or kiểm tra mạng",QMessageBox::Ok,QMessageBox::NoButton);
    }
}

void DialogChiTietBan::on_pushButton_3_clicked()
{
    phieuXuat->inBill(ban->idPhieuXuatHt);
}
