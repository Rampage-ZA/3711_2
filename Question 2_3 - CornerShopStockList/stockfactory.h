#ifndef STOCKFACTORY_H
#define STOCKFACTORY_H

#include "stock.h"


class StockFactory
{
public:
    static Stock* createStock(const QString& type, const QString& item, int quantity, int weight);
    static Stock* createStock(const QString& type, const QString& item, int quantity, const QString& frequency);
};

#endif // STOCKFACTORY_H
