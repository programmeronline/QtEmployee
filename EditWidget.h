#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>

namespace Ui {
class EditWidget;
}

class EditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditWidget(QWidget *parent = 0);
    ~EditWidget();

signals:
    void modUserClicked();
    void changePinClick(int pinType);
    void editWidgetCancelled(QWidget *);

private slots:
    void on_modUserBut_clicked();

    void on_changePin1But_clicked();

    void on_cancelBut_clicked();

    void on_changePin2_clicked();

private:
    Ui::EditWidget *ui;
};

#endif // EDITWIDGET_H
