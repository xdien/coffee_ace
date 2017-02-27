#include "formquyen.h"
#include "ui_formquyen.h"

FormQuyen::FormQuyen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormQuyen)
{
    ui->setupUi(this);
    quyen = new Quyen();
    phongBanModel = new QSqlQueryModel();
    chamCongDC = new QStandardItemModel();
    tinhLuongDC = new QStandardItemModel();
    danhSachDC = new QStandardItemModel();
    contextMenuCC.reset(new QMenu());
    contextMenuTL.reset(new QMenu());
    contextMenuDS.reset(new QMenu());
    action_xoaCC = new QAction(this);
    action_xoaDS = new QAction(this);
    action_xoaTL = new QAction(this);
    action_xoaCC->setText("Xóa");
    action_xoaTL->setText("Xóa");
    action_xoaDS->setText("Xóa");
    contextMenuCC->addAction(action_xoaCC);
    contextMenuTL->addAction(action_xoaTL);
    contextMenuDS->addAction(action_xoaDS);
    ui->listViewChamCongCC_CQ->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listViewChamCongTL_CQ->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listViewChamCongDS_CQ->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listViewChamCongCC_CQ,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customMenuRequestedCC(QPoint)));
    connect(ui->listViewChamCongTL_CQ,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customMenuRequestedTL(QPoint)));
    connect(ui->listViewChamCongDS_CQ,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customMenuRequestedDS(QPoint)));
    //ket noi den ham xoa
    connect(action_xoaCC,SIGNAL(triggered(bool)),this,SLOT(xoaCC()));
    connect(action_xoaTL,SIGNAL(triggered(bool)),this,SLOT(xoaTL()));
    connect(action_xoaDS,SIGNAL(triggered(bool)),this,SLOT(xoaDS()));
    setWindowTitle("Quyền ["+QString::fromLatin1(metaObject()->className())+"]");
    phongBanModel->setQuery("select TEN_PHONG_BAN,PHONGBANID from PHONG_BAN");
    ui->listViewPhongBanCC->setModel(phongBanModel);
    ui->listViewPhongBanTL->setModel(phongBanModel);
    ui->listViewPhongBanDS->setModel(phongBanModel);
    ui->listViewChamCongCC_CQ->setModel(chamCongDC);
    ui->listViewChamCongTL_CQ->setModel(tinhLuongDC);
    ui->listViewChamCongDS_CQ->setModel(danhSachDC);
    ui->pushButtonCapNhat->setVisible(false);
}

FormQuyen::~FormQuyen()
{
    delete ui;
    delete phongBanModel;
    delete quyen;
    delete chamCongDC;
    delete tinhLuongDC;
    delete action_xoaCC;
    delete action_xoaDS;
    delete action_xoaTL;
    delete danhSachDC;
}

void FormQuyen::on_pushButton_2_clicked()
{
    layGiaTri();
    if(quyen->themQuyen()){
    //quyen->themQuyen()
    }
}

QList<QStandardItem *> FormQuyen::append(const QString &tenPhongBan,
                                         const QString &phongBanid)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(tenPhongBan);
    rowItems << new QStandardItem(phongBanid);
    return rowItems;
}

void FormQuyen::on_listViewPhongBanCC_doubleClicked(const QModelIndex &index)
{
    if(0 == chamCongDC->findItems(phongBanModel->index(index.row(),1).data().toString(),Qt::MatchExactly,1).length()){
        chamCongDC->appendRow(append(phongBanModel->index(index.row(),0).data().toString(),
                                     phongBanModel->index(index.row(),1).data().toString()));
    }
}

void FormQuyen::on_listViewPhongBanTL_doubleClicked(const QModelIndex &index)
{
    if(0 == tinhLuongDC->findItems(phongBanModel->index(index.row(),1).data().toString(),Qt::MatchExactly,1).length()){
        tinhLuongDC->appendRow(append(phongBanModel->index(index.row(),0).data().toString(),
                                      phongBanModel->index(index.row(),1).data().toString()));
    }
}

void FormQuyen::on_listViewPhongBanDS_doubleClicked(const QModelIndex &index)
{
    if(0 == danhSachDC->findItems(phongBanModel->index(index.row(),1).data().toString(),Qt::MatchExactly,1).length()){
        danhSachDC->appendRow(append(phongBanModel->index(index.row(),0).data().toString(),
                                      phongBanModel->index(index.row(),1).data().toString()));
    }
}
void FormQuyen::customMenuRequestedCC(QPoint pos)
{
    contextMenuCC->popup(ui->listViewChamCongCC_CQ->viewport()->mapToGlobal(pos));
}
void FormQuyen::customMenuRequestedTL(QPoint pos)
{
    contextMenuTL->popup(ui->listViewChamCongTL_CQ->viewport()->mapToGlobal(pos));
}
void FormQuyen::customMenuRequestedDS(QPoint pos)
{
    contextMenuDS->popup(ui->listViewChamCongDS_CQ->viewport()->mapToGlobal(pos));
}

