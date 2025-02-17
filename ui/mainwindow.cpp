#include "mainwindow.h"
#include <chrono>

#include "customWidgets/inputWidget/dateInputWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    if (this->objectName().isEmpty())
        this->resize(800, 600);
    centralwidget = new QWidget(this);
    verticalLayout = new QVBoxLayout(centralwidget);
    representatives_layout = new QHBoxLayout();

    sender_layout = new QVBoxLayout();
    sender_label = new QLabel(centralwidget);
    sender_layout->addWidget(sender_label);
    sender = new representativeWidget();
    sender_layout->addWidget(sender);
    representatives_layout->addLayout(sender_layout);

    recipients_spacer = new QSpacerItem(50, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

    representatives_layout->addItem(recipients_spacer);

    recipient_layout = new QVBoxLayout();
    recipient_label = new QLabel(centralwidget);
    recipient_layout->addWidget(recipient_label);
    recipient = new representativeWidget();
    recipient_layout->addWidget(recipient);
    representatives_layout->addLayout(recipient_layout);

    verticalLayout->addLayout(representatives_layout);

    number_date_horizontal = new QHBoxLayout();

    invoice_number = new textInputWidget("Rechnungsnummer", centralwidget);
    number_date_horizontal->addWidget(invoice_number);

    invoice_service_date = new dateInputWidget("Leistungsdatum", centralwidget);
    invoice_service_date->input->setMinimumDate(QDate(1900, 1, 1));
    invoice_service_date->input->setDate(QDate::currentDate());
    invoice_service_date->input->setMaximumDate(QDate::currentDate());

    number_date_horizontal->addWidget(invoice_service_date);


    verticalLayout->addLayout(number_date_horizontal);

    invoice_title = new textInputWidget("Rechnungstitel", centralwidget);
    invoice_title->input->setPlaceholderText("Projekt XY");

    verticalLayout->addWidget(invoice_title);

    products_label = new QLabel(centralwidget);

    verticalLayout->addWidget(products_label);

    productList = new QListWidget(centralwidget);

    verticalLayout->addWidget(productList);

    add_product_button_center_layout = new QHBoxLayout();

    add_product_button_space_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    add_product_button_center_layout->addItem(add_product_button_space_left);

    add_product_button = new QPushButton(centralwidget);
    add_product_button_center_layout->addWidget(add_product_button);

    add_product_button_space_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    add_product_button_center_layout->addItem(add_product_button_space_right);


    verticalLayout->addLayout(add_product_button_center_layout);

    generate_invoice_button_center_layout = new QHBoxLayout();

    generate_invoice_button_space_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    generate_invoice_button_center_layout->addItem(generate_invoice_button_space_left);

    generate_invoice_button = new QPushButton(centralwidget);
    generate_invoice_button_center_layout->addWidget(generate_invoice_button);

    generate_invoice_button_space_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    generate_invoice_button_center_layout->addItem(generate_invoice_button_space_right);


    verticalLayout->addLayout(generate_invoice_button_center_layout);

    this->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    sender_label->setText(QCoreApplication::translate("MainWindow", "Sender", nullptr));
    recipient_label->setText(QCoreApplication::translate("MainWindow", "Empfänger", nullptr));
    invoice_service_date->input->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd.MM.yyyy", nullptr));
    products_label->setText(QCoreApplication::translate("MainWindow", "Produkte", nullptr));
    add_product_button->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
    generate_invoice_button->setText(QCoreApplication::translate("MainWindow", "Generieren", nullptr));

    this->setCentralWidget(centralwidget);

    connect(add_product_button, &QPushButton::clicked, this, &MainWindow::addProductWidget);
}

void MainWindow::addProductWidget() {
    productWidget *customWidget = new productWidget(this);
    QListWidgetItem *item = new QListWidgetItem(productList);
    item->setSizeHint(customWidget->sizeHint());
    productList->setItemWidget(item, customWidget);

    connect(customWidget, &productWidget::requestDeletion, this, &MainWindow::removeProductWidget);
}

void MainWindow::removeProductWidget(const productWidget *widget) const {
    for (int i = 0; i < productList->count(); ++i) {
        QListWidgetItem *item = productList->item(i);
        if (productList->itemWidget(item) == widget) {
            delete productList->takeItem(i);
            break;
        }
    }
}
