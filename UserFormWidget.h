#ifndef USERFORMWIDGET_H
#define USERFORMWIDGET_H
#include <User.h>
#include <QWidget>
#include <QString>
#include <User.h>
namespace Ui {
class UserFormWidget;
}

class UserFormWidget : public QWidget
{
    Q_OBJECT
public:
    UserFormWidget(User *user);
public:
    explicit UserFormWidget(QWidget *parent = 0);
    ~UserFormWidget();

private slots:
    void on_saveBut_clicked();

    void on_cancelBut_clicked();
signals:
    void saveUserClicked(User *user);
    void cancelUserFormClicked(QWidget *);

private:
    Ui::UserFormWidget *ui;
};

#endif // USERFORMWIDGET_H
