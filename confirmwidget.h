#ifndef CONFIRMWIDGET_H
#define CONFIRMWIDGET_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QScrollBar>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include <iostream>
#include "dirinfo.h"
#include "unionfindset.h"
using namespace std;

namespace Ui {
class ConfirmWidget;
}

struct Pairs
{
    QString file1;
    QString file2;
    Pairs(QString f1, QString f2) : file1(f1), file2(f2) {}
};

class ConfirmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmWidget(QWidget *parent = nullptr);
    ~ConfirmWidget();
    void closeEvent(QCloseEvent *event);
    void showCode();

private slots:
    void on_verticalScrollBar_valueChanged(int value);

    void on_equalButton_clicked();

    void on_inequalButton_clicked();

    void on_doubtButton_clicked();

    void getData(QString, QString);

private:
    Ui::ConfirmWidget *ui;

    QString inputDirPath; //OJ源程序文件夹
    QVector<Pairs> inputVec; //等价判断工具给出的所有等价程序对（绝对路径）
    int index; //第几对等价程序对

    DirInfo sonDir; //每个子文件夹对象
    UnionFindSet uset; //每个子文件夹对应的并查集
};

#endif // CONFIRMWIDGET_H
