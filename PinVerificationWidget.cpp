#include "PinVerificationWidget.h"
#include "ui_PinVerificationWidget.h"

PinVerificationWidget::PinVerificationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinVerificationWidget)
{
    ui->setupUi(this);
}

PinVerificationWidget::~PinVerificationWidget()
{
    delete ui;
}

void PinVerificationWidget::on_cancelBut_clicked()
{
    emit pinVerifcationCancelled(this);
}

void PinVerificationWidget::on_verifyBut_clicked()
{
    //get text and emit
    if(!ui->pinLe->text().isEmpty())
        emit verifyClicked(ui->pinLe->text());
}
