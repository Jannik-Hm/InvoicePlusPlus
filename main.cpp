#include "ui/mainwindow.h"

#include <QApplication>

#include "pdf/invoice.h"
#include "data_objects/invoice_data.h"
#include "data_objects/product_data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
