#include "formphanquyen.h"
#include "ui_formphanquyen.h"

FormPhanQuyen::FormPhanQuyen(QString nvid, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPhanQuyen)
{
    ui->setupUi(this);
    m_username = nvid;
    nhomQuyenModel = new QSqlQueryModel();
    quyenChonModel = new QStandardItemModel();

    this->username = nvid;
    query = new QSqlQuery();
    /*nhomQuyenModel->setQuery("select NHOM_QUYEN.NHOMQUYENID,MO_TA from NHOM_QUYEN "
                         "LEFT JOIN THUOC_NHOM on THUOC_NHOM.NHOMQUYENID = NHOM_QUYEN.NHOMQUYENID "
                         "LEFT join TAI_KHOAN on TAI_KHOAN.USERNAME = THUOC_NHOM.USERNAME where TAI_KHOAN.USERNAME = '"+nvid+"'");*/
    nhomQuyenModel->setQuery("select NHOMQUYENID,MO_TA from NHOM_QUYEN");
    query->exec("select NHOM_QUYEN.NHOMQUYENID,MO_TA from NHOM_QUYEN "
                "LEFT JOIN THUOC_NHOM on THUOC_NHOM.NHOMQUYENID = NHOM_QUYEN.NHOMQUYENID "
                "LEFT join TAI_KHOAN on TAI_KHOAN.USERNAME = THUOC_NHOM.USERNAME where TAI_KHOAN.USERNAME = '"+nvid+"'");
    while (query->next()) {
        quyenChonModel->appendRow(add(query->value(0).toString(),
                                      query->value(1).toString()));
    }
    //menu xoa
    action_xoa = new QAction(this);
    action_xoaQuyen = new QAction(this);
    action_xoa->setText("Xóa");
    action_xoaQuyen->setText("Xóa");
    contextMenu.reset(new QMenu());
    contextMenuQuyen.reset(new QMenu());
    contextMenu->addAction(action_xoa);
    contextMenuQuyen->addAction(action_xoaQuyen);
    ui->treeViewCoQuyenoQuyen->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeViewQuyenuyen->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeViewCoQuyenoQuyen,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customMenuRequested(QPoint)));
    connect(ui->treeViewQuyenuyen,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customMenuRequestedQuyen(QPoint)));
    connect(action_xoa,SIGNAL(triggered(bool)),this,SLOT(onclickxoa()));
    connect(action_xoaQuyen,SIGNAL(triggered(bool)),this,SLOT(onclickxoaQuyen()));
    /*Lay thong tin quyen cua nhan vien hien tai*/
    //ui->lineEditTenNV->setText(username);
    ui->treeViewCoQuyenoQuyen->setModel(quyenChonModel);
    ui->treeViewQuyenuyen->setModel(nhomQuyenModel);

}

FormPhanQuyen::~FormPhanQuyen()
{
    delete ui;
    delete quyenChonModel;
    delete nhomQuyenModel;
    delete query;
    delete action_xoa;
}
QList<QStandardItem *> FormPhanQuyen::add(const QString &nhomquyenid,
                                          const QString &moTa)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(nhomquyenid);
    rowItems << new QStandardItem(moTa);
    return rowItems;
}

void FormPhanQuyen::on_treeViewQuyenuyen_clicked(const QModelIndex &index)
{
    if(quyenChonModel->findItems(nhomQuyenModel->index(index.row(),0).data().toString(),
                                 Qt::MatchExactly,0).length() == 0){
        //quyenChonModel->appendRow(add(nhomQuyenModel->index(index.row(),0).data().toString()));
        quyenChonModel->appendRow(add(nhomQuyenModel->index(index.row(),0).data().toString(),
                                      nhomQuyenModel->index(index.row(),1).data().toString()));
    }

}

void FormPhanQuyen::on_pushButton_clicked()
{
    /*cap nhat vao nhan vien vao bang THUOC_NHOM*/
    query->clear();
    query->prepare("INSERT INTO THUOC_NHOM "
                   "(NHOMQUYENID, USERNAME)"
                 "VALUES (:quyenid, :nvid) ");
    query->bindValue(":nvid",m_username);
    for (int i = 0; i < quyenChonModel->rowCount(); ++i) {
        query->bindValue(":quyenid",quyenChonModel->index(i,0).data().toInt());
        if(!query->exec()){
            qDebug() << query->lastError().text();
        }
    }
}
void FormPhanQuyen::customMenuRequested(QPoint pos)
{
    contextMenu->popup(ui->treeViewCoQuyenoQuyen->viewport()->mapToGlobal(pos));
}
void FormPhanQuyen::customMenuRequestedQuyen(QPoint pos)
{
    contextMenuQuyen->popup(ui->treeViewQuyenuyen->viewport()->mapToGlobal(pos));
}

void FormPhanQuyen::onclickxoa()
{
    query->clear();
    query->prepare("delete from THUOC_NHOM where USERNAME = :username and NHOMQUYENID =:quyenid");
    query->bindValue(":username",m_username);
    query->bindValue(":quyenid",quyenChonModel->index(ui->treeViewCoQuyenoQuyen->currentIndex().row(),0).data().toInt());
    if(query->exec()){
        quyenChonModel->removeRow(ui->treeViewCoQuyenoQuyen->currentIndex().row());
        qDebug() << query->lastQuery();
    }else{
        QMessageBox::warning(this,"Loi", "Khong the thu hoi quyen cua nhan vien luc nay xin thu lai sau");
    }
}

void FormPhanQuyen::onclickxoaQuyen()
{
    query->clear();
    qDebug() << "adsad";
    query->prepare("delete from NHOM_QUYEN where NHOMQUYENID =:quyenid");
    query->bindValue(":quyenid",nhomQuyenModel->index(ui->treeViewQuyenuyen->currentIndex().row(),0).data().toInt());
    if(query->exec()){
        nhomQuyenModel->setQuery(nhomQuyenModel->query().lastQuery());
    }else{
        QMessageBox::warning(this,"Loi", "Khong the thu hoi quyen cua nhan vien luc nay xin thu lai sau");
    }
}

void FormPhanQuyen::on_treeViewQuyenuyen_doubleClicked(const QModelIndex &index)
{
    //mo form quyen de cap nhat lai
    QPointer<FormQuyen> fquyen;
    fquyen = new FormQuyen(this);
    fquyen->setAttribute(Qt::WA_DeleteOnClose);
    fquyen->setQuyen(nhomQuyenModel->index(index.row(),0).data().toInt());
    fquyen->exec();
}
