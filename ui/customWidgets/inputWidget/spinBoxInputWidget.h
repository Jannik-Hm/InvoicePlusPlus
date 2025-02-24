#ifndef SPININPUTWIDGET_H
#define SPININPUTWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>

/// @brief a Widget containing a label and a spinbox (int input) below
class spinBoxInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit spinBoxInputWidget(const QString& inputLabel, QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QLabel *label;
    QSpinBox *input;


private:
};

#endif //SPININPUTWIDGET_H
