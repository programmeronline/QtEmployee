#include "EditWidget.h"
#include "ui_EditWidget.h"

EditWidget::EditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWidget)
{
    ui->setupUi(this);
}

EditWidget::~EditWidget()
{
    delete ui;
}

void EditWidget::on_modUserBut_clicked()
{
    emit modUserClicked();
}

void EditWidget::on_changePin1But_clicked()
{
    emit changePinClick(1);
}


void EditWidget::on_cancelBut_clicked()
{
    emit editWidgetCancelled(this);
}


void EditWidget::on_changePin2_clicked()
{
    emit changePinClick(2);
}
