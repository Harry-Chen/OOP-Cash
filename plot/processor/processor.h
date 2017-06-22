//产品系列1的基类
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QVector>
#include <QMap>
#include <QDate>
#include <QString>

#include "model/bill.h"
#include "dao/query.h"

class Processor
{
public:
    Processor(const QVector<Bill> & _bills, const QMap<ID, QString> & _nameMap)
        :bills_(_bills),
          nameMap_(_nameMap)
    {}
    virtual ~Processor(){}
    virtual bool ProcessAll();//缺省实现为逐个运行Process(i),不做其他处理
    virtual const QVector<QDate> & GetDates() {return dates_;}
    virtual const QVector<QString> GetFieldnames();
    virtual const QVector < QVector <int> > & GetValues() {return matrix_;}

protected:
    QVector <Bill> bills_; //原始bill数据
    QMap<ID, QString> nameMap_;//ID与字段的名字对应的Map

    QVector < QVector <int> > matrix_;//即相应金额
    QVector <QDate> dates_;//日期
    QVector <ID> fieldnames_;//所选字段的各个名字的ID

    virtual ID GetFieldname(int i) = 0;
    virtual QDate GetDate(int i) {return bills_[i].date;}//缺省实现为按日得到日期
    bool Process(int i);//把第i个biil中的value值按字段和日期放入matrix_中
    virtual void Sort(){}//缺省实现为无变化，即不需要排序
};
#endif // PROCESSOR_H
