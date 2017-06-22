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
 * @file   processor.cpp
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Implementation file of class Processor
 */

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

void Processor::Sort()
{
    for(int i = 0; i < dates_.size(); ++i)
        for(int j = 1; j < dates_.size() - i; ++j)
        {
            if(dates_[j] < dates_[j - 1])
            {
                std::swap(dates_[j], dates_[j - 1]);
                std::swap(matrix_[j], matrix[j - 1]);
            }
        }
}
