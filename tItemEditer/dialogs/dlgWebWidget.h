#ifndef DLGWEBWIDGET_H
#define DLGWEBWIDGET_H

#include <QDialog>

namespace Ui {
class dlgWebWidget;
}

class dlgWebWidget : public QDialog
{
    Q_OBJECT

public:
    explicit dlgWebWidget(QString url,QWidget *parent = nullptr);
    ~dlgWebWidget();

private:
    Ui::dlgWebWidget *ui;
};

#endif // DLGWEBWIDGET_H
