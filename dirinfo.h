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
    QString path;
    int count;
    QVector<QString> fileVec;
public:
    DirInfo();
    void changeDir(QString src);
    QString get_path() const { return path; }
    int get_count() const { return count; }
    int fileIndex(QString filename);
};

#endif // DIRINFO_H
