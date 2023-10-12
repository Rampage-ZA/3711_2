#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QXmlStreamWriter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

void MainWindow::setupUi()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    stockListWidget = new QListWidget(centralWidget);
    stockListWidget->setSelectionMode(QAbstractItemView::NoSelection);

    addButton = new QPushButton("Add Item to Stock list", centralWidget);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);

    //
    XMLButton = new QPushButton("Generate XML Stock list", centralWidget);
    connect(XMLButton, &QPushButton::clicked, this, &MainWindow::onXMLButtonClicked);
   //

    confectioneryRadioButton = new QRadioButton("Confectionery", centralWidget);
    connect(confectioneryRadioButton, &QRadioButton::clicked, this, &MainWindow::onConfectioneryListSelected);

    readingMaterialRadioButton = new QRadioButton("Reading Material", centralWidget);
    connect(readingMaterialRadioButton, &QRadioButton::clicked, this, &MainWindow::onReadingMaterialListSelected);

    nameLabel = new QLabel ("Name of item: ");
    nameLineEdit = new QLineEdit(centralWidget);

    frequencyLabel = new QLabel ("Frequency (for publications): ");
    frequencyLineEdit = new QLineEdit(centralWidget);

    quantityLabel = new QLabel ("Quantity: ");
    quantitySpinBox = new QSpinBox(centralWidget);

    weightLabel = new QLabel ("Weight (for confectionaries): ");
    weightSpinBox = new QSpinBox(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(stockListWidget);

    layout->addWidget(XMLButton);
    layout->addWidget(confectioneryRadioButton);
    layout->addWidget(readingMaterialRadioButton);

    layout->addWidget(nameLabel);
    layout->addWidget(nameLineEdit);
    layout->addWidget(frequencyLabel);
    layout->addWidget(frequencyLineEdit);
    layout->addWidget(quantityLabel);
    layout->addWidget(quantitySpinBox);
    layout->addWidget(weightLabel);
    layout->addWidget(weightSpinBox);
    layout->addWidget(addButton);

    confectioneryRadioButton->setChecked(true);
    onConfectioneryListSelected();
}

void MainWindow::onAddButtonClicked()
{
    QString item = nameLineEdit->text();
    int quantity = quantitySpinBox->value();

    if (confectioneryRadioButton->isChecked())
    {
        int weight = weightSpinBox->value();
        Stock* confectionery = StockFactory::createStock("Confectionery", item, quantity, weight);
        StockList::getInstance()->addStock(confectionery);
    }
    else if (readingMaterialRadioButton->isChecked())
    {
        QString frequency = frequencyLineEdit->text();
        Stock* readingMaterial = StockFactory::createStock("ReadingMaterial", item, quantity, frequency);
        StockList::getInstance()->addStock(readingMaterial);
    }

    clearStockList();
    if (confectioneryRadioButton->isChecked())
    {
        onConfectioneryListSelected();
    }
    else if (readingMaterialRadioButton->isChecked())
    {
        onReadingMaterialListSelected();
    }
}

void::MainWindow::onXMLButtonClicked()
{
    writeStockListToXml("stocklist.xml");
}

void MainWindow::onConfectioneryListSelected()
{
    clearStockList();
    populateStockList(StockList::getInstance()->getConfectioneryList());
    frequencyLineEdit->setEnabled(false);
    weightSpinBox->setEnabled(true);
}

void MainWindow::onReadingMaterialListSelected()
{
    clearStockList();
    populateStockList(StockList::getInstance()->getReadingMaterialList());
    frequencyLineEdit->setEnabled(true);
    weightSpinBox->setEnabled(false);
}

void MainWindow::populateStockList(QList<Stock*> stockList)
{
    for (Stock* stock : stockList)
    {
        stockListWidget->addItem(stock->toString());
    }
}

void MainWindow::clearStockList()
{
    stockListWidget->clear();
    nameLineEdit->clear();
    frequencyLineEdit->clear();
    quantitySpinBox->setValue(0);
    weightSpinBox->setValue(0);
}



void MainWindow::writeStockListToXml(const QString& fileName)
{

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Handle file open error
        QMessageBox msgBox;
        msgBox.setText("Error opening file.");
        msgBox.exec();

        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("stockList");

    QList<Stock*> confectioneryList = StockList::getInstance()->getConfectioneryList();
    QList<Stock*> readingMaterialList = StockList::getInstance()->getReadingMaterialList();

    // Write confectionery items
    for (Stock* stock : confectioneryList)
    {
        Confectionery* confectionery = dynamic_cast<Confectionery*>(stock);
        if (confectionery)
        {
            xmlWriter.writeStartElement("stockItem");
            xmlWriter.writeAttribute("type", "Confectionery");

            xmlWriter.writeTextElement("item", confectionery->getItem());
            xmlWriter.writeTextElement("quantity", QString::number(confectionery->getQuantity()));
            xmlWriter.writeTextElement("weight", QString::number(confectionery->getWeight()));

            xmlWriter.writeEndElement(); // stockItem
        }
    }

    // Write reading material items
    for (Stock* stock : readingMaterialList)
    {
        ReadingMaterial* readingMaterial = dynamic_cast<ReadingMaterial*>(stock);
        if (readingMaterial)
        {
            xmlWriter.writeStartElement("stockItem");
            xmlWriter.writeAttribute("type", "ReadingMaterial");

            xmlWriter.writeTextElement("item", readingMaterial->getItem());
            xmlWriter.writeTextElement("quantity", QString::number(readingMaterial->getQuantity()));
            xmlWriter.writeTextElement("frequency", readingMaterial->getFrequency());

            xmlWriter.writeEndElement(); // stockItem
        }
    }

    xmlWriter.writeEndElement(); // stockList
    xmlWriter.writeEndDocument();

    file.close();

    QMessageBox msgBox;
    msgBox.setText("File written successfully.");
    msgBox.exec();
}
