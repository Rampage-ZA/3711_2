#include "readingmaterial.h"

ReadingMaterial::ReadingMaterial()
    : Stock(), frequency("")
{
}

ReadingMaterial::ReadingMaterial(const QString& i, int q, const QString& f)
    : Stock(i, q), frequency(f)
{
}

QString ReadingMaterial::getFrequency() const
{
    return frequency;
}

void ReadingMaterial::setFrequency(const QString& f)
{
    frequency = f;
}

QString ReadingMaterial::toString() const
{
    return QString("Item: %1, Quantity: %2, Frequency: %3").arg(getItem()).arg(getQuantity()).arg(frequency);
}
