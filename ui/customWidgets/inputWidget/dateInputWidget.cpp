#include "dateInputWidget.h"

dateInputWidget::dateInputWidget(const QString& inputLabel, QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    label = new QLabel(inputLabel);

    layout->addWidget(label);

    input = new QDateEdit();
    input->setCalendarPopup(true);

    layout->addWidget(input);
}