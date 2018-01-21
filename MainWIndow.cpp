#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <UserFormWidget.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QWidget>
#include <EditWidget.h>
#include <ChangePinWidget.h>
#include <mainwindow.h>
#include <QDebug>

QSqlDatabase MainWindow::db;
unsigned long long MainWindow::key;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    key = 0x1122334455667788;
    ui->setupUi(this);

    pin1 = new Pin(pin1Value,RETRY_COUNT);

    pin2 = new Pin(pin2Value,RETRY_COUNT);

    ui->mainStackWidget->insertWidget(1,&optWidget);

    //ui->mainStackWidget->insertWidget(5,&dispWidget);
    db = QSqlDatabase::addDatabase("QSQLITE");

    //db.setDatabaseName("C:/Users/takshila/Desktop/QtEshwar/UserManagement/myDatabase.db");
    db.setDatabaseName("/home/ish/DownloadsmyDatabase.db");
    if(db.open())
    {
//        QMessageBox::information(this,tr("Success"),"Database opened");
        QSqlQuery query;
        query.exec("create table user "
                   "(ID integer primary key,"
                   "FirstName varchar(25),"
                   "LastName varchar(25),"
                   "Age varchar(3),"
                   "Designation varchar(15))");
//        QMessageBox::information(this,tr("Error"),query.lastError().text());
    }
    else
    {
        QMessageBox::information(this,tr("Erro"),"Database failed to open");
    }
    db.close();
    connect(&optWidget,SIGNAL(sendOptionsToMainWindow(int)),this,SLOT(receiveFromOptionsWidget(int)));

    ui->mainStackWidget->setCurrentWidget(&optWidget);

}

