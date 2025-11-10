#ifndef BINTREEHEADER
#define BINTREEHEADER
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "threadtree.h"

template <typename T>
class BinTree
{
private:
    struct BinNode 
    {
        T data;   
        BinNode *lchild;      
        BinNode *rchild;  
        BinNode(T val, BinNode* l = nullptr, BinNode* r = nullptr) : data(val), lchild(l), rchild(r) {}
    };

    BinNode* root;
    void destroy(BinNode* p);
    void convert(BinNode*& p,const std::string&, size_t& index);
    BinNode* getLCA(BinNode*, char X, char Y);
    void print_pre(BinNode* p) {if(!p) return; std::cout << p -> data << " "; print_pre(p -> lchild); print_pre(p -> rchild);}
    void print_in(BinNode* p) {if(!p) return; print_in(p -> lchild); std::cout << p -> data << " "; print_in(p -> rchild);}
    void print_post(BinNode* p) {if(!p) return; print_post(p -> lchild); print_post(p -> rchild); std::cout << p -> data << " ";}
    int maxDistance(BinNode* root);
    BinNode* construct(const std::vector<T>& pre, const std::vector<T>& in, size_t pre_l, size_t pre_r, size_t in_l, size_t in_r);
public:
    BinTree() : root(nullptr) {}
    ~BinTree() {destroy(root);}
    void convert(const std::string& s) {size_t count = 0; convert(root, s, count);}   //string -> BinTree<char>
    BinNode* getLCA(char X, char Y) {return getLCA(root, X, Y);}
    void print_pre() {print_pre(root);}
    void print_in() {print_in(root);}
    void print_post() {print_post(root);}
    int maxDistance() {return maxDistance(root);}
    void construct(const std::vector<T>& pre, const std::vector<T> in) {root = construct(pre, in, 0, pre.size(), 0, in.size());}
};

template <typename T>
void BinTree<T>::destroy(BinNode* p)
{
    if(p == nullptr)
        return;
    destroy(p -> lchild);
    destroy(p -> rchild);
    delete p;
}

template <>
void BinTree<char>::convert(BinNode*& p, const std::string& s, size_t& index)
{
    if(index >= s.size())
        return;

    char c = s[index++];
    if(c != '#')
    {
        p = new BinNode(c);
        convert(p -> lchild, s, index);
        convert(p -> rchild, s, index);
    }
    else
        p = nullptr;

}

template<>
typename BinTree<char>::BinNode* BinTree<char>::getLCA(BinNode* r, char X, char Y)
{
    if(r == nullptr)
        return nullptr;

    if(r -> data == X || r -> data == Y)
        return r;
    BinNode* leftLCA = getLCA(r -> lchild, X, Y);
    BinNode* rightLCA = getLCA(r -> rchild, X, Y);

    if(leftLCA != nullptr && rightLCA != nullptr)
        return r;
    return leftLCA ? leftLCA : rightLCA;
}

template<typename T>
int BinTree<T>::maxDistance(BinNode* r)
{
    static int maxDist = 0; 
    if(r == nullptr)
        return 0;
    
    int left = maxDistance(r->lchild);
    int right = maxDistance(r->rchild);

    maxDist = std::max(maxDist, left + right);
    if(r != root)
        return std::max(left, right) + 1;
    else    
        return maxDist;
}

template <typename T>
typename BinTree<T>::BinNode* BinTree<T>::construct(const std::vector<T>& pre, const std::vector<T>& in, size_t pre_l, size_t pre_r, size_t in_l, size_t in_r)
{
    if(pre_l >= pre_r)
        return nullptr;

    T newval = pre[pre_l];  size_t newindex; 
    BinNode* newnode = new BinNode(newval);
    if(pre_r == pre_l + 1)
        return newnode;
        
    for(size_t i = in_l; i < in_r; i++)
    {
        if(in[i] == newval)
        {    
            newindex = i;
            break;
        }
    }
    size_t newpredivision = pre_l + newindex - in_l + 1;

    newnode -> lchild = construct(pre, in, pre_l + 1, newpredivision, in_l, newindex);
    newnode -> rchild = construct(pre, in, newpredivision, pre_r, newindex + 1, in_r);
    return newnode;
}






#endif