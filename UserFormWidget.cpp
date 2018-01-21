#include "UserFormWidget.h"
#include "ui_UserFormWidget.h"

UserFormWidget::UserFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserFormWidget)
{
    ui->setupUi(this);
}

UserFormWidget::UserFormWidget(User *user)
{
    ui = new Ui::UserFormWidget;
    ui->setupUi(this);
    if(user == NULL)
    {
        ui->firstNameLe->setText(QString("Only Characters"));
        ui->lastNameLe->setText(QString("Only Characters"));
        ui->ageLe->setText(QString("Only Numbers"));
    }
    else
    {
        ui->firstNameLe->setText(user->firstName);
        ui->lastNameLe->setText(user->lastName);
        ui->ageLe->setText(user->age);
        ui->designationCb->setCurrentText(user->designation);
    }
}

UserFormWidget::~UserFormWidget()
{
    delete ui;
}

void UserFormWidget::on_saveBut_clicked()
{
    //ui->firstNameLe->text()
    User *newUser = new User();

    newUser->firstName = ui->firstNameLe->text();
    newUser->lastName = ui->lastNameLe->text();
    newUser->age = ui->ageLe->text();
    newUser->designation = ui->designationCb->currentText();

    emit saveUserClicked(newUser);
}

void UserFormWidget::on_cancelBut_clicked()
{
    emit cancelUserFormClicked(this);
}
