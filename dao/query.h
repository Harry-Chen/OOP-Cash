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

using std::vector;

class Query
{
private:
    sqlpp::sqlite3::connection *db;
    Query(sqlpp::sqlite3::connection *_db);
    vector<ID> creatorIds;
    vector<ID> fromAccountIds;
    vector<ID> toAccountIds;
    vector<ID> categoryIds;
    QPair<unsigned int, unsigned int> quantityRange;
    bool quantityRangeSet = false;
    QPair<QDate, QDate> dateRange;
    bool dateRangeSet = false;
    bool finished;
    bool finishedSet = false;
    QString noteKeyword;
    bool noteKeywordSet = false;
public:
    static Query newQuery(sqlpp::sqlite3::connection *_db);
    Query& addCreatorId(ID _creatorId);
    Query& addFromAccountId(ID _fromAccountId);
    Query& addToAccountId(ID _toAccountId);
    Query& addCategoryId(ID _categoryId);
    Query& setQuantityRange(unsigned int from, unsigned int to);
    Query& setDateRange(const QDate &start, const QDate &end);
    Query& setFinished(bool _finished);
    Query& setKeyword(const QString &_keyword);
    QVector<Bill> doQuery();
};

#endif // QUERY_H