void MainWindow::receiveFromOptionsWidget(int op)
{
    currentWorkingOption = op;
    loadPinVerificationWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPinVerificationWidget()
{
    PinVerificationWidget *pinVerWidget = new PinVerificationWidget();
    ui->mainStackWidget->insertWidget(2,pinVerWidget);
    ui->mainStackWidget->setCurrentWidget(pinVerWidget);
    connect(pinVerWidget,SIGNAL(verifyClicked(QString)),this,SLOT(verifyPin(QString)));
    connect(pinVerWidget,SIGNAL(pinVerifcationCancelled(QWidget *)),this,SLOT(processCancel(QWidget *)));
}

void MainWindow::processCancel(QWidget *widget)
{
    //load main window with options widget
    if(widget != NULL)
    {
        clearPreviousWidget(widget);
    }
    ui->mainStackWidget->setCurrentWidget(&optWidget);
    currentWorkingOption = MAIN_WINDOW;
}

void MainWindow::verifyPin(QString pinToVerify)
{
    if( (currentWorkingOption == EDIT_USER)?
        getPin(2)->verifyPin(pinToVerify):
        getPin(1)->verifyPin(pinToVerify))
    {
        switch(currentWorkingOption)
        {
        case ADD_USER:
            //view new entry form to get new user data
            loadUserFormWidget(NULL);
            break;
        case EDIT_USER:
            //view options to edit user/pin1/pin2
            loadEditWidget();
            break;
        case RET_USER:
            //view all the data fetched from server database
            loadDisplayWidget();
            break;
        case REM_USER:
            //veiw search widget to get the user to search
            loadSearchWidget();
            break;
        }
    }
}

void MainWindow::loadEditWidget()//contains
{
    EditWidget *editWidget = new EditWidget();
    connect(editWidget,SIGNAL(modUserClicked()),this,SLOT(processModifyUser()));
    connect(editWidget,SIGNAL(changePinClick(int)),this,SLOT(changePinOptionClicked(int)));
    connect(editWidget,SIGNAL(editWidgetCancelled(QWidget *)),this,SLOT(processCancel(QWidget*)));
    ui->mainStackWidget->insertWidget(7,editWidget);
    ui->mainStackWidget->setCurrentWidget(editWidget);
}

void MainWindow::loadUserFormWidget(User *userData)
{
    UserFormWidget *userFormWidget =new UserFormWidget(userData);
    ui->mainStackWidget->insertWidget(3,userFormWidget);
    ui->mainStackWidget->setCurrentWidget(userFormWidget);

    connect(userFormWidget,SIGNAL(saveUserClicked(User *)),this,SLOT(saveNewUser(User *)));
    connect(userFormWidget,SIGNAL(cancelUserFormClicked(QWidget *)),this,SLOT(processCancel(QWidget *)));
}

void MainWindow::loadSearchWidget()
{
    SearchWidget *searchWidget = new SearchWidget();

    ui->mainStackWidget->insertWidget(4,searchWidget);
    ui->mainStackWidget->setCurrentWidget(searchWidget);

    connect(searchWidget,SIGNAL(searchClicked(QString)),this,SLOT(searchUser(QString)));
    connect(searchWidget,SIGNAL(cancelledSearch(QWidget *)),this,SLOT(processCancel(QWidget *)));
}

//for retrieve user
void MainWindow::loadDisplayWidget()
{
    DisplayWidget *dispWidget = new DisplayWidget();
    ui->mainStackWidget->insertWidget(5,dispWidget);
    ui->mainStackWidget->setCurrentWidget(dispWidget);
    connect(dispWidget,SIGNAL(closeDisplayClicked(QWidget *)),this,SLOT(processCancel(QWidget *)));
}

void MainWindow::searchUser(QString searchText)
{
    int ret;
    int firstNameCol;
    int lastNameCol;
    int ageCol;
    int designationCol;

    userToDelOrEdit=0;
    SimpleCrypt crypto(key); //some random number
    QSqlQuery query;
    QSqlRecord rec;
    User *foundUser = new User();
    if(MainWindow::db.open())
    {
       // QMessageBox::information(this,tr("Hello window"),"Db is open");
        ret = query.exec(QString("select * from user"));
        if(ret)
        {
            //QMessageBox::information(this,tr("Hello window"),"Select success");

            //get total entries
            rec = query.record();
            firstNameCol = rec.indexOf("FirstName");
            lastNameCol = rec.indexOf("LastName");
            ageCol = rec.indexOf("Age");
            designationCol = rec.indexOf("Designation");

            while (query.next())
            {
                //get firstname and display
                if( crypto.decryptToString(query.value(firstNameCol).toString()) == searchText )
                {
                    foundUser->firstName    = crypto.decryptToString(query.value(firstNameCol).toString());
                    foundUser->lastName     = crypto.decryptToString(query.value(lastNameCol).toString());
                    foundUser->age          = crypto.decryptToString(query.value(ageCol).toString());
                    foundUser->designation  = crypto.decryptToString(query.value(designationCol).toString());

                    if(currentWorkingOption == EDIT_USER)
                        loadUserFormWidget(foundUser);
                    else if(currentWorkingOption == REM_USER)
                    {
                        ret = query.exec( QString("delete from user where ID =") + query.value(0).toString());
                        if(ret)
                        {
                            QMessageBox::information(this,tr("SQL Error"),"User deleted successfully!");
                             ui->mainStackWidget->setCurrentWidget(&optWidget);
                        }

                    }
                    return ;

                }userToDelOrEdit++;
                //get lastname and display
                //qDebug() << query.value(lastNameCol).toString();
            }
          }
        else
            QMessageBox::information(this,tr("SQL Error"),query.lastError().text());
    }
    else
        QMessageBox::information(this,tr("Error Window"),"Cannot connect to database!");
    userToDelOrEdit = 0xFF;
    //search in data base the enetered name
    //and display all matching results
}

void MainWindow::saveNewUser(User *userData)
{
    QSqlQuery query;
    int ret;
    SimpleCrypt crypto(key);
    QSqlRecord rec;
    QString previousRow;
    if(db.open())
    {
        if(currentWorkingOption == EDIT_USER)
        {
            ret = query.exec(QString("select * from user"));
            if(ret)
            {
                query.seek(userToDelOrEdit,false);
                previousRow = query.value(0).toString();
                ret = query.exec( QString("delete from user where ID =") + previousRow);
                if(!ret)
                {
                    QMessageBox::information(this,tr("Error"),"Some error occured");
                    db.close();
                    return;
                }
                else
                {
                    ret = query.exec(QString("insert into user values(NULL,'%1','%2', '%3', '%4')")
                           .arg(crypto.encryptToString(userData->firstName)).arg(crypto.encryptToString(userData->lastName))
                                     .arg(crypto.encryptToString(userData->age)).arg(crypto.encryptToString(userData->designation)));

                    if(ret)
                    QMessageBox::information(this,tr("Success"),"User data updated successfully");
                }
            }
        }
        else
        {
            ret = query.exec(QString("insert into user values(NULL,'%1','%2', '%3', '%4')")
                   .arg(crypto.encryptToString(userData->firstName)).arg(crypto.encryptToString(userData->lastName))
                             .arg(crypto.encryptToString(userData->age)).arg(crypto.encryptToString(userData->designation)));

            if(ret)
                QMessageBox::information(this,tr("Success"),"User data saved successfully");
            else
                QMessageBox::information(this,tr("Error Window"),"Somer error occured");
        }
            db.close();
    }
    ui->mainStackWidget->setCurrentWidget(&optWidget);
}

void MainWindow::changePinOptionClicked(int pinType)
{
    if(pinType == 1)
    {
        currentWorkingOption = CHANGE_PIN1;
    }
    else
    {
        currentWorkingOption = CHANGE_PIN2;
    }
    ChangePinWidget *chPinWidget = new ChangePinWidget();
    connect(chPinWidget,SIGNAL(saveNewPinClicked(QString,QString)),this,SLOT(processChangePin(QString,QString)));
    connect(chPinWidget,SIGNAL(pinChangeCancelled(QWidget*)),this,SLOT(processCancel(QWidget*)));

    ui->mainStackWidget->insertWidget(8,chPinWidget);
    ui->mainStackWidget->setCurrentWidget(chPinWidget);
}

void MainWindow::processChangePin(QString oldPin, QString newPin)
{
    if(currentWorkingOption == CHANGE_PIN1)
    {
        if(getPin(1)->changePin(oldPin,newPin))
        {
            QMessageBox::information(this,tr("Success"),"PIN 1 Updated successfully!");
            processCancel(NULL);
        }
    }
    else if(currentWorkingOption == CHANGE_PIN2)
    {
        if(getPin(2)->changePin(oldPin,newPin))
            QMessageBox::information(this,tr("Success"),"PIN 2 Updated successfully!");
            processCancel(NULL);
    }
}

Pin *MainWindow::getPin(int pinNumber)
{
    if(pinNumber == 1)
        return pin1;
    else
        return pin2;
}

void MainWindow::clearPreviousWidget(QWidget *preWidget)
{
    //clear whichever widget was cancelled
    ui->mainStackWidget->removeWidget(preWidget);
    delete preWidget;
}

void MainWindow::processModifyUser()
{
    loadSearchWidget();
}

void MainWindow::deleteUser(QString id)
{
    //delete from tab where ID =
}

/*
unsigned long long MainWindow::getEncKey()
{
    return key;
}

void MainWindow::setEncKey(unsigned long long value)
{
    key = value;
}
*/
