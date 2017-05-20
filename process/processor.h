#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QVector>
#include "model/bill.h"
//#include "isSameX/issamexstrategy.h"
//#include "getY/getystrategy.h"

//template < typename Tx, typename Ty >
class Processor
{
    //isSameXstrategy * issamex;
    //getYstrategy * gety;
    bool (* isSameXptr) (const QDate&, const QDate&);
    ID (* getYptr) (Bill);
    const QVector <Bill> &raw; //原始数据
    QVector < QVector <int> > matrix;//导出数据
    QVector <QDate> X;//横轴值
    QVector <ID> Y;//纵轴值（矩阵中的纵轴而非graph中的纵轴，graph中表现为多条曲线）
    int num; //即Y.size, 表示y(x)的个数, 0表示单变量，-1表示因变量个数未知， 正值表示因变量个数
   // int i;
public:
    //Processor();
    Processor (const QVector <Bill> &result): raw(result) {}
    //void setIsSameX(isSameXstrategy * _issamex) {issamex = _issamex;}
    ID getY(int i) {return (*getYptr) (raw[i]);}
    bool isSameX (int i1, int i2) {return (*isSameXptr)(raw[i1].date, X[i2]);}
    bool isSameY (int i1, int i2);
    bool process(int i);
    bool processAll();
    void sortByX();
    void setIsSameX (bool (*func) (const QDate&, const QDate&)) {isSameXptr = func;}
    void setGetY (ID (*func) (Bill)) {getYptr = func;}
    QVector <QDate> getXvector() {return X;}
    QVector <ID> getYvector() {return Y;}
    QVector < QVector <int> > getMatrix() {return matrix;}
    //~Processor();
};

#endif // PROCESSOR_H
