#include "dlgWebWidget.h"
#include "ui_dlgWebWidget.h"
#include <QWebEngineView>

dlgWebWidget::dlgWebWidget(QString url,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dlgWebWidget)
{
    // setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    QWebEngineView *view = new QWebEngineView(this);
    view->load(QUrl(url));

    ui->verticalLayout->addWidget(view);
}

dlgWebWidget::~dlgWebWidget()
{
    delete ui;
}
