#ifndef PROCESSORBASE_H
#define PROCESSORBASE_H

#include <QString>
#include <QVector>
#include <QMap>
#include "model/bill.h"
#include "dao/query.h"

class ProcessorBase
{
public:
    QVector <Bill> raw; //原始数据
    QVector < QVector <int> > matrix;//导出数据
    QMap<ID, QString> nameMap;
    QVector <QDate> X;//横轴值
    QVector <ID> Y;//纵轴值（矩阵中的纵轴而非graph中的纵轴，graph中表现为多条曲线）


    ProcessorBase();
    virtual ID getY(int i) = 0;
    virtual QDate getX(int i) = 0;
    bool process(int i);
    void sortByX();
    virtual bool processAll();
    QVector <QDate> getXvector() {return X;}
    virtual QVector <QString> getYvector();
    QVector < QVector <int> > getMatrix() {return matrix;}
    virtual ~ProcessorBase(){}
};

#endif // PROCESSORBASE_H
