#include "confectionery.h"

Confectionery::Confectionery()
    : Stock(), weight(0)
{
}

Confectionery::Confectionery(const QString& i, int q, int w)
    : Stock(i, q), weight(w)
{
}

int Confectionery::getWeight() const
{
    return weight;
}

void Confectionery::setWeight(int w)
{
    weight = w;
}

QString Confectionery::toString() const
{
    return QString("Item: %1, Quantity: %2, Weight: %3").arg(getItem()).arg(getQuantity()).arg(weight);
}
