#include "query.h"
#include <logging/logger.h>

Query::Query(sqlpp::sqlite3::connection *_db) : db(_db){}


Query Query::newQuery(sqlpp::sqlite3::connection *_db)
{
    return Query(_db);
}

Query &Query::addCreatorId(ID _creatorId)
{
    creatorIds.push_back(_creatorId);
    return *this;
}

Query &Query::addFromAccountId(ID _fromAccountId)
{
    fromAccountIds.push_back(_fromAccountId);
    return *this;
}

Query &Query::addToAccountId(ID _toAccountId)
{
    toAccountIds.push_back(_toAccountId);
    return *this;
}

Query &Query::addCategoryId(ID _categoryId)
{
    categoryIds.push_back(_categoryId);
    return *this;
}

Query &Query::setQuantityRange(unsigned int from, unsigned int to)
{
    if(from <= to){
        quantityRange = QPair<unsigned int, unsigned int>(from, to);
        quantityRangeSet = true;
        return *this;
    }
    else
        throw std::string("Quantity range lower bound larger than upper bound.");
}

Query &Query::setDateRange(const QDate &start, const QDate &end)
{
    if(start <= end){
        dateRange = QPair<QDate, QDate>(start, end);
        dateRangeSet = true;
        return *this;
    }
    else
        throw std::string("Date range lower bound larger than upper bound.");
}

Query &Query::setFinished(bool _finished)
{
    finished = _finished;
    finishedSet = true;
    return *this;
}

Query &Query::setKeyword(const QString &_keyword)
{
    noteKeyword = _keyword;
    noteKeywordSet = true;
    return *this;
}


QVector<Bill> Query::doQuery()
{
    logging::debug("Doing query:");
    QVector<Bill> result;
    auto qry = sqlpp::dynamic_select(*db, all_of(Bill::TABLE))
            .from(Bill::TABLE)
            .dynamic_where();
    if(creatorIds.size())
        qry.where.add(Bill::TABLE.creator.in(sqlpp::value_list(creatorIds)));
    if(fromAccountIds.size())
        qry.where.add(Bill::TABLE.afrom.in(sqlpp::value_list(fromAccountIds)));
    if(toAccountIds.size())
        qry.where.add(Bill::TABLE.ato.in(sqlpp::value_list(toAccountIds)));
    if(categoryIds.size())
        qry.where.add(Bill::TABLE.category.in(sqlpp::value_list(categoryIds)));
    if(quantityRangeSet)
    {
        qry.where.add(Bill::TABLE.quantity >= quantityRange.first);
        qry.where.add(Bill::TABLE.quantity <= quantityRange.second);
    }
    if(dateRangeSet)
    {
        qry.where.add(Bill::TABLE.date >= dateRange.first.toJulianDay());
        qry.where.add(Bill::TABLE.date <= dateRange.second.toJulianDay());
    }
    if(finishedSet)
        qry.where.add(Bill::TABLE.finished == (finished?1:0));
    if(noteKeywordSet)
        qry.where.add(Bill::TABLE.note.like(std::string("%") + noteKeyword.toStdString() + "%"));
    int count = 0;
    for(const auto &row:(*db)(qry)){
        Bill newBill(row.id, row.afrom, row.ato, row.creator,
                     row.category, row.quantity,
                     QDateTime::fromSecsSinceEpoch(row.ctime),
                     row.finished,
                     QDate::fromJulianDay(row.date),
                     QString::fromStdString(row.note));
        count++;
        logging::debug(std::string("Result ") + std::to_string(count)
                       + ": " + static_cast<std::string>(newBill));
        result.append(newBill);
    }
    logging::debug(std::to_string(count) + " results found.");
    return result;
}
