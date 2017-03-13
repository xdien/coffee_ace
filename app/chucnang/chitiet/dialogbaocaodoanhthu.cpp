#include "dialogbaocaodoanhthu.h"
#include "ui_dialogbaocaodoanhthu.h"

DialogBaoCaoDoanhThu::DialogBaoCaoDoanhThu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBaoCaoDoanhThu)
{
    ui->setupUi(this);
    baoCaoModel = new QSqlQueryModel();
    ui->dateEditDen->setDate(QDate::currentDate());
    ui->dateEditTU->setDate(ui->dateEditDen->date().addMonths(-1));
    QString dieuKienStr = " NGAY_LAP_HT >= '"+ui->dateEditTU->date().toString("yyyy-M-d")+"' and "
                          "NGAY_LAP_HT<= '"+ui->dateEditDen->date().toString("yyyy-M-d")+"'";
    baoCaoModel->setQuery("select * from PHIEU_XUAT where "+dieuKienStr);
    query.exec("select FORMAT(SUM(TONG_TIEN),0) from PHIEU_XUAT where " +dieuKienStr);
    if(query.next()){
        ui->labelTongDoanhThu->setText(query.value(0).toString());
    }
    ui->treeViewBaoCao->setModel(baoCaoModel);
}

DialogBaoCaoDoanhThu::~DialogBaoCaoDoanhThu()
{
    delete ui;
    delete baoCaoModel;
}

void DialogBaoCaoDoanhThu::on_pushButtonXem_clicked()
{
    QString dieuKienStr = " NGAY_LAP_HT >= '"+ui->dateEditTU->date().toString("yyyy-M-d")+"' and "
                          "NGAY_LAP_HT<= '"+ui->dateEditDen->date().toString("yyyy-M-d")+"'";
    baoCaoModel->setQuery("select * from PHIEU_XUAT where "+dieuKienStr);
    query.exec("select FORMAT(SUM(TONG_TIEN),0) from PHIEU_XUAT where " +dieuKienStr);
    if(query.next()){
        ui->labelTongDoanhThu->setText(query.value(0).toString());
    }
}
