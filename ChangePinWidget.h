#ifndef CHANGEPINWIDGET_H
#define CHANGEPINWIDGET_H

#include <QWidget>

namespace Ui {
class ChangePinWidget;
}

class ChangePinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePinWidget(QWidget *parent = 0);
    ~ChangePinWidget();
signals:
    void saveNewPinClicked(QString oldPin,QString newPin);
    void pinChangeCancelled(QWidget *);

private slots:
    void on_saveNewPinBut_clicked();

    void on_resetBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::ChangePinWidget *ui;
};

#endif // CHANGEPINWIDGET_H
