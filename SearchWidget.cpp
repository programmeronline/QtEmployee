#include "SearchWidget.h"
#include "ui_SearchWidget.h"
#include <QVector>

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);
}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::on_searchBut_clicked()
{
    if(!ui->searchLe->text().isEmpty())
    {
        //check for only alphabets
        emit searchClicked(ui->searchLe->text());
    }
    else
    {
        //display message empty
    }
}

void SearchWidget::on_cancelBut_clicked()
{
    emit cancelledSearch(this);
}

void SearchWidget::on_resetBut_clicked()
{
    ui->searchLe->clear();
}

