#ifndef REPRESENTATIVEWIDGET_H
#define REPRESENTATIVEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "../inputWidget/textInputWidget.h"

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


private:
};

#endif //REPRESENTATIVEWIDGET_H
