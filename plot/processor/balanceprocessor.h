﻿#ifndef BALANCEPROCESSOR_H
#define BALANCEPROCESSOR_H

#include "processor.h"

class BalanceProcessor : public Processor
{
    ID GetFieldname(int i);
public:
    using Processor::Processor;
    bool ProcessAll();
};

#endif // BALANCEPROCESSOR_H
