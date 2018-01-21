#include "DisplayWidget.h"
#include "ui_DisplayWidget.h"
#include <QMessageBox>
#include <mainwindow.h>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <simplecrypt.h>
DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
    //ui->tableWidget->setHidden(true);
    displayUserData();
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

void DisplayWidget::on_closeDisplay_clicked()
{
    //ui->tableWidget->setItem();
    emit closeDisplayClicked(this);
}

void DisplayWidget::displayUserData()
{
    int ret;
    int firstNameCol;
    int lastNameCol;
    int ageCol;
    int designationCol;
    int tableRow=0;
    int tableColumn=0;
    int totalUserCount;
    SimpleCrypt crypto(MainWindow::key); //some random number
    QSqlQuery query;
    QSqlRecord rec;
    if(MainWindow::db.open())
    {
       // QMessageBox::information(this,tr("Hello window"),"Db is open");
        ret = query.exec(QString("select * from user"));
        if(ret)
        {
            //QMessageBox::information(this,tr("Hello window"),"Select success");

            //get total entries
            rec = query.record();
            totalUserCount = rec.count();
            firstNameCol = rec.indexOf("FirstName");
            lastNameCol = rec.indexOf("LastName");ss
            ageCol = rec.indexOf("Age");
            designationCol = rec.indexOf("Designation");
            ui->tableWidget->setRowCount(totalUserCount);
            ui->tableWidget->setColumnCount(4);
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            while (query.next())
            {

                //get firstname and display
                qDebug() << query.value(firstNameCol).toString();
                ui->tableWidget->setItem(tableRow,tableColumn,
                                         new QTableWidgetItem(crypto.decryptToString(query.value(firstNameCol).toString())));
                tableColumn++;
                //get lastname and display
                qDebug() << query.value(lastNameCol).toString();
                ui->tableWidget->setItem(tableRow,tableColumn,
                                         new QTableWidgetItem(crypto.decryptToString(query.value(lastNameCol).toString())));
                tableColumn++;
                //get age and display
                qDebug() << query.value(ageCol).toString();
                ui->tableWidget->setItem(tableRow,tableColumn,
                                         new QTableWidgetItem(crypto.decryptToString(query.value(ageCol).toString())));
                tableColumn++;
                //get designation and display
                qDebug() << query.value(designationCol).toString();
                ui->tableWidget->setItem(tableRow,tableColumn,
                                         new QTableWidgetItem(crypto.decryptToString(query.value(designationCol).toString())));

                tableRow++;
                tableColumn = 0;
            }
        }
        else
            QMessageBox::information(this,tr("SQL Error"),query.lastError().text());

        //QMessageBox::information(this,tr("Hello Window"), rec.value(2).toString() );*/
    }
    else
        QMessageBox::information(this,tr("Error Window"),"Cannot connect to database!");
    MainWindow::db.close();
}