void FormQuyen::xoaCC()
{
    if(chamCongDC->index(ui->listViewChamCongCC_CQ->currentIndex().row(),0).isValid()){
        chamCongDC->removeRow(ui->listViewChamCongCC_CQ->currentIndex().row());
    }
}
void FormQuyen::xoaTL()
{
    if(tinhLuongDC->index(ui->listViewChamCongTL_CQ->currentIndex().row(),0).isValid()){
        tinhLuongDC->removeRow(ui->listViewChamCongTL_CQ->currentIndex().row());
    }
}
void FormQuyen::xoaDS()
{
    if(danhSachDC->index(ui->listViewChamCongDS_CQ->currentIndex().row(),0).isValid()){
        danhSachDC->removeRow(ui->listViewChamCongDS_CQ->currentIndex().row());
    }
}
void FormQuyen::setQuyen(int quyenid)
{
    m_quyenid = quyenid;
    query.clear();
    Q_ASSERT(query.exec("select NHOMQUYENID,COQUYEN,MO_TA from NHOM_QUYEN where NHOMQUYENID = "+QString::number(quyenid)));
    if(query.next()){
        ui->lineEditTen->setText(query.value("MO_TA").toString());
        //tach json
        QJsonDocument doc;
        doc = QJsonDocument::fromJson(query.value("COQUYEN").toByteArray());
        QScopedPointer<QJsonObject> root;
        root.reset(new QJsonObject(doc.object()));
        QScopedPointer<QJsonObject> danhSach;
        danhSach.reset(new QJsonObject(doc.object()["danhSach"].toObject()));
        QScopedPointer<QJsonObject> chamCong;
        chamCong.reset(new QJsonObject(doc.object()["chamCong"].toObject()));
        QScopedPointer<QJsonObject> tinhLuong;
        tinhLuong.reset(new QJsonObject(doc.object()["tinhLuong"].toObject()));
        //
        for (int i = 0; i < danhSach->keys().length(); ++i) {
            QString key = danhSach->keys().at(i);
            danhSachDC->appendRow(append(danhSach->value(key).toString(),key));
        }
        for (int i = 0; i < chamCong->keys().length(); ++i) {
            QString key = chamCong->keys().at(i);
            chamCongDC->appendRow(append(chamCong->value(key).toString(),key));
        }
        for (int i = 0; i < tinhLuong->keys().length(); ++i) {
            QString key = tinhLuong->keys().at(i);
            tinhLuongDC->appendRow(append(tinhLuong->value(key).toString(),key));
        }
        // cac checkbox
        if(root->value(tenquyen::capSo).toBool())
            ui->nvCapSo->setChecked(true);
        if(root->value(tenquyen::traSo).toBool())
            ui->nvTraSo->setChecked(true);
        if(root->value(tenquyen::thayDoiTKNH).toBool())
            ui->nvSTK->setChecked(true);
        if(root->value(tenquyen::taoHD).toBool())
            ui->nvTaoHd->setChecked(true);
        if(root->value(tenquyen::taoHDThuViec).toBool())
            ui->nvTaoThuViec->setChecked(true);
        if(root->value(tenquyen::quyDinhLuong).toBool())
            ui->nvQuyDinhLuong->setChecked(true);
        if(root->value(tenquyen::xemChiTietNV).toBool())
            ui->nvChiTiet->setChecked(true);
        if(root->value(tenquyen::xemSinhNhat).toBool())
            ui->nvXemSN->setChecked(true);
        if(root->value(tenquyen::xemHopDongGanHetHan).toBool())
            ui->nvXemHDganHethan->setChecked(true);

        if(root->value(tenquyen::phanQuyen).toBool())
            ui->phanQuyen->setChecked(true);
        if(root->value(tenquyen::taiKhoan).toBool())
            ui->taoTK->setChecked(true);
        if(root->value(tenquyen::thayDoiTK).toBool())
            ui->thayDoiTTTK->setChecked(true);
        if(root->value(tenquyen::quiDinhHeSo).toBool())
            ui->thietLapHeSo->setChecked(true);
        if(root->value(tenquyen::xemTinhLuong).toBool())
            ui->tlXem->setChecked(true);
        if(root->value(tenquyen::tamUng).toBool())
            ui->nvTamUng->setChecked(true);
        if(root->value(tenquyen::Quyen).toBool())
            ui->mnQuyen->setChecked(true);
        if(root->value(tenquyen::QLTamUng).toBool())
            ui->QLTamung->setChecked(true);
        if(root->value(tenquyen::QLNghiLuu).toBool())
            ui->QLNghiLuu->setChecked(true);
        if(root->value(tenquyen::QLTuyenNV).toBool())
            ui->QLTuyenNV->setChecked(true);
        if(root->value(tenquyen::QLHopDong).toBool())
            ui->QLHopDong->setChecked(true);
        if(root->value(tenquyen::QLThuong).toBool())
            ui->checkBoxThuong->setChecked(true);

        //
        ui->pushButtonCapNhat->setVisible(true);
    }else{

    }

}

