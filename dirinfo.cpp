#include "dirinfo.h"

DirInfo::DirInfo()
{
    path = "";
    count = 0;
}

void DirInfo::changeDir(QString src)
{
    path = src;

    QDir dir(path);
    QStringList filter;
    filter << "*.cpp" << "*.c"; //过滤文件类型
    dir.setNameFilters(filter);
    QFileInfoList fileList = dir.entryInfoList(filter);
    count = fileList.count();  //得到文件个数
    //qDebug() << count;

    fileVec.clear(); //更新文件数组
    for(auto file : fileList)
        fileVec.push_back(file.absoluteFilePath());
}

int DirInfo::fileIndex(QString filename)
{
    for(int i = 0; i < fileVec.size(); ++i)
        if(fileVec[i] == filename)
            return i;
    return -1;
}
