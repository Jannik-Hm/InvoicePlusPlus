#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "customWidgets/productWidget/productWidget.h"
#include "customWidgets/representativeWidget/representativeWidget.h"
#include "customWidgets/inputWidget/textInputWidget.h"
#include "customWidgets/inputWidget/dateInputWidget.h"
#include <QtCore/qcoreapplication.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *representatives_layout;

    QVBoxLayout *sender_layout;
    QLabel *sender_label;
    representativeWidget *sender;

    QSpacerItem *recipients_spacer;

    QVBoxLayout *recipient_layout;
    QLabel *recipient_label;
    representativeWidget *recipient;
    QHBoxLayout *number_date_horizontal;
    textInputWidget *invoice_number;
    dateInputWidget *invoice_service_date;
    textInputWidget *invoice_title;
    QLabel *footer_label;
    QHBoxLayout *banking_horizontal;
    textInputWidget *iban;
    textInputWidget *bic;
    textInputWidget *tax_number;
    QHBoxLayout *product_label_create_horizontal;
    QLabel *products_label;
    QListWidget *productList;
    QPushButton *add_product_button;
    QSpacerItem *add_product_button_space_right;
    QHBoxLayout *generate_invoice_button_center_layout;
    QSpacerItem *generate_invoice_button_space_left;
    QPushButton *generate_invoice_button;
    QSpacerItem *generate_invoice_button_space_right;

private slots:
    void addProductWidget();
    void removeProductWidget(const productWidget *widget) const;
    void generateInvoice();

private:
};
#endif // MAINWINDOW_H
