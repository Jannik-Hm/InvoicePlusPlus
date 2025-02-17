#include "representativeWidget.h"

#include <QtCore/qcoreapplication.h>
#include <QtGui/qvalidator.h>

representativeWidget::representativeWidget(QWidget *parent) : QWidget(parent) {
    representative_layout = new QVBoxLayout(this);
    representative_layout->setContentsMargins(0, 0, 0, 0);
    name = new textInputWidget("Name", this);

    representative_layout->addWidget(name);

    street_house_horizontal = new QHBoxLayout();
    street = new textInputWidget("Straße", this);
    street->input->setMinimumWidth(250);
    street_house_horizontal->addWidget(street);

    housenumber = new textInputWidget("Hausnummer", this);
    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(housenumber->input->sizePolicy().hasHeightForWidth());
    housenumber->input->setSizePolicy(sizePolicy);
    housenumber->input->setFixedWidth(90);
    housenumber->input->setValidator( new QIntValidator() );

    street_house_horizontal->addWidget(housenumber);


    representative_layout->addLayout(street_house_horizontal);

    zip_city_horizontal = new QHBoxLayout();
    zipcode = new textInputWidget("Postleitzahl", this);
    sizePolicy.setHeightForWidth(zipcode->input->sizePolicy().hasHeightForWidth());
    zipcode->input->setSizePolicy(sizePolicy);
    zipcode->input->setFixedWidth(100);
    zipcode->input->setValidator( new QIntValidator(0, 99999) );

    zip_city_horizontal->addWidget(zipcode);

    city = new textInputWidget("Stadt", this);
    zip_city_horizontal->addWidget(city);


    representative_layout->addLayout(zip_city_horizontal);
}
