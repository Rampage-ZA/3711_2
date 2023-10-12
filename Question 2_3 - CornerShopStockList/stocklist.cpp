#include "stocklist.h"


StockList* StockList::instance = nullptr;

StockList::StockList()
{
}

StockList* StockList::getInstance()
{
    if (!instance)
    {
        instance = new StockList();
    }
    return instance;
}

void StockList::addStock(Stock* stock)
{
    if (dynamic_cast<Confectionery*>(stock))
    {
        confectioneryList.append(stock);
    }
    else if (dynamic_cast<ReadingMaterial*>(stock))
    {
        readingMaterialList.append(stock);
    }
}

QList<Stock*> StockList::getConfectioneryList() const
{
    return confectioneryList;
}

QList<Stock*> StockList::getReadingMaterialList() const
{
    return readingMaterialList;
}
