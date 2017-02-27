#ifndef QUYEN_H
#define QUYEN_H

#include <QObject>
#include <QSqlTableModel>
#include "Objects/oquyen.h"
#include "utils/manageindex.h"
#include <QJsonDocument>

class Quyen : public QObject
{
    Q_OBJECT
public:
    explicit Quyen(QObject *parent = 0);
    ~Quyen();
    QString nhomQuyenId;
    QString moTa;
    QByteArray coQuyen;
    /// Cau truc du lieu {a:'a',chamCong:{phongid:'ten'}}
    QJsonDocument cacQuyen;
    bool themQuyen();
    QSqlQueryModel *layQuyen(QString username);
    bool update(const int quyenid);
private:
    QSqlTableModel *tableModelQuyen;
    QSqlQuery *query;
signals:

public slots:
};

#endif // QUYEN_H
