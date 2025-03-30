#include "representativeWidget.h"

#include <QtCore/qcoreapplication.h>
#include <QtGui/qvalidator.h>

representativeWidget::representativeWidget(QWidget *parent) : QWidget(parent) {
    representative_layout = new QVBoxLayout(this);
    representative_layout->setContentsMargins(0, 0, 0, 0);
    name = new textInputWidget("Name");
    name->input->setMaxLength(30);

    representative_layout->addWidget(name);

    // parent will be set by adding to layout
    street_house_horizontal = new QHBoxLayout();
    street = new textInputWidget("Straße");
    street->input->setMinimumWidth(250);
    street->input->setMaxLength(25);
    street_house_horizontal->addWidget(street);

    housenumber = new textInputWidget("Hausnummer");
    housenumber->input->setMaxLength(4);
    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(housenumber->input->sizePolicy().hasHeightForWidth());
    housenumber->input->setSizePolicy(sizePolicy);
    housenumber->input->setFixedWidth(90);
    housenumber->input->setValidator(new QIntValidator(housenumber));

    street_house_horizontal->addWidget(housenumber);


    representative_layout->addLayout(street_house_horizontal);

    zip_city_horizontal = new QHBoxLayout();
    zip_city_horizontal->setContentsMargins(0, 0, 0, 0);
    zipcode = new textInputWidget("Postleitzahl");
    sizePolicy.setHeightForWidth(zipcode->input->sizePolicy().hasHeightForWidth());
    zipcode->input->setSizePolicy(sizePolicy);
    zipcode->input->setFixedWidth(100);
    zipcode->input->setValidator(new QIntValidator(zipcode));
    zipcode->input->setMaxLength(5);

    zip_city_horizontal->addWidget(zipcode);

    city = new textInputWidget("Stadt");
    city->input->setMaxLength(25);
    zip_city_horizontal->addWidget(city);


    representative_layout->addLayout(zip_city_horizontal);
    this->setLayout(representative_layout);
}
