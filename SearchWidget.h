#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QString>
namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = 0);
    ~SearchWidget();
signals:
    void searchClicked(QString searchText);
    void cancelledSearch(QWidget *th);

private slots:
    void on_searchBut_clicked();

    void on_cancelBut_clicked();

    void on_resetBut_clicked();

private:
    Ui::SearchWidget *ui;
};

#endif // SEARCHWIDGET_H
