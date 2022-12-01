#ifndef UNIONFINDSET_H
#define UNIONFINDSET_H

class UnionFindSet
{
public:
    int* uset; //并查集
    int* rank; //用于记录每个元素的子节点数
    int size; //元素个数
public:
    UnionFindSet();
    UnionFindSet(int size);
    int find(int x); //查
    void unite(int x, int y); //并
    UnionFindSet &operator=(const UnionFindSet& u); //重载=号
};

#endif // UNIONFINDSET_H
