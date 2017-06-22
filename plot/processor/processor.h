/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   processor.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class Processor
 */

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
