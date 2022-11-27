#ifndef CONFIRMWIDGET_H
#define CONFIRMWIDGET_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <fstream>
using namespace std;

namespace Ui {
class ConfirmWidget;
}

class ConfirmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmWidget(QWidget *parent = nullptr);
    ~ConfirmWidget();

private slots:
    void on_equalButton_clicked();

    void on_inequalButton_clicked();

    void on_doubtButton_clicked();

private:
    Ui::ConfirmWidget *ui;
    QString file1name;
    QString file2name;
};

#endif // CONFIRMWIDGET_H
