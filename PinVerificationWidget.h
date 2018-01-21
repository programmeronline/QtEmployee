#ifndef PINVERIFICATIONWIDGET_H
#define PINVERIFICATIONWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class PinVerificationWidget;
}

class PinVerificationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PinVerificationWidget(QWidget *parent = 0);
    ~PinVerificationWidget();
signals:
    void pinVerifcationCancelled(QWidget *);
    void verifyClicked(QString);

private slots:
    void on_cancelBut_clicked();

    void on_verifyBut_clicked();

private:
    Ui::PinVerificationWidget *ui;
};

#endif // PINVERIFICATIONWIDGET_H
