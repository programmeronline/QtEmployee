#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QString>
namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

private slots:
    void on_closeDisplay_clicked();
    void displayUserData();
signals:
    void closeDisplayClicked(QWidget *);
private:
    Ui::DisplayWidget *ui;
};

#endif // DISPLAYWIDGET_H
