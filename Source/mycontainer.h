#ifndef MYCONTAINER_H
#define MYCONTAINER_H
#include "myiterator.h"
typedef int index;
template<typename ValueType>
class MyContainer
{
    size_t size;
    ValueType* info;
public:

    typedef MyIterator<ValueType> iterator;
    iterator begin();
    iterator end();

    int push_back(const ValueType&);
    int push_front(const ValueType&);
    int pop_back();
    int pop_front();
    int swap(index,index);
    int swap(iterator, iterator);
    int insert(index after, const ValueType&);
    index at(const ValueType&);
    size_t length();
    bool empty();
    void clear(void);
    ValueType back();
    ValueType front();
    MyContainer();
    MyContainer(const ValueType&);
    MyContainer(ValueType*);
    MyContainer(const MyContainer&);
    ~MyContainer();
    ValueType operator[] (const size_t&);
    MyContainer& operator=(MyContainer& other);
};
#include "mycontainer.cpp"

#endif // MYCONTAINER_H
