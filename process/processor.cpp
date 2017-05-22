#include "processor.h"
/*
ID Processor::getY(int i)
{
    return gety->getY(raw[i]);
}

bool isSame(bool (*func)(const QDate&, const QDate&), const QDate& a, const QDate& b){
    return (*func)(a, b);
}

void compare(){
    QDate a, b;
    bool sameYear = isSame([](const QDate& a1, const QDate& a2){return a1.year() == a2.year();}, a, b);

}

bool Processor::isSameX(int i1, int i2)
{
    return isSameX(raw[i1].date, X[i2]);
}
*/

Processor::Processor(Query *pQuery, const QMap<ID, QString> &_nameMap):
    raw(pQuery->doQuery()), nameMap(_nameMap)
{
    X.clear();
    Y.clear();
    QVector<int> temp(1,raw[0].quantity);
    matrix.push_back(temp);
    X.push_back(QDate());
    Y.push_back(0);
    std::cout << raw.size() << std::endl;
}

//bool Processor::isSameY(int i1, int i2)
//{
//    return getY(i1) == getY(i2);
//}

bool Processor::process(int i)
{
    //
    if(i == raw.size()) return false;
//    for(const auto & x:X){
//        if(getX(
//    }

    int indexX = X.indexOf(getX(i));
    int indexY = Y.indexOf(getY(i));
    if(indexX != -1 && indexY != -1){
        matrix[indexY][indexX] += raw[i].quantity;
    }
    else if(indexX != -1 && indexY == -1){
        matrix.push_back(QVector<int>(X.size(),0));
        Y.push_back(getY(i));
        matrix[Y.size() - 1][indexX] += raw[i].quantity;
    }
    else if(indexX == -1 && indexY != -1){
        for(int j = 0; j < Y.size(); ++j)
            matrix[j].push_back(0);
        X.push_back(getX(i));
        matrix[indexY][X.size() - 1] += raw[i].quantity;
    }
    else{
        matrix.push_back(QVector<int>(X.size() + 1,0));
        for(int j = 0; j < Y.size(); ++j)
            matrix[j].push_back(0);
        Y.push_back(getY(i));
        X.push_back(getX(i));
        matrix[Y.size() - 1][X.size() - 1] += raw[i].quantity;
    }

//    for(int ii = 0 ; ii < matrix.size() ;++ii)
//        if(isSameY(i, ii))
//            {
//                for (int jj = 0 ; jj < matrix[ii].size() ; ++jj)
//                    if(isSameX(i, jj)) { matrix[ii][jj] += raw[i].quantity; return true;}
//                X.push_back(raw[i].date);
//                matrix[ii].push_back(raw[i].quantity);
//                for(int _i = 0; _i < matrix.size(); ++_i)
//                    if( _i != ii ) matrix[_i].push_back(0);
//                return true;
//            }
//    Y.push_back(getY(i));

//    std::cout << X.size() << std::endl;
//    std::cout << Y.size() << std::endl;
//    std::cout << matrix.size() << std::endl;
//    std::cout << matrix[0].size() << std::endl;

//    matrix.push_back(QVector<int>(X.size()));

//    std::cout << matrix.size() << std::endl;
//    std::cout << matrix[0].size() << std::endl;

//    for (int jj = 0 ; jj < X.size() ; ++jj)
//        if(isSameX(i, jj))
//        {
//            matrix[Y.size() - 1][jj] += raw[i].quantity;
//            return true;
//        }
//    X.push_back(raw[i].date);
//    matrix.end()->push_back(raw[i].quantity);
//    for(int _i = 0; _i < matrix.size() - 1; ++_i)
//        matrix[_i].push_back(0);
    return true;
}

bool Processor::processAll()
{
    int i = 0;
    X[0] = getX(0);
    Y[0] = getY(0);
    while(process(i)) ++i;
    sortByX();
    return i == raw.size();
}

void Processor::sortByX()
{
    for(int i = 0; i < X.size(); ++i)
    {
        int min = i;
        for(int j = i+1; j < X.size(); ++j)
            if(X[j] < X[min])
            {
                min = j;
                std::swap (X[i], X[min]);
                for(int k = 0; k <Y.size(); ++k)
                    std::swap (matrix[k][i], matrix[k][min]);
            }
    }
}

QVector<QString> Processor::getYvector()
{
    QVector <QString> result;
    for(int i = 0; i < Y.size(); ++i)
        result.push_back(nameMap.value(Y[i]));
    return result;
}
