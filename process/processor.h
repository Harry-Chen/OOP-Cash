#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QVector>
#include <QMap>
#include "model/bill.h"
#include "dao/query.h"

class Processor
{
    //bool (* isSameXptr) (const QDate&, const QDate&);
    ID (* getYptr) (Bill);
    QDate (*getXptr) (QDate);
    QVector <Bill> raw; //原始数据
    QVector < QVector <int> > matrix;//导出数据
    const QMap<ID, QString> &nameMap;
    QVector <QDate> X;//横轴值
    QVector <ID> Y;//纵轴值（矩阵中的纵轴而非graph中的纵轴，graph中表现为多条曲线）
   // int num; //即Y.size, 表示y(x)的个数, 0表示单变量，-1表示因变量个数未知， 正值表示因变量个数
public:
    Processor (Query * pQuery, const QMap<ID, QString> & _nameMap);
   // double timeSpan;
    ID getY(int i) { return (*getYptr) (raw[i]);} const
    QDate getX(int i) {return(*getXptr) (raw[i].date);}
//    bool isSameX (QDate date1, QDate date2) {
//        return (*isSameXptr)(date1, date2);}
    //bool isSameY (int i1, int i2);
    bool process(int i);
    bool processAll();
    void sortByX();
    //void setIsSameX (bool (*func) (const QDate&, const QDate&)) {isSameXptr = func;}
    void setGetY (ID (*func) (Bill)) {getYptr = func;}
    void setGetX (QDate (*func) (QDate)) {getXptr = func;}
    QVector <QDate> getXvector() {return X;}
    QVector <QString> getYvector();
    QVector < QVector <int> > getMatrix() {return matrix;}
    //~Processor();
};

#endif // PROCESSOR_H
