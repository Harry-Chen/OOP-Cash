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
 * @file   query.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class Query
 */
#ifndef QUERY_H
#define QUERY_H

#include <QVector>
#include <QPair>
#include <QDateTime>
#include <QDate>
#include <date.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/connection.h>

#include "util/constants.h"
#include "model/bill.h"

/**
 * @brief make query of bills in the database
 */
class Query
{
private:
    sqlpp::sqlite3::connection *db;
    Query(sqlpp::sqlite3::connection *_db);
    std::vector<ID> creatorIds;
    std::vector<ID> fromAccountIds;
    std::vector<ID> toAccountIds;
    std::vector<ID> categoryIds;
    QPair<unsigned int, unsigned int> quantityRange;
    bool quantityRangeSet = false;
    QPair<QDate, QDate> dateRange;
    bool dateRangeSet = false;
    bool finished;
    bool finishedSet = false;
    QString noteKeyword;
    bool noteKeywordSet = false;
public:
    /**
     * @brief Construct a new Query
     * @param _db database connection
     * @return the Query object
     */
    static Query newQuery(sqlpp::sqlite3::connection *_db);
    /**
     * @brief add creator into the constraints
     * @param _creatorId UID of creator of the Bill
     * @return the Query object
     */
    Query& addCreatorId(ID _creatorId);
    /**
     * @brief add from Account into the constraints
     * @param _fromAccountId ID of the from Account
     * @return the Query object
     */
    Query& addFromAccountId(ID _fromAccountId);
    /**
     * @brief add to Account into the constraints
     * @param _toAccountId ID of the to Account
     * @return the Query object
     */
    Query& addToAccountId(ID _toAccountId);
    /**
     * @brief add Category into the constraints
     * @param _categoryId ID of the Category
     * @return the Query object
     */
    Query& addCategoryId(ID _categoryId);
    /**
     * @brief add quantity range (integer) into the constraints
     * @throws will throw exception if from > to
     * @param from lower bound
     * @param to upper bound
     * @return the Query object
     */
    Query& setQuantityRange(unsigned int from, unsigned int to);
    /**
     * @brief add date range (QDate) into the constraints
     * @throws will throw exception if start later than end
     * @param start lower bound
     * @param end upper bound
     * @return the Query object
     */
    Query& setDateRange(const QDate &start, const QDate &end);
    /**
     * @brief add finish state into the constraints
     * @param _finished is the transation finished
     * @return the Query object
     */
    Query& setFinished(bool _finished);
    /**
     * @brief add keyword into the constraints
     * @param _keyword the keyword used in LIKE statement in SQL
     * @return the Query object
     */
    Query& setKeyword(const QString &_keyword);
    /**
     * @brief execute the query with all constraints in the database
     * @return QVector of all bills that match the constraints
     */
    QVector<Bill> doQuery();
};

#endif // QUERY_H
