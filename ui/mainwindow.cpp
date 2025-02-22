#include "mainwindow.h"
#include "../data_objects/invoice_data.h"
#include "../data_objects/product_data.h"
#include "../data_objects/representative_data.h"
#include "../pdf/invoice.h"

#include "customWidgets/inputWidget/dateInputWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    if (this->objectName().isEmpty())
        this->resize(800, 800);
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

    footer_label = new QLabel("Fußzeile", centralwidget);
    verticalLayout->addWidget(footer_label);

    //TODO: needs styling (width) + regex validator
    banking_horizontal = new QHBoxLayout();
    iban = new textInputWidget("IBAN", centralwidget);
    banking_horizontal->addWidget(iban);
    bic = new textInputWidget("BIC", centralwidget);
    banking_horizontal->addWidget(bic);
    verticalLayout->addLayout(banking_horizontal);

    tax_number = new textInputWidget("Steuernummer", centralwidget);
    verticalLayout->addWidget(tax_number);

    product_label_create_horizontal = new QHBoxLayout();
    products_label = new QLabel(centralwidget);
    product_label_create_horizontal->addWidget(products_label);

    add_product_button = new QPushButton(centralwidget);
    product_label_create_horizontal->addWidget(add_product_button);

    add_product_button_space_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    product_label_create_horizontal->addItem(add_product_button_space_right);

    verticalLayout->addLayout(product_label_create_horizontal);

    productList = new QListWidget(centralwidget);

    verticalLayout->addWidget(productList);

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
    connect(generate_invoice_button, &QPushButton::clicked, this, &MainWindow::generateInvoice);
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

void MainWindow::generateInvoice() const {

    std::list<ProductData*> products = {};

    for (int row = 0; row < this->productList->count(); row++)
    {
        QListWidgetItem *item = this->productList->item(row);
        QWidget* child = productList->itemWidget(item);
        // products.push_back(new ProductData(item->));
        if (productWidget* product_widget = dynamic_cast<productWidget*>(child)) {
            products.push_back(new ProductData(product_widget->name->input->text().toStdString(), product_widget->count->input->value(), product_widget->ppe->input->text().toDouble()));
        }
    }

    InvoiceData* invoice_data = new InvoiceData();
    invoice_data->sender = new RepresentativeData(this->sender->name->input->text().toStdString(), this->sender->street->input->text().toStdString(), this->sender->housenumber->input->text().toStdString(), this->sender->zipcode->input->text().toStdString(), this->sender->city->input->text().toStdString());
    invoice_data->recipient = new RepresentativeData(this->recipient->name->input->text().toStdString(), this->recipient->street->input->text().toStdString(), this->recipient->housenumber->input->text().toStdString(), this->recipient->zipcode->input->text().toStdString(), this->recipient->city->input->text().toStdString());
    invoice_data->invoice_number = this->invoice_number->input->text().toStdString();
    invoice_data->invoice_service_date = this->invoice_service_date->input->date();
    invoice_data->invoice_title = this->invoice_title->input->text().toStdString();
    invoice_data->iban = this->iban->input->text().toStdString();
    invoice_data->bic = this->bic->input->text().toStdString();
    invoice_data->tax_number = this->tax_number->input->text().toStdString();
    invoice_data->products = products;
    Invoice* invoice = new Invoice(invoice_data);
    invoice->generate();
}
