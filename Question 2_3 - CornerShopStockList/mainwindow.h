#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include "stockfactory.h"
#include "stocklist.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddButtonClicked();
    void onXMLButtonClicked();
    void onConfectioneryListSelected();
    void onReadingMaterialListSelected();

private:
    void setupUi();
    void populateStockList(QList<Stock*> stockList);
    void clearStockList();
    void writeStockListToXml(const QString& fileName);

    QListWidget* stockListWidget;
    QPushButton* addButton;
    QRadioButton* confectioneryRadioButton;
    QRadioButton* readingMaterialRadioButton;
    QLabel* nameLabel;
    QLineEdit* nameLineEdit;
    QLabel* frequencyLabel;
    QLineEdit* frequencyLineEdit;
    QLabel* quantityLabel;
    QSpinBox* quantitySpinBox;
    QLabel* weightLabel;
    QSpinBox* weightSpinBox;
    QPushButton* XMLButton;
};

#endif // MAINWINDOW_H
