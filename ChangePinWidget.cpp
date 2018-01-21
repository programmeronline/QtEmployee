#include "ChangePinWidget.h"
#include "ui_ChangePinWidget.h"

ChangePinWidget::ChangePinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePinWidget)
{
    ui->setupUi(this);
}

ChangePinWidget::~ChangePinWidget()
{
    delete ui;
}

void ChangePinWidget::on_saveNewPinBut_clicked()
{
    if(!ui->oldPinLe->text().isEmpty() && !ui->newPinLe->text().isEmpty())
        emit saveNewPinClicked(ui->oldPinLe->text(), ui->newPinLe->text());
}

void ChangePinWidget::on_resetBut_clicked()
{
    ui->newPinLe->clear();
    ui->oldPinLe->clear();
}

void ChangePinWidget::on_cancelBut_clicked()
{
    emit pinChangeCancelled(this);
}
