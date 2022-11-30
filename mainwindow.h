#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QFileDialog>
#include <QDebug>

#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sendData(QString, QString); //传递参数

private slots:
    void on_importButton_clicked();

    void on_startButton_clicked();

    void on_exportButton_clicked();

    void on_exitButton_clicked();



private:
    Ui::MainWindow *ui;
    QString inputDirPath; //OJ源程序文件夹
    int maxCount; //每个子文件夹中的cpp文件数的最大值
    QString oldEqualFilePath; //等价判断工具输出的等价程序对文件
    bool importFlag; //是否已导入文件的标志
    bool exportFlag; //是否已导出结果的标志
};
#endif // MAINWINDOW_H
