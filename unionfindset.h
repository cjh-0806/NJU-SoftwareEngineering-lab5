#ifndef UNIONFINDSET_H
#define UNIONFINDSET_H


class UnionFindSet
{
public:
    int* uset;
    int* rank;
    int size;
public:
    UnionFindSet();
    UnionFindSet(int size);
    int find(int x);
    bool unite(int x, int y);
    UnionFindSet &operator=(const UnionFindSet& u);
};

#endif // UNIONFINDSET_H
