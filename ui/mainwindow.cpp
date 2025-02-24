#include "mainwindow.h"

#include <QMessageBox>

#include "../data_objects/invoice_data.h"
#include "../data_objects/product_data.h"
#include "../data_objects/representative_data.h"
#include "../pdf/invoice.h"
#include "../pdf/pdf_exception.h"

#include "customWidgets/inputWidget/dateInputWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    if (this->objectName().isEmpty())
        this->resize(800, 800);
    centralwidget = new QWidget(this);
    verticalLayout = new QVBoxLayout(centralwidget);
    representatives_layout = new QHBoxLayout();

    sender_layout = new QVBoxLayout();
    sender_label = new QLabel();
    sender_layout->addWidget(sender_label);
    sender = new representativeWidget();
    sender_layout->addWidget(sender);
    representatives_layout->addLayout(sender_layout);

    recipients_spacer = new QSpacerItem(50, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

    representatives_layout->addItem(recipients_spacer);

    recipient_layout = new QVBoxLayout();
    recipient_label = new QLabel();
    recipient_layout->addWidget(recipient_label);
    recipient = new representativeWidget();
    recipient_layout->addWidget(recipient);
    representatives_layout->addLayout(recipient_layout);

    verticalLayout->addLayout(representatives_layout);

    number_date_horizontal = new QHBoxLayout();

    invoice_number = new textInputWidget("Rechnungsnummer");
    number_date_horizontal->addWidget(invoice_number);

    invoice_service_date = new dateInputWidget("Leistungsdatum");
    invoice_service_date->input->setMinimumDate(QDate(1900, 1, 1));
    invoice_service_date->input->setDate(QDate::currentDate());
    invoice_service_date->input->setMaximumDate(QDate::currentDate());

    number_date_horizontal->addWidget(invoice_service_date);


    verticalLayout->addLayout(number_date_horizontal);

    invoice_title = new textInputWidget("Rechnungstitel");
    invoice_title->input->setPlaceholderText("Projekt XY");

    verticalLayout->addWidget(invoice_title);

    footer_label = new QLabel("Fußzeile");
    verticalLayout->addWidget(footer_label);

    //TODO: needs styling (width) + regex validator
    banking_horizontal = new QHBoxLayout();
    iban = new textInputWidget("IBAN");
    banking_horizontal->addWidget(iban);
    bic = new textInputWidget("BIC");
    banking_horizontal->addWidget(bic);
    verticalLayout->addLayout(banking_horizontal);

    tax_number = new textInputWidget("Steuernummer");
    verticalLayout->addWidget(tax_number);

    product_label_create_horizontal = new QHBoxLayout();
    products_label = new QLabel();
    product_label_create_horizontal->addWidget(products_label);

    add_product_button = new QPushButton();
    product_label_create_horizontal->addWidget(add_product_button);

    add_product_button_space_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding,
                                                     QSizePolicy::Policy::Minimum);
    product_label_create_horizontal->addItem(add_product_button_space_right);

    verticalLayout->addLayout(product_label_create_horizontal);

    productList = new QListWidget();

    verticalLayout->addWidget(productList);

    generate_invoice_button_center_layout = new QHBoxLayout();

    generate_invoice_button_space_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding,
                                                         QSizePolicy::Policy::Minimum);
    generate_invoice_button_center_layout->addItem(generate_invoice_button_space_left);

    generate_invoice_button = new QPushButton();
    generate_invoice_button_center_layout->addWidget(generate_invoice_button);

    generate_invoice_button_space_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding,
                                                          QSizePolicy::Policy::Minimum);
    generate_invoice_button_center_layout->addItem(generate_invoice_button_space_right);


    verticalLayout->addLayout(generate_invoice_button_center_layout);

    this->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    sender_label->setText(QCoreApplication::translate("MainWindow", "Verfasser", nullptr));
    recipient_label->setText(QCoreApplication::translate("MainWindow", "Empfänger", nullptr));
    invoice_service_date->input->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd.MM.yyyy", nullptr));
    products_label->setText(QCoreApplication::translate("MainWindow", "Produkte", nullptr));
    add_product_button->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
    generate_invoice_button->setText(QCoreApplication::translate("MainWindow", "Generieren", nullptr));

    this->setCentralWidget(centralwidget);

    connect(add_product_button, &QPushButton::clicked, this, &MainWindow::addProductWidget);
    connect(generate_invoice_button, &QPushButton::clicked, this, &MainWindow::generateInvoice);
    //TODO: some kind of user feedback, that generation succeeded -> QMessageBox
}

