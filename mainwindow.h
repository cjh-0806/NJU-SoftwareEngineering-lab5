#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include <iostream>
#include <fstream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Pairs
{
    string file1;
    string file2;
    Pairs(string f1, string f2) : file1(f1), file2(f2) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_viewButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Pairs> equalPairsVec; //存放所有等价程序对
    QVector<Pairs> inequalPairsVec; //存放所有不等价程序对
    int index; //第几对等价程序对
};
#endif // MAINWINDOW_H
