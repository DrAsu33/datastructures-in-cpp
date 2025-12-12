#include <iostream>
#include <string>
using std::cin, std::cout;

template <typename T>
class GenList
{
    private:
        struct node
        {
            bool utype;   //0 for listhead, 1 for atom
            union {T value; node* hlink;} info;
            node* tlink;
            node(bool u = 0) : utype(u), tlink(nullptr) {if (utype == 0) info.hlink = nullptr;}
        };
        node* first;
        node* conv(const std::string& s, size_t&); //string -> GenList<char>
        void print(node *p);
        void destroy(node *p);

    public:
        GenList() : first(nullptr) {}
        ~GenList() {destroy();}
        void conv(const std::string& s) {size_t  pos = 0; first = conv(s, pos);}
        void print() {print(first);}
        bool equal(node* s, node* t);
        bool equal(const GenList& other) {return equal(this -> first, other.first);}
};

template<>
GenList<char>::node* GenList<char>::conv(const std::string& s, size_t& pos)
{
    node* head = nullptr;
    node* last = nullptr;

    while(pos < s.size())
    {    
        if(s[pos] == '(')
        {
            pos++;
            node* newnode = new node(0);
            newnode -> info.hlink = conv(s, pos);
            if(head == nullptr)
                last = head = newnode;
            else
            {    
                last -> tlink = newnode;
                last = newnode;
            }
        }
        else if(s[pos] == ' ' || s[pos] == '\t' || s[pos] == ',')
            pos++;
        else if(s[pos] == ')')
        {
            pos++;
            return head;
        }
        else
        {
            node* newnode = new node(1);
            newnode -> info.value = s[pos];
            if(head == nullptr)
                head = last = newnode;
            else
            {
                last -> tlink = newnode;
                last = newnode; 
            }
            pos++;
        }
    }
    return head;
}

template <typename T>
void GenList<T>::print(typename GenList<T>::node* p)
{
    if(p == nullptr)
        return;

    if(p -> utype == 0)
    {
        cout << "(";
        print(p -> info.hlink);
        cout << ")";
        if(p ->tlink != nullptr)
            cout << ",";
        print(p -> tlink);
    }
    else
    {
        cout << p -> info.value;
        if(p ->tlink != nullptr)
            cout << ",";
        print(p -> tlink);
    }
}

template<typename T>
bool GenList<T>::equal(node* s, node* t)
{
    if(s == nullptr && t == nullptr)
        return 1;
    if(s == nullptr || t == nullptr)
        return 0;

    if(s -> utype != t -> utype)
        return 0;
    if(s -> utype == 1)
        return (s -> info.value == t -> info.value) && equal(s -> tlink, t -> tlink);
    else
        return equal(s -> info.hlink, t -> info.hlink) && equal(s -> tlink, t -> tlink);
    return 0;
}

template <typename T>
void GenList<T>::destroy(node* p)
{    
    node* temp;
    while(p != nullptr)
    {
        if(p -> utype == 0)
            destroy(p -> info.hlink);
        temp = p;
        p = p -> tlink;
        delete temp;
    }
}

int main()
{
    GenList<char> a, b, c;
    a.conv("(a,(b, c), d)"); b.conv("(a,(b, c), d)"); c.conv("(a,(b,c))");
    printf("GenList a: "); a.print(); cout << std::endl;
    printf("GenList b: "); b.print(); cout << std::endl;
    printf("GenList c: "); c.print(); cout << std::endl;
    printf("a == b : "); cout << a.equal(b) << std::endl;
    printf("a == c : "); cout << a.equal(c) << std::endl;
    return 0;
}