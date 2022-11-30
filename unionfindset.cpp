#include "unionfindset.h"

UnionFindSet::UnionFindSet()
{
    uset = nullptr;
    rank = nullptr;
    size = 0;
}

UnionFindSet::UnionFindSet(int size)
{
    uset = new int[size];
    rank = new int[size];
    this->size = size;
    for(int i = 0; i < size; ++i)
    {
        uset[i] = i;
        rank[i] = 1;
    }
}

int UnionFindSet::find(int x) //找到x的根节点
{
    if(x == uset[x])
        return x;
    else
    {
        uset[x] = find(uset[x]);
        return uset[x];
    }
}

bool UnionFindSet::unite(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)
        return false;
    //判断两棵树的高度，将新的根节点选为节点数较多的那一个
    if (rank[fx] < rank[fy])
    {
        uset[fx] = fy;
        rank[fy] += rank[fx];
    }
    else
    {
        uset[fy] = fx;
        rank[fx] += rank[fy];
    }
    return true;
}

UnionFindSet& UnionFindSet::operator=(const UnionFindSet& u)
{
    if (this == &u)
        return *this;
    delete[] uset;
    delete[] rank;
    uset = new int[u.size];
    rank = new int[u.size];
    size = u.size;
    for(int i = 0; i < size; ++i)
    {
        uset[i] = i;
        rank[i] = 1;
    }
    return *this;
}
