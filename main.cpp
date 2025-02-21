#include "ui/mainwindow.h"

#include <QApplication>

#include "pdf/invoice.h"
#include "data_objects/invoice_data.h"
#include "data_objects/product.h"

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
    InvoiceData* invoice_data = new InvoiceData();
    invoice_data->sender_name = "Fritz Fröhlich";
    invoice_data->products = {
        new Product("Macbook", 3, 1499.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Something", 1, 5),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        new Product("Something", 1, 5),
        // new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        // new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99),
        // new Product("Samsung Galaxy S20\nGebraucht", 2, 1099.99)
    };
    Invoice* invoice = new Invoice(invoice_data);
    invoice->generate();
}
