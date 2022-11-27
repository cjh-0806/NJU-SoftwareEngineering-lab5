#include "confirmwidget.h"
#include "ui_confirmwidget.h"

ConfirmWidget::ConfirmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmWidget)
{
    ui->setupUi(this);

    QFile file1(file1name);
    if(file1.open(QIODevice::ReadOnly | QIODevice::Text)) //打开文件
    {
        QTextStream textStream(&file1);
        while(!textStream.atEnd())
        {
            //按行显示文件内容
            ui->textEdit1->append(textStream.readLine());
        }
    }
    QFile file2(file2name);
    if(file2.open(QIODevice::ReadOnly | QIODevice::Text)) //打开文件
    {
        QTextStream textStream(&file2);
        while(!textStream.atEnd())
        {
            //按行显示文件内容
            ui->textEdit2->append(textStream.readLine());
        }
    }
}

ConfirmWidget::~ConfirmWidget()
{
    delete ui;
}

void ConfirmWidget::on_equalButton_clicked()
{
    this->close(); //结果不变
}

void ConfirmWidget::on_inequalButton_clicked()
{
    //发出信号：两个文件不等价

    /*QString filename = "output/equal.csv";
    QFile file(filename);
    if(file.open())
    {
        //找到equal.csv中的“等价程序对”并删除，加到inequal.csv最后

    }*/
    this->close();
}

void ConfirmWidget::on_doubtButton_clicked()
{
    this->close(); //结果不变
}
