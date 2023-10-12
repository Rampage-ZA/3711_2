#ifndef READINGMATERIAL_H
#define READINGMATERIAL_H

#include "stock.h"

class ReadingMaterial : public Stock
{
public:
    ReadingMaterial();
    ReadingMaterial(const QString& i, int q, const QString& f);
    QString getFrequency() const;
    void setFrequency(const QString& f);
    QString toString() const override;

private:
    QString frequency;
};

#endif // READINGMATERIAL_H
