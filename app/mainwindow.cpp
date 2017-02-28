#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_setting.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    db = QSqlDatabase::database("qt_sql_default_connection");
    //ui->menuBao_cao->setEnabled(false);
    ui->menuHe_thong->setEnabled(true);//Comment de bao tri
    /*Thanh Thong bao trang thai status bar*/
    statusLabel = new QLabel(this);
    tinhtrangsql = new QLabel(this);
    //lay nam hien tai
    Common::NAM_HIEN_TAI = QDate::currentDate().year();
    statusLabel->setText("Bạn chưa đăng nhập");
    ui->actionChuc_vu->setVisible(false);

    if(db.isOpen())
    {
        /*Khoi dong cac form*/
        moi = new login();
        connect(moi,SIGNAL(nvdangnhap(QString)),this,SLOT(capnhatPhanQuyen(QString)));
        tinhtrangsql->setText("Thiết lập kết nối thành công |");
        /*lay ky hien tai*/
        query.prepare("select KYID from KY where NAM = :nam and THANG = :thang limit 1");
        query.bindValue(":nam",Common::NAM_HIEN_TAI);
        QDate mocNgay;//dua theo ngay tinh luong
        mocNgay.setDate(Common::NAM_HIEN_TAI,QDate::currentDate().month(),Common::NGAY_BAT_DAU_TINH_LUONG);
        if(QDate::currentDate() > mocNgay){
            //lay thang hien tai"
            query.bindValue(":thang", QDate::currentDate().month());
        }else{
            //lay thang hien tai tru 1
            query.bindValue(":thang", QDate::currentDate().addMonths(-1).month());
            query.bindValue(":nam",QDate::currentDate().addMonths(-1).year());
        }

        if(query.exec()){
            if(query.next()){
                Common::kyHienTai = query.value("KYID").toInt();
            }
        }
        query.clear();
    }else{
        ui->actionDan_nhap->setEnabled(false);
        tinhtrangsql->setText("Không thể kết nối tới máy chủ, xem lại tùy chỉnh kết nối");
    }
    ui->statusBar->addPermanentWidget(tinhtrangsql);
    ui->statusBar->addPermanentWidget(statusLabel);
    ///xac dinh quyen
    ///
    //ui->actionBH->setVisible(false);
    //ui->actionQuan_Ly_Luong->setDisabled(true);
    //ui->actionQuyen->setDisabled(true);
    //ui->actionTai_Khoan->setDisabled(true);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete moi;
    delete statusLabel;
    delete tinhtrangsql;
}

void MainWindow::on_actionSQL_triggered()
{
    Dialog_setting setting;
    setting.exec();
}

void MainWindow::on_actionDan_nhap_triggered()
{
    if(!moi->isActiveWindow())
    {
        moi->show();
        moi->activateWindow();
    }
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox aa;
    QString aas ="Thong tin ve Qt";
    aa.aboutQt(parentWidget(), aas);
    aa.show();
}
///
/// \brief MainWindow::capnhatPhanQuyen
/// \param username
///
void MainWindow::capnhatPhanQuyen(QString username)//cap nhat phan quyen dua theo macv
{
    //ui->actionQuan_Ly_Luong->setDisabled(true);
    ui->actionQuyen->setDisabled(true);
    ui->actionTai_Khoan->setDisabled(true);
    ui->actionHop_dong->setEnabled(false);
    ui->actionTai_Khoan->setEnabled(Common::timQuyen(tenquyen::taiKhoan));
    ui->actionQuyen->setEnabled(Common::timQuyen(tenquyen::Quyen));
    ui->actionHop_dong->setEnabled(Common::timQuyen(tenquyen::QLHopDong));
    ui->actionT_m_ng->setEnabled(false);
    ui->actionT_m_ng->setEnabled(Common::timQuyen(tenquyen::QLTamUng));
    ui->actionNgh_l_u->setEnabled(false);
    ui->actionNgh_l_u->setEnabled(Common::timQuyen(tenquyen::QLNghiLuu));
    ui->actionTuy_n_nh_n_vi_n->setEnabled(false);
    ui->actionTuy_n_nh_n_vi_n->setEnabled(Common::timQuyen(tenquyen::QLTuyenNV));
    //ui->actionQuan_Ly_Luong->setEnabled(Common::timQuyen(tenquyen::xemTinhLuong));
    ui->actionThuong->setEnabled(false);
    ui->actionThuong->setEnabled(Common::timQuyen(tenquyen::QLThuong));
    statusLabel->setText("Xin chào! " + username);
}


void MainWindow::on_actionAbout_triggered()
{
    about *a = new about();
    a->setAttribute(Qt::WA_DeleteOnClose,true);
    a->show();
}


void MainWindow::on_actionQuan_ly_NKH_triggered()
{
    //Kiem tra doi tuong xem co bi xoa vung nho chua
    //http://stackoverflow.com/questions/65724/uninitialized-memory-blocks-in-vc
    LimeReport::ReportEngine m_report;
    //LimeReport::PreviewReportWidget* m_preview;
     LimeReport::ReportEngine *report = new LimeReport::ReportEngine(this);
     report->loadFromFile(QApplication::applicationDirPath()+"/demo_reports/test.lrxml");
     report->previewReport();
     report->printReport();
}


void MainWindow::on_actionQuyen_triggered()
{
    FormQuyen *FQuyen = new FormQuyen(this);
    FQuyen->setAttribute(Qt::WA_DeleteOnClose);
    FQuyen->show();
}

void MainWindow::on_actionTai_Khoan_triggered()
{
    //kiem tra null, sau do kiem tra trang thai window
    if(formTaiKhoan.isNull()){
        formTaiKhoan = new FormTaiKhoan();
        formTaiKhoan->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(formTaiKhoan);
        //chamCongForm->setAttribute(Qt::WA_DeleteOnClose);
    ////diaTuyen->setAttribute(Qt::WA_DeleteOnClose,true);//xoa vung nho dialog khi dong cua so
    }
    formTaiKhoan->showMaximized();
}


void MainWindow::on_actionNhapHang_triggered()
{
    //kiem tra null, sau do kiem tra trang thai window
    /*if(chamCongForm.isNull()){
        chamCongForm = new FormChamCong();
        ui->mdiArea->addSubWindow(chamCongForm);
        //chamCongForm->setAttribute(Qt::WA_DeleteOnClose);
    ////diaTuyen->setAttribute(Qt::WA_DeleteOnClose,true);//xoa vung nho dialog khi dong cua so
    }
    chamCongForm->showMaximized();*/
}

void MainWindow::on_actionB_n_h_ng_triggered()
{
    QQuickView *view2 = new QQuickView();

    view2->setSource(QUrl("qrc:/banhang.qml"));
    view2->show();

}
