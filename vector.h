#ifndef VECTORHEADER
#define VECTORHEADER

#include<iostream>
#include <cstddef>
using std::size_t;

template<typename T>
class vector
{
    using iterator = T*;
    using const_iterator = const T*;
    template<typename R>
    friend std::ostream& operator<<(std::ostream& out, const vector<R>& v);

    private:
        iterator data;
        size_t _size;
        size_t _capacity;

        void destruct() {delete[] data; data = nullptr; _size = _capacity = 0;}

    public:
        vector() : data(nullptr), _size(0), _capacity(0) {}
        vector(int a) : _size(0), _capacity((size_t)a) {data = new T[a];}
        vector(size_t a) : _size(0), _capacity(a) { data = new T[a]; }
        vector(int a, const T& val);
        vector(const vector& other);
        ~vector() {destruct();}

        size_t size() const {return _size;} //gets the size of vector
        size_t capacity() const {return _capacity;}  //gets the capacity of vector
        bool empty() const {return _size == 0;}  //returns 1 if the vector is empty
        T& operator[](int index) {return data[index];}
        const T& operator[](int index) const {return data[index];} 
        iterator begin() {return data;}
        iterator end() {return data + _size;}
        const_iterator begin() const {return data;}
        const_iterator end() const {return data + _size;}

        void push_back(const T& val);
        void pop_back() {if(_size) _size--;}
        void clear() { _size = 0;}
        void resize(size_t count, const T& value = T());
        void reserve(size_t ncap);
        void assign(size_t n, const T& val);


};

//construct(n*val)
template<typename T>
vector<T>::vector(int a, const T& val)
{
    _size = (size_t)a; _capacity = 2 * a;
    for(size_t __i = 0; __i < _size; __i++)
        data[__i] = val;

}

//construct the same vector
template<typename T>
vector<T>::vector(const vector<T>& other)
{
    data = new T[other._capacity];

    _size = other._size;
    _capacity = other._capacity;
    for(size_t __i = 0; __i < _size; __i++)
        data[__i] = other[__i];
}

//add T to the back of the vector
template<typename T>
void vector<T>::push_back(const T& val)
{
    //needs larger space
    if(_size == _capacity)
    {
        _capacity = 2 * _capacity + 1;
        iterator newdata = new T[_capacity];
        for(size_t __i = 0; __i < _size; __i++)
            newdata[__i] = data[__i];
        delete[] data;
        data = newdata;
    }
    data[_size++] = val;
}

//print out the vector
template<typename R>
std::ostream& operator<<(std::ostream& out, const vector<R>& v)
{
    out << "(";
    size_t s = v.size();
    for(size_t __i = 0; __i < s; __i++)
    {
        out << v.data[__i];
        if(__i != s - 1)
        out << ", ";
    }
    out << ")";
    return out;
}

template<typename T>
void vector<T>::resize(size_t nsize, const T& value)
{
    if(nsize > _capacity)
    {
        reserve(nsize);
        _capacity = nsize;
    }
    if (nsize > _size)
    {
        for (size_t i = _size; i < nsize; i++)
            data[i] = value;
    }
    _size = nsize;
}

template<typename T>
void vector<T>::reserve(size_t ncap)
{
    if(ncap > _capacity)
    {   
        iterator ndata = new T[ncap];
        for(size_t __i = 0; __i < _size; __i++)
            ndata[__i] = data[__i];
        delete[] data;
        data = ndata;
    }
}

template<typename T>
void vector<T>::assign(size_t n, const T& val)
{
    if (n > _capacity)
        reserve(n);  // 扩容

    for (size_t i = 0; i < n; ++i)
        data[i] = val;

    _size = n;
}


#endif        