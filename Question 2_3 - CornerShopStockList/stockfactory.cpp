#include "stockfactory.h"
#include "confectionery.h"
#include "readingmaterial.h"

Stock* StockFactory::createStock(const QString& type, const QString& item, int quantity, int weight)
{
    if (type == "Confectionery")
    {
        return new Confectionery(item, quantity, weight);
    }
    else if (type == "ReadingMaterial")
    {
        return new ReadingMaterial(item, quantity, "");
    }

    return nullptr;
}

Stock* StockFactory::createStock(const QString& type, const QString& item, int quantity, const QString& frequency)
{
    if (type == "Confectionery")
    {
        return new Confectionery(item, quantity, 0);
    }
    else if (type == "ReadingMaterial")
    {
        return new ReadingMaterial(item, quantity, frequency);
    }

    return nullptr;
}
