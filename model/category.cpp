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
 * @file   category.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class Category
 */

#include <QString>
#include <sstream>
#include "util/constants.h"
#include "database/tables.h"
#include "model/category.h"

Category::Category(ID _id, QString _name, ID _uid):
    id(_id), name(_name), uid(_uid){}

Category::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

Table::Category Category::TABLE = Table::Category();

std::ostream& operator<<(std::ostream& os, const Category& dt)
{
    os << "Category info: id " << dt.id
       << ", name " << dt.name.toStdString()
       << ", uid " << dt.uid;
    return os;
}
