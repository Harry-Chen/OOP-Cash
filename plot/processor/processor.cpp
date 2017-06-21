#include "processor.h"

bool Processor::Process(int i)
{
    if(i == bills_.size()) return false;
    int indexX = dates_.indexOf(GetDate(i));
    int indexY = fieldnames_.indexOf(GetFieldname(i));
    if(indexX != -1 && indexY != -1){
        matrix_[indexY][indexX] += bills_[i].quantity;
    }
    else if(indexX != -1 && indexY == -1){
        matrix_.push_back(QVector<int>(dates_.size(),0));
        fieldnames_.push_back(GetFieldname(i));
        matrix_[fieldnames_.size() - 1][indexX] += bills_[i].quantity;
    }
    else if(indexX == -1 && indexY != -1){
        for(int j = 0; j < fieldnames_.size(); ++j)
            matrix_[j].push_back(0);
        dates_.push_back(GetDate(i));
        matrix_[indexY][dates_.size() - 1] += bills_[i].quantity;
    }
    else{
        matrix_.push_back(QVector<int>(dates_.size() + 1,0));
        for(int j = 0; j < fieldnames_.size(); ++j)
            matrix_[j].push_back(0);
        fieldnames_.push_back(GetFieldname(i));
        dates_.push_back(GetDate(i));
        matrix_[fieldnames_.size() - 1][dates_.size() - 1] += bills_[i].quantity;
    }
    return true;
}

bool Processor::ProcessAll()
{
    int i = 0;
    while(Process(i)) ++i;
    Sort();
    return i == bills_.size();
}

const QVector<QString> Processor::GetFieldnames()
{
    QVector <QString> result;
    for(int i = 0; i < fieldnames_.size(); ++i)
        result.push_back(nameMap_.value(fieldnames_[i]));
    return result;
}
