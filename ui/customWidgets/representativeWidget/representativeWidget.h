#ifndef REPRESENTATIVEWIDGET_H
#define REPRESENTATIVEWIDGET_H

#include "../inputWidget/textInputWidget.h"

/// @brief the respective widget for entering representative data
class representativeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit representativeWidget(QWidget *parent = nullptr);
    QVBoxLayout *representative_layout;
    textInputWidget *name;
    QHBoxLayout *street_house_horizontal;
    textInputWidget *street;
    textInputWidget *housenumber;
    QHBoxLayout *zip_city_horizontal;
    textInputWidget *zipcode;
    textInputWidget *city;

};

#endif //REPRESENTATIVEWIDGET_H
