#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <Pin.h>
#include <User.h>
#include <SearchWidget.h>
#include <UserFormWidget.h>
#include <DisplayWidget.h>
#include <PinVerificationWidget.h>
#include <OptionsWidget.h>
#include <QtSql/QSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QWidget>
#include <simplecrypt.h>
#include <qglobal.h>

#define MAIN_WINDOW 0
#define ADD_USER    1
#define EDIT_USER   2
#define RET_USER    3
#define REM_USER    4
#define CHANGE_PIN1 5
#define CHANGE_PIN2 6
#define RETRY_COUNT 3

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    Pin *pin1;
    Pin *pin2;

private:
    Ui::MainWindow *ui;
    OptionsWidget optWidget;
    UserFormWidget userFormWidget;
    int currentWorkingOption = MAIN_WINDOW;
    int userToDelOrEdit = 0xFF;
    QString pin1Value = "1234";
    QString pin2Value = "1111";
public:
    static unsigned long long key;
public:
    static QSqlDatabase db;

    static unsigned long long getKey();
    static void setKey(unsigned long long value);

private slots:
    void receiveFromOptionsWidget(int op);
    //common for all options
    void loadPinVerificationWidget();

    void processCancel(QWidget *widget);
    void verifyPin(QString pinToVerify);
    //for add user
    void loadUserFormWidget(User *user);
    void saveNewUser(User *userData);
    //for edit user and delete user
    void loadEditWidget();
    void loadSearchWidget();
    void processModifyUser();
    void searchUser(QString searchText);
    void changePinOptionClicked(int pinType);
    void processChangePin(QString , QString );
    void clearPreviousWidget(QWidget *preWidget);

    Pin *getPin(int pinNumber);

    //for retrieve user
    void loadDisplayWidget();
    void deleteUser(QString id);
    //for delete user

};

#endif // MAINWINDOW_H


