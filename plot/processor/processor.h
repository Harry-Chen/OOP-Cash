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

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QVector>
#include <QMap>
#include <QDate>
#include <QString>

#include "model/bill.h"
#include "dao/query.h"

/**
 * @brief The Processor class, abstract class (as an abstract product and templete method)
 */
class Processor
{
public:

    /**
     * @brief Construct a Processor
     * @param _bills the QVector of bills to be processed
     * @param _nameMap the map of ID and its name in QString, which is return by a concrete class of ItemManager
     */
    Processor(const QVector<Bill> & _bills, const QMap<ID, QString> & _nameMap)
        :bills_(_bills),
          nameMap_(_nameMap)
    {}
    virtual ~Processor(){}
    /**
     * @brief ProcessAll, default relization is to process every bill
     * @return if process all bills successfully, return true
     */
    virtual bool ProcessAll();
    /**
     * @brief Get QVector of Dates
     * @return QVector of Date for xAxis
     */
    virtual const QVector<QDate> & GetDates() {return dates_;}
    /**
     * @brief Get QVector of Fieldnames
     * @return QVector of FieldNames for different graphs
     */
    virtual const QVector<QString> GetFieldnames();
    /**
     * @brief GetValues
     * @return Matrix of Values for yAxis
     */
    virtual const QVector < QVector <int> > & GetValues() {return matrix_;}

protected:
    QVector <Bill> bills_;
    QMap<ID, QString> nameMap_;
    QVector < QVector <int> > matrix_;
    QVector <QDate> dates_;
    QVector <ID> fieldnames_;

    /**
     * @brief GetFieldname of No.i bill
     * @param No.i
     * @return the ID of its fieldname
     */
    virtual ID GetFieldname(int i) = 0;
    /**
     * @brief GetDate of No.i bill (read and process)
     *        default realization is to get date by day
     * @param No.i
     * @return the processed Date
     */
    virtual QDate GetDate(int i) {return bills_[i].date;}
    /**
     * @brief Process No.i bill, put its date, fieldname and value in QVector
     * @param No.i
     * @return if process successfully, return true
     */
    bool Process(int i);
    /**
     * @brief Sort QVector and Matrix if needed
     */
    void Sort();
};
#endif // PROCESSOR_H
