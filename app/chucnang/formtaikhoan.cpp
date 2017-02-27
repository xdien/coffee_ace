#include "formtaikhoan.h"
#include "ui_formtaikhoan.h"

FormTaiKhoan::FormTaiKhoan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTaiKhoan)
{
    ui->setupUi(this);
    taiKhoan = new TaiKhoan();
    taiKhoanTableModel = new QSqlTableModel();
    ui->tableViewTaiKhoan->setModel(taiKhoanTableModel);
    taiKhoanTableModel->setTable("TAI_KHOAN");
    taiKhoanTableModel->select();
    taiKhoanTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    setWindowTitle("Tài khoản");
    ui->tableViewTaiKhoan->horizontalHeader()->hideSection(1);
    ui->capNhat->setVisible(false);
    contextMenu.reset(new QMenu(this));
    actionXoa = new QAction(this);
    actionDoiMK = new QAction(this);
    actionXoa->setText("Xóa Tài Khoản");
    actionDoiMK->setText("Đổi mật khẩu");
    //contextMenu->addAction(actionCapNhat);
    contextMenu->addAction(actionDoiMK);
    ui->tableViewTaiKhoan->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableViewTaiKhoan->verticalHeader(),SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customMenuRequested(QPoint)));
    connect(actionXoa,SIGNAL(triggered(bool)),this,SLOT(capNhat()));
    connect(actionDoiMK,SIGNAL(triggered(bool)),this,SLOT(mo_formDoiMatKhau()));


}

FormTaiKhoan::~FormTaiKhoan()
{
    delete ui;
    delete taiKhoanTableModel;
    delete taiKhoan;
    delete actionXoa;
    delete actionDoiMK;

}

void FormTaiKhoan::on_pushButtonThemTaiKHoan_clicked()
{
    taiKhoan->userName = ui->lineEditUseName->text();
    taiKhoan->password = ui->lineEditPass->text();
    taiKhoan->diaChiNv = ui->plainTextEditDiaChi->document()->toPlainText();
    taiKhoan->tenNv = ui->lineEditHoTen->text();
    taiKhoan->gioiTinh = ui->checkBoxGioiTinh->checkState();
    if(taiKhoan->themTaiKhoan()){
        taiKhoanTableModel->select();
    }
}

void FormTaiKhoan::on_tableViewTaiKhoan_doubleClicked(const QModelIndex &index)
{
    /*hien thi formPhanQuyen*/
    QPointer<FormPhanQuyen> phanQuyen = new FormPhanQuyen(taiKhoanTableModel->index(index.row(),0).data().toString());
    phanQuyen->setAttribute(Qt::WA_DeleteOnClose);
    phanQuyen->setWindowTitle("Phân quyền cho nhân viên: " + taiKhoanTableModel->index(index.row(),0).data().toString());
    phanQuyen->show();
}

void FormTaiKhoan::on_capNhat_clicked()
{

}
void FormTaiKhoan::customMenuRequested(QPoint pos)
{
    contextMenu->popup(ui->tableViewTaiKhoan->viewport()->mapToGlobal(pos));
}

void FormTaiKhoan::xoaMotTaiKhoan()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Bạn có chắc xóa hợp đồng này không?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Yeah!"), QMessageBox::YesRole);
    msgBox.addButton(tr("Nope"), QMessageBox::NoRole);
    msgBox.exec();
    if (msgBox.clickedButton()==pButtonYes) {
        if(taiKhoan->xoa(taiKhoanTableModel->index(ui->tableViewTaiKhoan->currentIndex().row(),0).data().toString()))
            taiKhoanTableModel->select();
    }
}

void FormTaiKhoan::mo_formDoiMatKhau()
{
    QPointer<DialogDoiMatKhau> dgMk;
    dgMk = new DialogDoiMatKhau(taiKhoanTableModel->index(ui->tableViewTaiKhoan->currentIndex().row(),0).data().toString(),this);
    dgMk->setAttribute(Qt::WA_DeleteOnClose);
    dgMk->show();
}