void FormQuyen::on_pushButtonCapNhat_clicked()
{
    layGiaTri();//da set moTa va coQuyen trong ham nay
    quyen->update(m_quyenid);
}

void FormQuyen::layGiaTri()
{
    quyen->coQuyen ="";
    quyen->moTa = ui->lineEditTen->text();
    //chuyen QStandardItemModel thanh json {phongbanid : 'ten phong ban'}
    QScopedPointer<QJsonObject> root;
    root.reset(new QJsonObject);
    root->insert(ui->nvChiTiet->objectName(),ui->nvChiTiet->isChecked());
    QJsonObject chamCongObj;
    QJsonObject tinhLuongObj;
    QJsonObject danhSachObj;
    for (int i = 0; i < chamCongDC->rowCount(); ++i) {
        chamCongObj.insert(chamCongDC->index(i,1).data().toString(),
                   chamCongDC->index(i,0).data().toString());
    }
    for (int i = 0; i < tinhLuongDC->rowCount(); ++i) {
        tinhLuongObj.insert(tinhLuongDC->index(i,1).data().toString(),
                   tinhLuongDC->index(i,0).data().toString());
    }

    //danh cho form danh sach nhan
    for (int i = 0; i < danhSachDC->rowCount(); ++i) {
        danhSachObj.insert(danhSachDC->index(i,1).data().toString(),
                   danhSachDC->index(i,0).data().toString());
    }
    ///kiem tra tung check
    //
    if(ui->nvCapSo->isChecked())
        root->insert(tenquyen::capSo,true);
    if(ui->nvTraSo->isChecked())
        root->insert(tenquyen::traSo,true);
    if(ui->nvSTK->isChecked())
        root->insert(tenquyen::thayDoiTKNH,true);
    if(ui->nvTaoHd->isChecked())
        root->insert(tenquyen::taoHD,true);
    if(ui->nvTaoThuViec->isChecked())
        root->insert(tenquyen::taoHDThuViec,true);
    if(ui->nvQuyDinhLuong->isChecked())
        root->insert(tenquyen::quyDinhLuong,true);
    if(ui->nvChiTiet->isChecked())
        root->insert(tenquyen::xemChiTietNV,true);
    if(ui->nvXemSN->isChecked())
        root->insert(tenquyen::xemSinhNhat,true);
    if(ui->nvXemHDganHethan->isChecked())
        root->insert(tenquyen::xemHopDongGanHetHan,true);
    //
    if(ui->phanQuyen->isChecked())
        root->insert(tenquyen::phanQuyen,true);
    if(ui->taoTK->isChecked())
        root->insert(tenquyen::taiKhoan,true);
    if(ui->thayDoiTTTK->isChecked())
        root->insert(tenquyen::thayDoiTK,true);
    if(ui->thietLapHeSo->isChecked())
        root->insert(tenquyen::quiDinhHeSo,true);
    if(ui->tlXem->isChecked())
        root->insert(tenquyen::xemTinhLuong,true);
    if(ui->nvTamUng->isChecked())
        root->insert(tenquyen::tamUng,true);
    if(ui->mnQuyen->isChecked())
        root->insert(tenquyen::Quyen,true);
    if(ui->QLTamung->isChecked())
        root->insert(tenquyen::QLTamUng,true);
    if(ui->QLNghiLuu->isChecked())
        root->insert(tenquyen::QLNghiLuu,true);
    if(ui->QLTuyenNV->isChecked())
        root->insert(tenquyen::QLTuyenNV,true);
    if(ui->QLHopDong->isChecked())
        root->insert(tenquyen::QLHopDong,true);
    if(ui->checkBoxThuong->isChecked())
        root->insert(tenquyen::QLThuong,true);
    root->insert("chamCong",chamCongObj);
    root->insert("tinhLuong",tinhLuongObj);
    root->insert("danhSach",danhSachObj);
    QJsonDocument doc;
    doc.setObject(*root.data());
    quyen->coQuyen = doc.toJson();
}
