#include "processorbase.h"

ProcessorBase::ProcessorBase()
{
    X.clear();
    Y.clear();
    matrix.clear();
    QVector<int> temp(1,0);
    matrix.push_back(temp);
    X.push_back(QDate());
    Y.push_back(0);
}

bool ProcessorBase::process(int i)
{
    if(i == raw.size()) return false;
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
    return true;
}
/*
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
*/


void ProcessorBase::sortByX()
{
    for(int i = 0; i < X.size() - 1; ++i)
    {
        for(int j = 0; j < X.size() - i - 1; ++j)
            if(X[j] > X[j + 1])
            {
                std::swap (X[j], X[j + 1]);
                for(int k = 0; k <Y.size(); ++k)
                    std::swap (matrix[k][j], matrix[k][j + 1]);
            }
    }
}

bool ProcessorBase::processAll()
{
    int i = 0;
    X[0] = this->getX(0);
    Y[0] = this->getY(0);
    while(process(i)) ++i;
    sortByX();
    return i == raw.size();
}

const QVector<QString> & ProcessorBase::getYvector()
{
    QVector <QString> result;
    for(int i = 0; i < Y.size(); ++i)
        result.push_back(nameMap.value(Y[i]));
    return result;
}