std::list<std::string> MainWindow::checkForMissingFields() const {
    std::list<std::string> missing_fields = {};
    if (this->sender->name->input->text() == "") {
        missing_fields.push_back("Verfasser Name wird benötigt");
    }
    if (this->sender->street->input->text() == "") {
        missing_fields.push_back("Verfasser Straße wird benötigt");
    }
    if (this->sender->housenumber->input->text() == "") {
        missing_fields.push_back("Verfasser Hausnummer wird benötigt");
    }
    if (this->sender->zipcode->input->text() == "") {
        missing_fields.push_back("Verfasser Postleitzahl wird benötigt");
    }
    if (this->sender->city->input->text() == "") {
        missing_fields.push_back("Verfasser Stadt wird benötigt");
    }
    if (this->recipient->name->input->text() == "") {
        missing_fields.push_back("Empfänger Name wird benötigt");
    }
    if (this->recipient->street->input->text() == "") {
        missing_fields.push_back("Empfänger Straße wird benötigt");
    }
    if (this->recipient->housenumber->input->text() == "") {
        missing_fields.push_back("Empfänger Hausnummer wird benötigt");
    }
    if (this->recipient->zipcode->input->text() == "") {
        missing_fields.push_back("Empfänger Postleitzahl wird benötigt");
    }
    if (this->recipient->city->input->text() == "") {
        missing_fields.push_back("Empfänger Stadt wird benötigt");
    }
    if (this->invoice_number->input->text() == "") {
        missing_fields.push_back("Rechnungsnummer wird benötigt");
    }
    if (this->invoice_title->input->text() == "") {
        missing_fields.push_back("Rechnungstitel wird benötigt");
    }
    if (this->iban->input->text() == "") {
        missing_fields.push_back("IBAN wird benötigt");
    }
    if (this->bic->input->text() == "") {
        missing_fields.push_back("BIC wird benötigt");
    }
    if (this->tax_number->input->text() == "") {
        missing_fields.push_back("Steuernummer wird benötigt");
    }
    if (this->productList->count() == 0) {
        missing_fields.push_back("Mindestens 1 Produkt wird benötigt");
    } else {
        // iterate through product list to check if name or ppe are missing
        bool is_missing_name = false;
        bool is_missing_ppe = false;
        for (int row = 0; row < this->productList->count(); row++) {
            QListWidgetItem *item = this->productList->item(row);
            QWidget *child = productList->itemWidget(item);
            if (productWidget *product_widget = dynamic_cast<productWidget *>(child)) {
                if (product_widget->name->input->text() == "") {
                    is_missing_name = true;
                }
                // count already has default value
                if (product_widget->ppe->input->text() == "") {
                    is_missing_ppe = true;
                }
                if (is_missing_name && is_missing_ppe) {
                    break;
                }
            }
        }
        if (is_missing_name) {
            missing_fields.push_back("Mindestens 1 Produkt fehlt der Name");
        }
        if (is_missing_ppe) {
            missing_fields.push_back("Mindestens 1 Produkt fehlt der PPE");
        }
    }
    return missing_fields;
}


void MainWindow::addProductWidget() {
    // will be deleted by Qt memory management when necessary
    QListWidgetItem *item = new QListWidgetItem(productList);
    productWidget *customWidget = new productWidget(this);
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

void MainWindow::generateInvoice() {
    if (std::list<std::string> missing_fields = checkForMissingFields(); missing_fields.size() > 0) {
        // merge list of error messages into \n seperated string
        const std::string text = std::accumulate(missing_fields.begin(), missing_fields.end(), std::string(),
                                                 [](const std::string &a, const std::string &b) {
                                                     return a.empty() ? b : a + "\n" + b;
                                                 });
        // display error message to the user
        QMessageBox::information(this, "Fehler", QString::fromStdString(text));
    } else {
        std::list<std::shared_ptr<ProductData>> products = {};

        // iterate through product list widget, create a ProductData Object for each entry and append to products list
        for (int row = 0; row < this->productList->count(); row++) {
            QListWidgetItem *item = this->productList->item(row);
            QWidget *child = productList->itemWidget(item);
            if (const productWidget *product_widget = dynamic_cast<productWidget *>(child)) {
                products.push_back(std::make_shared<ProductData>(product_widget->name->input->text().toStdString(),
                                                                 product_widget->count->input->value(),
                                                                 product_widget->ppe->input->text().toDouble()));
            }
        }

        // generate InvoiceData object from form widgets
        const std::shared_ptr<InvoiceData> invoice_data = std::make_shared<InvoiceData>();
        invoice_data->sender = std::make_shared<RepresentativeData>(this->sender->name->input->text().toStdString(),
                                                      this->sender->street->input->text().toStdString(),
                                                      this->sender->housenumber->input->text().toStdString(),
                                                      this->sender->zipcode->input->text().toStdString(),
                                                      this->sender->city->input->text().toStdString());
        invoice_data->recipient = std::make_shared<RepresentativeData>(this->recipient->name->input->text().toStdString(),
                                                         this->recipient->street->input->text().toStdString(),
                                                         this->recipient->housenumber->input->text().toStdString(),
                                                         this->recipient->zipcode->input->text().toStdString(),
                                                         this->recipient->city->input->text().toStdString());
        invoice_data->invoice_number = this->invoice_number->input->text().toStdString();
        invoice_data->invoice_service_date = this->invoice_service_date->input->date();
        invoice_data->invoice_title = this->invoice_title->input->text().toStdString();
        invoice_data->iban = this->iban->input->text().toStdString();
        invoice_data->bic = this->bic->input->text().toStdString();
        invoice_data->tax_number = this->tax_number->input->text().toStdString();
        invoice_data->products = products;
        const std::shared_ptr<Invoice> invoice = std::make_shared<Invoice>(invoice_data);
        // try to generate the pdf invoice and display success message with file location, display error code when pdf lib encounters error
        try {
            const std::string filepath = invoice->generate();
            QMessageBox::information(this, "Erfolg",
                                     QString::fromStdString("Rechnung unter " + filepath + " gespeichert"));
        } catch (PDFException &e) {
            HPDF_Free(invoice->pdf);
            QMessageBox::information(this, "Fehler", QString::fromStdString(e.message()));
        } catch (std::runtime_error &e) {
            HPDF_Free(invoice->pdf);
            QMessageBox::information(this, "Fehler", e.what());
        }

        // TODO: switch over to shared_ptr instead of new
    }
}
