#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //读取等价判断工具输出的等价程序对
    ifstream fin1("output/equal.csv");
    string line;
    while(getline(fin1, line))
    {
        int index = line.find(',');
        string file1 = line.substr(0, index);
        string file2 = line.substr(index+1);
        equalPairsVec.push_back(Pairs(file1, file2));
    }
    fin1.close();

    //读取等价判断工具输出的不等价程序对
    ifstream fin2("output/inequal.csv");
    while(getline(fin2, line))
    {
        int index = line.find(',');
        string file1 = line.substr(0, index);
        string file2 = line.substr(index+1);
        inequalPairsVec.push_back(Pairs(file1, file2));
    }
    fin2.close();
    index = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    index += 1;
    ConfirmWidget* cw = new ConfirmWidget;
    cw->show();
    //把第index对等价程序对的文件名称传给cw
}

void MainWindow::on_viewButton_clicked()
{

}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

//槽函数，接收等价转换为不等价
