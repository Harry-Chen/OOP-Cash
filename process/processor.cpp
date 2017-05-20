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
bool Processor::isSameY(int i1, int i2)
{
    return getY(i1) == getY(i2);
}

bool Processor::process(int i)
{
    if(i == raw.size()) return false;
    for(int ii = 0 ; ii < matrix.size() ;++ii)
        if(isSameY(i, ii))
            {
                for (int jj = 0 ; jj < matrix[ii].size() ; ++jj)
                    if(isSameX(i, jj)) { matrix[ii][jj] += raw[i].quantity; return true;}
                X.push_back(raw[i].date);
                matrix[ii].push_back(raw[i].quantity);
                return true;
            }
    Y.push_back(getY(i));
    for (int jj = 0 ; jj < matrix[i].size() ; ++jj)
        if(isSameX(i, jj)) {matrix[i][jj] += raw[i].quantity; return true;}
    X.push_back(raw[i].date);
    matrix[i].push_back(raw[i].quantity);
    return true;
}

bool Processor::processAll()
{
    int i = 0;
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
            if(X[j] < X[min]) min = j;
        std::swap(X[i], X[min]);
        std::swap(matrix[i], matrix[min]);
    }
}
