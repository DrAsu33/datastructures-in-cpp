#ifndef HEAPHEADER
#define HEAPHEADER
#include <vector>
#include <algorithm>
#include <iostream>
using std::vector, std::swap;

template <typename T>
class Heap
{
    private:
        vector<T> data;
        int size;
        void siftup(int index);
        void siftdown(int index);

    public:
        Heap() : size(0) {}
        Heap(const vector<T>& v);
        ~Heap() {}
        void print() {for(auto i : data) std::cout << i << " "; std::cout << std::endl;}
};

template <typename T>
Heap<T>::Heap(const vector<T>& v)
{
    size = (int)v.size();
    data = v;
    for(int i = (size - 2) / 2; i >= 0; i--)
        siftdown(i);
}

template <typename T>
void Heap<T>::siftup(int index)
{
    int parent = (index - 1) / 2;
    while(index > 0 && data[index] < data[parent])
    {
        swap(data[index], data[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template <typename T>
void Heap<T>::siftdown(int index)
{
    int lchild, rchild, min = index;
    while(1)
    {    
        lchild = index * 2 + 1;
        rchild = index * 2 + 2;
        if(lchild < size && data[lchild] < data[min])
            min = lchild;
        if(rchild < size && data[rchild] < data[min])
            min = rchild;
        if(min != index)
        {            
            swap(data[index], data[min]);
            index = min;
        }
        else    
            break;
    }
}





#endif