#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if defined(QT_ARCH_X86_64) || defined(Q_OS_WIN64)
    QMessageBox::information(nullptr, "信息", "当前是64位程序");
#else
    QMessageBox::information(nullptr, "信息", "当前是32位程序");
#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}
