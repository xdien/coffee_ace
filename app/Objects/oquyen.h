#ifndef OQUYEN_H
#define OQUYEN_H

#include <QObject>
#include <QStandardItem>
#include <QSqlTableModel>

class OQuyen : public QObject
{
    Q_OBJECT
public:
    explicit OQuyen(QObject *parent = 0);
    ~OQuyen();
    QString formid, moTa;
    bool xem,capNhat;
signals:

public slots:
};

#endif // OQUYEN_H
