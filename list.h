#include <iostream>


template <typename T>
class List
{
    private:
        struct Node
        {
            T data;
            Node* next;
            Node(T d, Node* n = nullptr) : data(d), next(n) {}
        };
        Node* head, *rear;
        size_t count;
    public:
        List() : head(nullptr), rear(nullptr), count(0) {}
        ~List() {auto p = head; while(head) {head = head -> next; delete p; p = head;}}
        void push_back(const T& val);
        void push_front(const T& val);
        void print() const;
        size_t size() const {return count;}
        bool empty() const {return count == 0;}
        Node* begin() {return head;}
        Node* end() {return rear ? rear -> next : nullptr;}
        void insert(Node* p, T val);

};

template <typename T>
void List<T>::push_back(const T& val)
{
    if(count == 0)
        head = rear = new Node(val);
    else
    {
        rear -> next = new Node(val);
        rear = rear -> next;
    }
    count++;
}

template <typename T>
void List<T>::push_front(const T& val)
{
    if(count == 0)
        head = rear = new Node(val);
    else
        head = new Node(val, head);
    count++;
}

template <typename T>
void List<T>::print() const
{
    std::cout << "(";
    auto p = head;
    for(p = head; p != rear; p = p -> next)
        std::cout << p -> data << " -> ";
    if(p != nullptr)
        std::cout << p -> data;
    std::cout << ")";
}

template <typename T>
void List<T>::insert(Node* p, T val)
{
    if(p == nullptr)
        return;
    Node* newnode = new Node(val, p -> next);
    p -> next = newnode;
    count++;
}

template <typename NodeType>
NodeType* advance(NodeType* p, size_t n)
{
    while (p != nullptr && n--)
        p = p->next;
    return p;
}
