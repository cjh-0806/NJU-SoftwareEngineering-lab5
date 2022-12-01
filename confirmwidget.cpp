#include "confirmwidget.h"
#include "ui_confirmwidget.h"

//全局变量
QVector<Pairs> equalPairsVec; //存放最终的所有等价程序对
QVector<Pairs> inequalPairsVec; //存放最终的所有不等价程序对
QVector<Pairs> doubtPairsVec; //存放最终的存疑等价对

ConfirmWidget::ConfirmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmWidget),
    sonDir(), uset()
{
    ui->setupUi(this);
    connect(ui->textEdit1->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_verticalScrollBar_valueChanged(int)));
    connect(ui->textEdit2->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_verticalScrollBar_valueChanged(int)));
    index = 0;
}

ConfirmWidget::~ConfirmWidget()
{
    delete ui;
}

void ConfirmWidget::closeEvent(QCloseEvent *event)
{
    if(index >= inputVec.size())
    {
        QMessageBox::information(this, "提示", "您已完成所有程序对的确认！");
        event->accept();
        return;
    }
    QMessageBox::StandardButton button;
    button = QMessageBox::warning(this, "警告", "未确认完所有等价程序对，是否关闭窗口？", QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void ConfirmWidget::on_verticalScrollBar_valueChanged(int value) //两个textEdit实现滚轮同步
{
    QScrollBar *scrollbar1 = ui->textEdit1->verticalScrollBar();
    QScrollBar *scrollbar2 = ui->textEdit2->verticalScrollBar();

    scrollbar1->setValue(value);
    scrollbar2->setValue(value);
}

void ConfirmWidget::showCode()
{
    if(index >= inputVec.size())
    {
        this->close();
        return;
    }

    QString nowDir = inputVec[index].file1.left(inputVec[index].file1.lastIndexOf('/'));
    if(nowDir != sonDir.get_path()) //换到下个文件夹
    {
        sonDir.changeDir(nowDir);
        uset = UnionFindSet(sonDir.get_count());
    }

    int index1 = sonDir.fileIndex(inputVec[index].file1);
    int index2 = sonDir.fileIndex(inputVec[index].file2);
    //qDebug() << index1 << index2;
    while(uset.find(index1) == uset.find(index2)) //如果两个文件已经在并查集的等价类中
    {
        equalPairsVec.push_back(inputVec[index]); //直接添加到最终等价程序对数组中
        index++;
        if(index >= inputVec.size())
        {
            this->close();
            return;
        }
        qDebug() << "已在并查集" ;
        nowDir = inputVec[index].file1.left(inputVec[index].file1.lastIndexOf('/'));
        if(nowDir != sonDir.get_path()) //到下一个文件夹了
        {
            sonDir.changeDir(nowDir);
            uset = UnionFindSet(sonDir.get_count());
        }
        index1 = sonDir.fileIndex(inputVec[index].file1);
        index2 = sonDir.fileIndex(inputVec[index].file2);
    }

    ui->label1->setText(inputVec[index].file1.mid(inputDirPath.length()+1));
    ui->label2->setText(inputVec[index].file2.mid(inputDirPath.length()+1));
    ui->textEdit1->clear(); //清空
    ui->textEdit2->clear();

    QFile file1(inputVec[index].file1);
    QFile file2(inputVec[index].file2);
    if(file1.open(QIODevice::ReadOnly) && file2.open(QIODevice::ReadOnly))
    {
        QTextStream ts1(&file1);
        QTextStream ts2(&file2);
        while(!ts1.atEnd() && !ts2.atEnd()) //按行显示文件内容
        {
            QString line1 = ts1.readLine();
            QString line2 = ts2.readLine();
            if(line1.simplified() != line2.simplified())
            {
                ui->textEdit1->setTextColor(Qt::red);
                ui->textEdit2->setTextColor(Qt::red);
            }
            ui->textEdit1->append(line1);
            ui->textEdit2->append(line2);
            ui->textEdit1->setTextColor(Qt::black);
            ui->textEdit2->setTextColor(Qt::black);
        }
        while(!ts1.atEnd())
        {
            ui->textEdit1->setTextColor(Qt::red);
            ui->textEdit1->append(ts1.readLine());
        }
        while(!ts2.atEnd())
        {
            ui->textEdit2->setTextColor(Qt::red);
            ui->textEdit2->append(ts2.readLine());
        }
    }
}

void ConfirmWidget::on_equalButton_clicked()
{
    equalPairsVec.push_back(inputVec[index]); //添加到最终等价程序对数组中
    int index1 = sonDir.fileIndex(inputVec[index].file1);
    int index2 = sonDir.fileIndex(inputVec[index].file2);
    //qDebug() << index1 << index2;
    uset.unite(index1, index2);
    index++;
    //for(int i=0;i<sonDir.get_count();++i)
        //qDebug() << sonDir.fileVec[i] << uset.uset[i];
    showCode(); //确认了结果之后自动推荐下一个程序对
}

void ConfirmWidget::on_inequalButton_clicked()
{
    inequalPairsVec.push_back(inputVec[index]); //添加到最终不等价程序对数组中
    qDebug() << index;
    inputVec.erase(inputVec.begin() + index); //从原等价程序对数组删除
    showCode();
}

void ConfirmWidget::on_doubtButton_clicked()
{
    doubtPairsVec.push_back(inputVec[index]); //添加到最终存疑程序对数组中
    inputVec.erase(inputVec.begin() + index); //从原等价程序对数组删除
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
    sonDir.changeDir(inputVec[index].file1.left(inputVec[index].file1.lastIndexOf('/')));
    uset = UnionFindSet(sonDir.get_count());
    showCode();
}
