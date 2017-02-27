#ifndef FORMPHANQUYEN_H
#define FORMPHANQUYEN_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QSqlError>
#include <QDebug>
#include <QMenu>
#include <QJsonObject>
#include <QDebug>
#include "chucnang/formquyen.h"
#include <QMessageBox>

namespace Ui {
class FormPhanQuyen;
}

class FormPhanQuyen : public QWidget
{
    Q_OBJECT

public:
    explicit FormPhanQuyen(QString nvid, QWidget *parent = 0);
    ~FormPhanQuyen();
    QString username;

private slots:
    void on_treeViewQuyenuyen_clicked(const QModelIndex &index);

    void on_pushButton_clicked();
    void customMenuRequested(QPoint pos);
    void customMenuRequestedQuyen(QPoint pos);
    void onclickxoa();
    void onclickxoaQuyen();

    void on_treeViewQuyenuyen_doubleClicked(const QModelIndex &index);

private:
    Ui::FormPhanQuyen *ui;
    QSqlQueryModel *nhomQuyenModel;
    QStandardItemModel *quyenChonModel;
    QList<QStandardItem *> add(const QString &nhomquyenid, const QString &moTa);
    QSqlQuery *query;
    QString m_username;
    ///
    QScopedPointer<QMenu> contextMenu;
    QAction *action_xoa;
    ///
    QScopedPointer<QMenu> contextMenuQuyen;
    QAction *action_xoaQuyen;
};

#endif // FORMPHANQUYEN_H
