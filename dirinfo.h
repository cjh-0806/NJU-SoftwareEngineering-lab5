#ifndef DIRINFO_H
#define DIRINFO_H

#include <QVector>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include <iostream>
using namespace std;

class DirInfo
{
public:
    QString path; //路径
    int count; //c或cpp文件数
    QVector<QString> fileVec; //c或cpp文件数组
public:
    DirInfo();
    void changeDir(QString src); //更新对象内容
    QString get_path() const { return path; }
    int get_count() const { return count; }
    int fileIndex(QString filename); //查找文件在数组中的下标
};

#endif // DIRINFO_H
