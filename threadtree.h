#ifndef THREADTREEHEADER
#define THREADTREEHEADER

#include <string>
#include <iostream>

//thread is in-ordered
template <typename T>
class ThreadTree
{
    private:
        struct node
        {
            T data;
            bool ltag, rtag;   //0 for childptr, 1 for pred(in lchild) / succ(in rchild)
            node* lchild, *rchild;
            node(T val, bool l = 0, bool r = 0, node* l1 = nullptr, node* r1 = nullptr) : 
            data(val), ltag(l), rtag(r), lchild(l1), rchild(r1) {}
        };
        node* root;
        void convert2tree(node*& p,const std::string&, size_t& index);
        void threaded(node* p, node*& pre);
        static void printnode(node* p) {std::cout << p -> data << " ";}
    public:
        ThreadTree() : root(nullptr) {}
        node* InOrderFirst(node* r);
        node* InOrderSucc(node* r);
        node* InOrderLast(node* r);
        node* InOrderPred(node* r);   
        void InOrderVisit(void(*visit)(node *p));
        void convert(const std::string& s); //string -> BinTree<char>
        void print() {InOrderVisit(printnode);}
};

template <typename T>
typename ThreadTree<T>::node* ThreadTree<T>::InOrderFirst(node* r)
{
    if(r == nullptr)
        return nullptr;
    while(r -> ltag == 0)
        r = r -> lchild;
    return r;
}

template <typename T>
typename ThreadTree<T>::node* ThreadTree<T>::InOrderSucc(node* r)
{
    if(r == nullptr)
        return nullptr;
    if(r -> rtag == 1)
        return r -> rchild;
    return InOrderFirst(r -> rchild);
}

template <typename T>
typename ThreadTree<T>::node* ThreadTree<T>::InOrderLast(node* r)
{
    if(r == nullptr)
        return nullptr;
    while(r -> rtag == 0)
        r = r -> rchild;
    return r;
}

template <typename T>
typename ThreadTree<T>::node* ThreadTree<T>::InOrderPred(node* r)
{
    if(r == nullptr)
        return nullptr;
    if(r -> ltag == 1)
        return r -> lchild;
    return InOrderLast(r -> lchild);
}

template <class T> 
void ThreadTree<T>::InOrderVisit(void(*visit)(node *p)) 
{
    node* p;  
    for (p = InOrderFirst (root); p != NULL; p = InOrderSucc(p) ) 
        visit(p);
}

template <>
void ThreadTree<char>::convert2tree(node*& p, const std::string& s, size_t& index)
{
    if(index >= s.size())
        return;

    char c = s[index++];
    if(c != '#')
    {
        p = new node(c);
        convert2tree(p -> lchild, s, index);
        convert2tree(p -> rchild, s, index);
    }
    else
        p = nullptr;
}

template <typename T>
void ThreadTree<T>::threaded(node* p, node*& pre)
{
    if(p == nullptr) return;

    threaded(p -> lchild, pre);
    if(pre != nullptr && pre -> rchild == nullptr)
    {
        pre -> rtag = 1; pre -> rchild = p; 
    }
    if(p -> lchild == nullptr)
    {
        p -> ltag = 1; p -> lchild = pre;
    }
    pre = p;
    threaded(p -> rchild, pre);
}

template <typename T>
void ThreadTree<T>::convert(const std::string& s)
{
    size_t count = 0; node* p = nullptr; 
    convert2tree(root, s, count); threaded(root, p);
    if(p != nullptr) 
        p -> rtag = 1;   //rchild is already nullptr
}   

#endif