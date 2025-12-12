#ifndef BINSEARCHTREE
#define BINSEARCHTREE
#include <iostream>

template <typename T>
class BinSearchTree
{
    private:
        struct node
        {
            T data;
            node* lchild, *rchild;
            node(T d, node* l = nullptr, node* r = nullptr) : data(d), lchild(l), rchild(r) {}
        };
        node* root;
        void print(node* r);
        void insert(T val, node*& p);
        node* search(T val, node* p);
        void del(T val, node*& p);
        void destroy(node* p);

    public:
        BinSearchTree() : root(nullptr) {}
        ~BinSearchTree() {destroy(root);}
        void print() {print(root);}
        void insert(T val) {insert(val, root);}
        bool search(T val) {if(search(val, root)) return 1; return 0;}
        void del(T val) {del(val, root);}
};

template <typename T>
void BinSearchTree<T>::destroy(node* p)
{
    if(p == nullptr)
        return;
    destroy(p -> lchild);
    destroy(p -> rchild);
    delete p;
}

template <typename T>
void BinSearchTree<T>::print(typename BinSearchTree<T>::node* r)
{
    if(r == nullptr)
        return;
    std::cout << r -> data << " ";
    print(r -> lchild);
    print(r -> rchild);
    
}

template <typename T>
void BinSearchTree<T>::insert(T val, typename BinSearchTree<T>::node*& p)
{
    if(p == nullptr)
        p = new typename BinSearchTree<T>::node(val);
    else
    {
        if(val < p -> data)
            insert(val, p -> lchild);
        else
            insert(val, p -> rchild);
    }
}

template <typename T>
typename BinSearchTree<T>::node* BinSearchTree<T>::search(T val, typename BinSearchTree<T>::node* p)
{
    if(p == nullptr)
        return nullptr;

    if(val == p -> data)
        return p;
    else if(val > p -> data)
        return search(val, p -> rchild);
    return search(val, p -> lchild);
}

template <typename T>
void BinSearchTree<T>::del(T val, typename BinSearchTree<T>::node*& p)
{
    if(p == nullptr)
        return ;
    if(val < p -> data)
        del(val, p -> lchild);
    else if(val > p -> data)
        del(val, p -> rchild);
    else
    {
        typename BinSearchTree<T>::node* temp = p;
        if(p -> lchild == nullptr)
        {
            p = p -> rchild;
            delete temp;
        }
        else if(p -> rchild == nullptr)
        {
            p = p -> lchild;
            delete temp;
        }
        else
        {
            temp = p -> rchild;
            while(temp -> lchild != nullptr)
                temp = temp -> lchild;
            p -> data = temp -> data;
            del(temp -> data, p -> rchild);
        }
    }
}
#endif
