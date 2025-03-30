#include "./productWidget.h"

#include <QtGui/qvalidator.h>

productWidget::productWidget(QWidget *parent) : QWidget(parent) {
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setContentsMargins(10, 5, 10, 5);
    verticalLayout = new QVBoxLayout();
    //parent not required, as it is overwritten by adding to a layout
    name = new textInputWidget("Name");
    // require a space every 50 chars
    const QRegularExpression regex("^(?:(?=.{0,50}$)\\S+|(?:\\S{0,50}\\s+)+\\S{0,50})$");
    const QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(regex, name->input);
    name->input->setValidator(nameValidator);
    verticalLayout->addWidget(name);


    horizontalLayout->addLayout(verticalLayout);

    ppe = new textInputWidget("PPE in €");

    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ppe->input->sizePolicy().hasHeightForWidth());
    ppe->input->setSizePolicy(sizePolicy);
    ppe->input->setFixedWidth(100);

    const QLocale locale = QLocale::system();
    // Note: Validator is safely deleted in line 52, Memory Leak Warning can be ignored
    QDoubleValidator* validator = new QDoubleValidator(ppe->input);
    validator->setBottom(0.0);
    validator->setDecimals(6);
    validator->setTop(99999999999999.999999);
    validator->setLocale(locale);

    ppe->input->setValidator( validator );

    horizontalLayout->addWidget(ppe);

    count = new spinBoxInputWidget("Anzahl");

    sizePolicy.setHeightForWidth(count->input->sizePolicy().hasHeightForWidth());
    count->input->setSizePolicy(sizePolicy);
    count->input->setFixedWidth(100);
    count->input->setValue(1);
    count->input->setMaximum(99999);

    horizontalLayout->addWidget(count);

    deleteButton = new QPushButton("Löschen");

    horizontalLayout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, &productWidget::handleDelete);
}

void productWidget::handleDelete() {
    delete this->ppe->input->validator();
    emit requestDeletion(this);
}
