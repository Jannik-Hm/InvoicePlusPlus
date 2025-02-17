#ifndef TEXTINPUTWIDGET_H
#define TEXTINPUTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class textInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit textInputWidget(const QString& inputLabel, QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QLabel *label;
    QLineEdit *input;


private:
};

#endif //TEXTINPUTWIDGET_H
