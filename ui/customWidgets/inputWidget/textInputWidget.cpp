#include "textInputWidget.h"

textInputWidget::textInputWidget(const QString& inputLabel, QWidget *parent) : QWidget(parent)
 {
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    label = new QLabel(inputLabel, this);

    layout->addWidget(label);

    input = new QLineEdit(this);

    layout->addWidget(input);
}