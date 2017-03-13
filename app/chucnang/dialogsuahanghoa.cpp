#include "dialogsuahanghoa.h"
#include "ui_dialogsuahanghoa.h"

DialogSuaHangHoa::DialogSuaHangHoa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSuaHangHoa)
{
    ui->setupUi(this);
    hangHoaModel = new QSqlTableModel();
    hangHoaModel->setTable("HANG_HOA");
    hangHoaModel->select();
    hangHoaModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableViewhangHoa->setModel(hangHoaModel);
}

DialogSuaHangHoa::~DialogSuaHangHoa()
{
    delete ui;
    delete hangHoaModel;
}

void DialogSuaHangHoa::on_pushButtonThemHang_clicked()
{
    query.clear();
    query.prepare("insert into HANG_HOA(HANGHOAID,TEN,GIA_BAN) values(:hdid,:ten,:giaBan)");
    query.bindValue(":ten",ui->lineEditTenHang->text());
    query.bindValue(":hdid",ui->lineEditMaHang->text());
    query.bindValue(":giaBan",ui->spinBox->value());
    if(query.exec()){
        ui->lineEditMaHang->setText("");
        ui->lineEditTenHang->setText("");
        ui->spinBox->setValue(0);
        hangHoaModel->select();
    }else{
        QMessageBox::warning(this,"Loi them moi","Không thể thêm mới hàng hóa lúc này or kiểm tra mạng rồi thử lại sau",QMessageBox::Ok,QMessageBox::NoButton);
    }
}
