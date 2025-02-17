#include "spinBoxInputWidget.h"

spinBoxInputWidget::spinBoxInputWidget(const QString& inputLabel, QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    label = new QLabel(inputLabel, this);

    layout->addWidget(label);

    input = new QSpinBox(this);

    layout->addWidget(input);
}