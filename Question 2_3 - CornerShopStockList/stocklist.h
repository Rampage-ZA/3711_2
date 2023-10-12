#ifndef STOCKLIST_H
#define STOCKLIST_H

#include <QList>
#include "stock.h"
#include "confectionery.h"
#include "readingmaterial.h"

class StockList
{
public:
    static StockList* getInstance();
    void addStock(Stock* stock);
    QList<Stock*> getConfectioneryList() const;
    QList<Stock*> getReadingMaterialList() const;

private:
    StockList();
    static StockList* instance;
    QList<Stock*> confectioneryList;
    QList<Stock*> readingMaterialList;
};

#endif // STOCKLIST_H
