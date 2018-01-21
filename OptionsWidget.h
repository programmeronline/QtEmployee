#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>

namespace Ui {
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();
signals:
    void sendOptionsToMainWindow(int op);
    void addUserFromOptWidget();
    void editUserFromOptWidget();
    void retUserFromOptWidget();
    void remUserFromOptWidget();

private slots:
    void on_addUserBut_clicked();
    void on_editUserBut_clicked();
    void on_retUserBut_clicked();
    void on_delUserBut_clicked();

private:
    Ui::OptionsWidget *ui;
};

#endif // OPTIONSWIDGET_H
