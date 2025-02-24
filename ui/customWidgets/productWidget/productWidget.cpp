#include "./productWidget.h"

#include <QtGui/qvalidator.h>

productWidget::productWidget(QWidget *parent) : QWidget(parent) {
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setContentsMargins(10, 5, 10, 5);
    verticalLayout = new QVBoxLayout();
    //parent not required, as it is overwritten by adding to a layout
    name = new textInputWidget("Name");
    verticalLayout->addWidget(name);


    horizontalLayout->addLayout(verticalLayout);

    ppe = new textInputWidget("PPE in €");

    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ppe->input->sizePolicy().hasHeightForWidth());
    ppe->input->setSizePolicy(sizePolicy);
    ppe->input->setFixedWidth(100);
    ppe->input->setValidator( new QDoubleValidator(ppe) );

    horizontalLayout->addWidget(ppe);

    count = new spinBoxInputWidget("Anzahl");

    sizePolicy.setHeightForWidth(count->input->sizePolicy().hasHeightForWidth());
    count->input->setSizePolicy(sizePolicy);
    count->input->setFixedWidth(100);
    count->input->setValue(1);

    horizontalLayout->addWidget(count);

    deleteButton = new QPushButton("Löschen");

    horizontalLayout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, &productWidget::handleDelete);
}

void productWidget::handleDelete() {
    emit requestDeletion(this);
}
