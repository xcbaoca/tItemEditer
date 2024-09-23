#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if defined(QT_ARCH_X86_64) || defined(Q_OS_WIN64)
    QMessageBox::information(nullptr, tr("message"), tr("It is currently a 64-bit program"));
#else
    QMessageBox::information(nullptr, tr("message"), tr("It is currently a 32-bit program"));
#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}
