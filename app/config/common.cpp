#include "common.h"
QString Common::TEN_DN = QStringLiteral("Cong ty co phan ISUZU");
QString Common::DIA_CHI_DN = QStringLiteral("an khanh, binh thuy");
int Common::NGAY_BAT_DAU_TINH_LUONG = 10;
int Common::NGAY_BAT_DAU_CHAM_CONG = 26;
int Common::NAM_HIEN_TAI = 2015;//set 2015 de kiem tra loi phat sinh
int Common::kyHienTai = 1;
QScopedPointer<QJsonArray> Common::coQuyen;
struct aa {
   static const char* enumtext[];
};
QStringList Common::mangso = QStringList() << "không"<<"một"<<"hai"<<"ba"<<"bốn"<<"năm"<<"sáu"<<"bảy"<<"tám"<<"chín";
/*QString Common::mangso[0] = "không";
QString Common::mangso[1] = "một";
QString Common::mangso[2] = "hai";
QString Common::mangso[3] = "ba";
QString Common::mangso[4] = "bốn";
QString Common::mangso[5] = "năm";
QString Common::mangso[6] ="sáu";
QString Common::mangso[7] = "bảy";
QString Common::mangso[8] = "tám";
QString Common::mangso[9] = "chín";*/
QString Common::chuoi = QStringLiteral("a");
Common::Common()
{
    Common::NAM_HIEN_TAI = QDate::currentDate().year();


    //mangso[0] ="aaaa";
}

/*int Common::findIndex(QSqlQueryModel *model,QString value, int columnNum) const
{
    for (int i = 0; i < model->rowCount(); ++i) {
        if(model->index(i,columnNum).data().toString() == value)
            return i;
    }
    return -1;
}*/
void Common::themPBTheoQuyen(QComboBox *comBoBox, Common::FORMCHINH f)
{
    QJsonObject::iterator it;
    QScopedPointer<QJsonObject> subArr;
    QString tenFrom;
    if(f == FORM_CHAMCONG)
        tenFrom = "chamCong";
    if(f == FORM_DANHSACH)
        tenFrom = "danhSach";
    QString key;
    if(!Common::coQuyen.isNull()){
        for (int i =0; i <= Common::coQuyen->count(); ++i) {
            //qDebug() << it.i;
            subArr.reset(new QJsonObject(Common::coQuyen->at(i).toObject()[tenFrom].toObject()));
            for(it =subArr->begin();it!= subArr->end(); ++it){
                key = "";//chac chan la key duoc xoa.
                key = it.key();
                if(comBoBox->findData(key) == -1){//tim khong thay thi them vao
                    comBoBox->addItem(subArr->value(key).toString(),key);
                    if(i==0){
                        comBoBox->setCurrentIndex(0);
                    }
                }
            }
            //

        }
    }
}

bool Common::timQuyen(const QString q)
{
    QJsonObject::iterator it;
    QScopedPointer<QJsonObject> subArr;
    QString key;
    if(!Common::coQuyen.isNull()){
        for (int i =0; i <= Common::coQuyen->count(); ++i) {
            //qDebug() << it.i;
            subArr.reset(new QJsonObject(Common::coQuyen->at(i).toObject()));
            for(it =subArr->begin();it!= subArr->end(); ++it){
                key = "";//chac chan la key duoc xoa.
                if(it.key() == q){
                    return subArr->value(it.key()).toBool(false);
                }
            }
        }
    }
    return false;
}

int Common::findIndex(QStandardItemModel *model, QString value, int columnNum)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        if(model->index(i,columnNum).data().toString() == value)
            return i;
    }
    return -1;
}
int Common::findIndex(QSqlQueryModel *model, QString value, int columnNum)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        if(model->index(i,columnNum).data().toString() == value)
            return i;
    }
    return -1;
}


//string mangso[10] = {'không','một','hai','ba','bốn','năm','sáu','bảy','tám','chín'};
QString Common::dochangchuc(int so, bool daydu) {
    QString chuoi = "";
    int chuc = so/10;
    int donvi = so%10;
    if (chuc>1) {
        chuoi = " " + Common::mangso[chuc] + " mươi";
        if (donvi==1) {
            chuoi += " mốt";
        }
    } else if (chuc==1) {
        chuoi = " mười";
        if (donvi==1) {
            chuoi += " một";
        }
    } else if (daydu && donvi>0) {
        chuoi = " lẻ";
    } if (donvi==5 && chuc>1) {
        chuoi += " lăm";
    } else if (donvi>1||(donvi==1&&chuc==0)) {
        chuoi += " " + Common::mangso[donvi];
    }
    return chuoi;
}
QString Common::docblock(int so, bool daydu) {
    QString chuoi = "";
    int tram = so/100;
    so = so%100;
    if (daydu || tram>0) {
        chuoi = " " + Common::mangso.at(tram) + " trăm";
        chuoi += dochangchuc(so,true);
    } else {
        chuoi = dochangchuc(so,false);
    } return chuoi;
}
QString Common::dochangtrieu(int so, bool daydu) {
    QString chuoi = "";
    int trieu = so/1000000;
    so = so%1000000;
    if (trieu>0) {
        chuoi = docblock(trieu,daydu) + " triệu";
        daydu = true;
    }
    int nghin = so/1000;
    so = so%1000;
    if (nghin>0) {
        chuoi += docblock(nghin,daydu) + " nghìn";
        daydu = true;
    } if (so>0) {
        chuoi += docblock(so,daydu);
    }
    return chuoi;
}
QString Common::docso(int so) {
    if (so==0) {
        return Common::mangso[0];
    }
    Common::chuoi = "";
    QString hauto = "";
    int ty=0;
    do {
        ty = so%1000000000;
        so = so/1000000000;
        if (so>0) {
            Common::chuoi = dochangtrieu(ty,true) + hauto + Common::chuoi;
        } else {
            Common::chuoi = dochangtrieu(ty,false) + hauto + Common::chuoi;
        }
        hauto = " tỷ";
    } while
            (so>0);
    return Common::chuoi + " đồng";
}
