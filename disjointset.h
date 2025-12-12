#ifndef DISJOINTSETHEADER
#define DISJOINTSETHEADER
#include <vector>


class Set
{
private:
    std::vector<size_t> parent;
    size_t size, count;

public:
    Set(size_t num = 0) : size(num), count(num) {parent.resize(num); for(int i = 0; i < num; i++) parent[i] = i;} 
    int find(size_t i);
    void unite(size_t x, size_t y);
    bool same(size_t x, size_t y);
    int getCount() const {return count;}
    int getSize(int x) const {return size;}
};

int Set::find(size_t i) 
{
    if(parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

void Set::unite(size_t x, size_t y)
{
    size_t rootx = find(x), rooty = find(y);
    if(rootx == rooty)
        return;
    count--;
    parent[rootx] = rooty;
}

bool Set::same(size_t x, size_t y)
{
    return find(x) == find(y);
}



#endif