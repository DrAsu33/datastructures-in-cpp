#ifndef AVLTREEHEADER
#define AVLTREEHEADER

#include <iostream>
#include <string> 

template <typename T>
class AVLTree
{
    private:
        struct Node
        {
            T data;
            Node* lchild, *rchild;
            int bf;
            Node(T d = T(), Node* l = nullptr, Node* r = nullptr, int b = 0) 
            : data(d), lchild(l), rchild(r), bf(b) {}
        };
        Node* root;
        void rotate_L(Node*& p);
        void rotate_R(Node*& p);
        void rotate_LR(Node*& p);
        void rotate_RL(Node*& p);

        void insert(const T& val, Node*& p, bool& taller);
        void balance_l_insert(Node*& p, bool& taller);
        void balance_r_insert(Node*& p, bool& taller);
    
        void remove(const T& val, Node*& p, bool& shorter);
        void balance_l_remove(Node*& p, bool& taller);
        void balance_r_remove(Node*& p, bool& taller);

        void destroy(Node*& p);

    public:
        AVLTree() : root(nullptr) {}
        ~AVLTree() {destroy(root);}
        AVLTree(const AVLTree&) = delete;
        AVLTree& operator=(const AVLTree&) = delete;

        void insert(const T& val) { bool isTaller = false; insert(val, root, isTaller); }
        void remove(const T& val) { bool isShorter = false; remove(val, root, isShorter); }
        void print();
};

template <typename T>
void AVLTree<T>::destroy(typename AVLTree<T>::Node*& p)
{
    if(p == nullptr)
        return;
    destroy(p->lchild);
    destroy(p->rchild);
    delete p;
    p = nullptr;
}

template <typename T>
void AVLTree<T>::rotate_L(typename AVLTree<T>::Node*& p)
{
    Node* left = p;
    p = p->rchild; int temp = p->bf;
    left->rchild = p->lchild;
    p->lchild = left;
    if(temp != 0)
        p->bf = left->bf = 0;
    else
    {
        p->bf = -1; left->bf = 1;
    }
}

template <typename T>
void AVLTree<T>::rotate_R(typename AVLTree<T>::Node*& p)
{
    Node* right = p;
    p = p->lchild; int temp = p->bf;
    right->lchild = p->rchild;
    p->rchild = right;
    if(temp != 0)
        p->bf = right->bf = 0;
    else
    {
        p->bf = 1; right->bf = -1;
    }
}

template <typename T>
void AVLTree<T>::rotate_LR(typename AVLTree<T>::Node*& p)
{
    Node* left = p->lchild, *right = p;
    p = left->rchild;
    left->rchild = p->lchild; right->lchild = p->rchild;
    p->lchild = left; p->rchild = right;
    switch (p->bf)
    {
    case -1:
        left->bf = 0;
        right->bf = 1;
        break;
    case 1:
        left->bf = -1;
        right->bf = 0;
        break;
    default:
        left->bf = 0;
        right->bf = 0;
        break;
    }
    p->bf = 0;
}

template <typename T>
void AVLTree<T>::rotate_RL(typename AVLTree<T>::Node*& p)
{
    Node* right = p->rchild, *left = p;
    p = right->lchild;
    right->lchild = p->rchild; left->rchild = p->lchild;
    p->lchild = left; p->rchild = right;
    switch (p->bf)
    {
    case 1:
        left->bf = -1;
        right->bf = 0;
        break;
    case -1:
        left->bf = 0;
        right->bf = 1;
        break;
    default:
        left->bf = 0;
        right->bf = 0;
        break;
    }
    p->bf = 0;
}

template <typename T>
void AVLTree<T>::balance_l_insert(typename AVLTree<T>::Node*& p, bool& taller)
{
    switch (p->bf)
    {
        case -1:
            taller = false;
            if(p->lchild->bf < 0)
                rotate_R(p);
            else
                rotate_LR(p);
            break;           
        case 0:
            p->bf = -1; taller = true;
            break;
        case 1:
            p->bf = 0; taller = false;
            break;
        default:
            break;
    }
}

template <typename T>
void AVLTree<T>::balance_r_insert(typename AVLTree<T>::Node*& p, bool& taller)
{
    switch (p->bf)
    {
        case 1:
            taller = false;
            if(p->rchild->bf > 0)
                rotate_L(p);
            else
                rotate_RL(p); 
            break;          
        case 0:
            p->bf = 1; taller = true;
            break;
        case -1:
            p->bf = 0; taller = false;
            break;
        default:
            break;
    }
}

template <typename T>
void AVLTree<T>::insert(const T& val, typename AVLTree<T>::Node*& p, bool& taller)
{
    if(p == nullptr)
    {
        p = new typename AVLTree<T>::Node(val);
        taller = true;
    }
    else if(val <= p->data)
    {    
        insert(val, p->lchild, taller);      
        if(taller)
            balance_l_insert(p, taller);
    }
    else
    {
        insert(val, p->rchild, taller);
        if(taller)
            balance_r_insert(p, taller);
    }
}

template <typename T>
void AVLTree<T>::balance_l_remove(typename AVLTree<T>::Node*& p, bool& shorter)
{
    switch(p->bf)
    {
        case 1:
            shorter = (p->rchild->bf == 0) ? false : true;
            if(p->rchild->bf >= 0)
                rotate_L(p);
            else
                rotate_RL(p);
            break;
        case 0:
            p->bf = 1; shorter = false;
            break;
        case -1:
            p->bf = 0; shorter = true;     
            break;    
    }
}

template <typename T>
void AVLTree<T>::balance_r_remove(typename AVLTree<T>::Node*& p, bool& shorter)
{
    switch(p->bf)
    {
        case -1:
            shorter = (p->lchild->bf == 0) ? false : true;
            if(p->lchild->bf <= 0) 
                rotate_R(p);
            else
                rotate_LR(p);
            break;
        case 0:
            p->bf = -1; shorter = false;
            break;
        case 1:
            p->bf = 0; shorter = true;
            break;    
    }
}

template <typename T>
void AVLTree<T>::remove(const T& val, typename AVLTree<T>::Node*& p, bool& shorter)
{
    if(p == nullptr)
        {shorter = false; return;}

    if(val < p->data)
    {
        remove(val, p->lchild, shorter);
        if(shorter)
            balance_l_remove(p, shorter);
    }
    else if(val > p->data)
    {
        remove(val, p->rchild, shorter);
        if(shorter)
            balance_r_remove(p, shorter);
    }
    else
    {
        typename AVLTree<T>::Node* temp = p;
        if(p -> lchild == nullptr)
        {
            p = p -> rchild;
            delete temp;
            shorter = true;
        }
        else if(p -> rchild == nullptr)
        {
            p = p -> lchild;
            delete temp;
            shorter = true;
        }
        else
        {
            temp = p -> rchild;
            while(temp -> lchild != nullptr)
                temp = temp -> lchild;
            p -> data = temp -> data;
            remove(temp -> data, p -> rchild, shorter);
            if(shorter)
                balance_r_remove(p, shorter);
        }
    }
}

template <typename T>
void AVLTree<T>::print()
{
    if (root == nullptr) {
        std::cout << "Empty Tree" << std::endl;
        return;
    }
    std::cout << "---------------------------------------" << std::endl;
    // 初始缩进为0，类型为0(根)
    printStructure(root, 0, 0);
    std::cout << "---------------------------------------" << std::endl;
}


#endif