#include "confirmwidget.h"
#include "ui_confirmwidget.h"

//全局变量
QVector<Pairs> equalPairsVec; //存放最终的所有等价程序对
QVector<Pairs> inequalPairsVec; //存放最终的所有不等价程序对

ConfirmWidget::ConfirmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmWidget)
{
    ui->setupUi(this);
}

ConfirmWidget::~ConfirmWidget()
{
    delete ui;
}

void ConfirmWidget::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::warning(this, "警告", "未确认完所有等价程序对，是否关闭窗口？", QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void ConfirmWidget::showCode()
{
    if(index > inputVec.size())
    {
        this->close();
        return;
    }
    ui->textEdit1->clear(); //清空
    ui->textEdit2->clear();
    QFile file1(inputVec[index].file1);
    if(file1.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file1);
        while(!textStream.atEnd()) //按行显示文件内容
            ui->textEdit1->append(textStream.readLine());
    }
    QFile file2(inputVec[index].file2);
    if(file2.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file2);
        while(!textStream.atEnd())
            ui->textEdit2->append(textStream.readLine());
    }
}

void ConfirmWidget::on_equalButton_clicked()
{
    equalPairsVec.push_back(inputVec[index]); //添加到最终等价程序对数组中
    index++;
    showCode(); //确认了结果之后自动推荐下一个程序对
}

void ConfirmWidget::on_inequalButton_clicked()
{
    inequalPairsVec.push_back(inputVec[index]); //添加到最终不等价程序对数组中
    inputVec.erase(inputVec.begin() + index); //从原等价程序对数组删除
    showCode();
}

void ConfirmWidget::on_doubtButton_clicked()
{
    index++;
    showCode();
}

void ConfirmWidget::getData(QString dirpath, QString filepath)
{
    inputDirPath = dirpath;
    //存放等价程序对文件路径
    QFile file(filepath);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file);
        QString line;
        while(!textStream.atEnd())
        {
            line = textStream.readLine();
            int pos = line.indexOf(',');
            QString file1name = dirpath + '/' + line.left(pos);
            QString file2name = dirpath + '/' + line.mid(pos+1);
            inputVec.push_back(Pairs(file1name, file2name));
        }
        file.close();
    }
    else
        return;
    index = 0;
    showCode();
}
