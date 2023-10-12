#ifndef CONFECTIONERY_H
#define CONFECTIONERY_H

#include "stock.h"

class Confectionery : public Stock
{
public:
    Confectionery();
    Confectionery(const QString& i, int q, int w);
    int getWeight() const;
    void setWeight(int w);
    QString toString() const override;

private:
    int weight;
};

#endif // CONFECTIONERY_H
