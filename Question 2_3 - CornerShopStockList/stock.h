#ifndef STOCK_H
#define STOCK_H

#include <QString>

class Stock
{
public:
    Stock();
    Stock(const QString& i, int q);
    QString getItem() const;
    int getQuantity() const;
    void setItem(const QString& i);
    void setQuantity(int q);
    virtual QString toString() const = 0;

private:
    QString item;
    int quantity;
};

#endif // STOCK_H
