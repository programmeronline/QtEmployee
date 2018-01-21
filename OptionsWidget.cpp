#include "OptionsWidget.h"
#include "ui_OptionsWidget.h"
#include <mainwindow.h>
OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWidget)
{
    ui->setupUi(this);
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::on_addUserBut_clicked()
{
    emit sendOptionsToMainWindow(ADD_USER);
}

void OptionsWidget::on_editUserBut_clicked()
{
    emit sendOptionsToMainWindow(EDIT_USER);
}

void OptionsWidget::on_retUserBut_clicked()
{
    emit sendOptionsToMainWindow(RET_USER);
}

void OptionsWidget::on_delUserBut_clicked()
{
    emit sendOptionsToMainWindow(REM_USER);
}
