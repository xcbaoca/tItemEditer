#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include "BaseClass/CProcess.h"
#include "BaseClass/CItem.h"
#include <QDebug>
#include "dialogs/dlgWebWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// #if defined(QT_ARCH_X86_64) || defined(Q_OS_WIN64)
//     QMessageBox::information(nullptr, tr("message"), tr("It is currently a 64-bit program"));
// #else
//     QMessageBox::information(nullptr, tr("message"), tr("It is currently a 32-bit program"));
// #endif

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pbtnConfirm_clicked()
{
    // uint pid = ui->ledPid->text().toUInt();
    // CProcess process(pid);
    // if(process.isInited())
    //     qDebug() << process.getProcessName();
    ui->tableWidget->clear();
    uint id = ui->ledPid->text().toUInt();
    CItem item = CItem::fromTable(id);
    QSqlRecord record = item.toSqlRecord();
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(record.count());

    for(int i=0;i<record.count();++i){
        QTableWidgetItem*item = new QTableWidgetItem(record.value(i).toString());
        ui->tableWidget->setItem(0,i,item);
    }
}


void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    if(item->column() ==  3){
        dlgWebWidget dlg(item->text(),this);
        dlg.exec();
    }
}

