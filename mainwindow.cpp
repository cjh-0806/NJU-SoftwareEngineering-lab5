#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmwidget.h"

//声明外部变量
extern QVector<Pairs> equalPairsVec; //存放最终的所有等价程序对
extern QVector<Pairs> inequalPairsVec; //存放最终的所有不等价程序对

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_importButton_clicked()
{
    //读取OJ源程序文件夹路径
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择OJ源程序文件夹");
    if(dirpath.isEmpty())
        return;
    inputDirPath = dirpath.left(dirpath.lastIndexOf('/')); //去掉"/input"
    qDebug() << inputDirPath;
    //读取等价判断工具输出的等价程序对文件路径
    QString filepath = QFileDialog::getOpenFileName(this, "选择等价程序对文件", "", "CSV files(*.csv)");
    if(filepath.isEmpty())
        return;
    oldEqualFilePath = filepath;
    qDebug() << filepath;
    flag = true;
}

void MainWindow::on_startButton_clicked() //开始进行人工确认
{
    if(flag == false)
    {
        QMessageBox::warning(this, "警告", "文件未导入！");
        return;
    }
    ConfirmWidget* cw = new ConfirmWidget;
    connect(this, SIGNAL(sendData(QString, QString)), cw, SLOT(getData(QString, QString)));
    emit sendData(inputDirPath, oldEqualFilePath);//把OJ源程序文件夹和等价程序对文件的路径传给cw
    cw->show();
}

void MainWindow::on_exportButton_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择结果输出文件夹");
    if(dirpath.isEmpty())
        return;
    qDebug() << dirpath;
    //存储等价程序对
    QFile equalfile(dirpath + "/equal.csv");
    if(equalfile.open(QIODevice::WriteOnly))
    {
        QTextStream fout(&equalfile);
        for(auto pair : equalPairsVec)
        {
            QString file1name = pair.file1.mid(inputDirPath.length()+1); //文件路径从"/input"开始
            QString file2name = pair.file2.mid(inputDirPath.length()+1);
            fout << file1name << ',' << file2name << endl;
        }
        equalfile.close();
    }
    //存储不等价程序对
    QFile inequalFile(dirpath + "/inequal.csv");
    QString oldInequalFilePath = oldEqualFilePath.mid(0, oldEqualFilePath.length()-9) + "inequal.csv";
    qDebug() << oldInequalFilePath;
    QFile oldInequalFile(oldInequalFilePath);
    if(inequalFile.open(QIODevice::WriteOnly) && oldInequalFile.open(QIODevice::ReadOnly))
    {
        QTextStream fout(&inequalFile);
        QTextStream fin(&oldInequalFile);
        while(!fin.atEnd()) //把原不等价程序对文件照搬
            fout << fin.readLine() << endl;
        oldInequalFile.close();
        for(auto pair : inequalPairsVec) //加上用户确认的不等价程序对
        {
            QString file1name = pair.file1.mid(inputDirPath.length()+1);
            QString file2name = pair.file2.mid(inputDirPath.length()+1);
            fout << file1name << ',' << file2name << endl;
        }
        inequalFile.close();
    }
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}
