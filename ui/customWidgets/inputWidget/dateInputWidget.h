//
// Created by Jannik Heym on 17.02.25.
//

#ifndef DATEINPUTWIDGET_H
#define DATEINPUTWIDGET_H


#include <QWidget>
#include <QDateEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

/// @brief a Widget containing a label and a datepicker below
class dateInputWidget : public QWidget {
    Q_OBJECT

public:
    explicit dateInputWidget(const QString &inputLabel, QWidget *parent = nullptr);

    QVBoxLayout *layout;
    QLabel *label;
    QDateEdit *input;

private:
};


#endif //DATEINPUTWIDGET_H
