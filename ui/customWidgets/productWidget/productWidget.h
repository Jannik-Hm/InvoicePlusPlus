#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "../inputWidget/textInputWidget.h"
#include "../inputWidget/spinBoxInputWidget.h"

/// @brief the respective widget for entering product data
class productWidget : public QWidget
{
    Q_OBJECT

public:
    explicit productWidget(QWidget *parent = nullptr);
    QWidget *centralWidgetwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    textInputWidget *name;
    textInputWidget *ppe;
    spinBoxInputWidget *count;
    QPushButton *deleteButton;

    signals:
        void requestDeletion(productWidget *widget);

    private slots:
        void handleDelete();

private:
};

#endif // PRODUCTWIDGET_H
