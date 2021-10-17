#include "mycontainer.h"
#include "rangeexception.h"
#include <malloc.h>
#include <QDebug>
//Cons|Des-tructors
template <typename ValueType>
MyContainer<ValueType>::MyContainer() {
    this->size = 0;
    this->info = nullptr;
}
template <typename ValueType>
MyContainer<ValueType>::MyContainer(const ValueType &obj) {
    this->size = 0;
    this->push_back(obj);
}
template <typename ValueType>
MyContainer<ValueType>::MyContainer(ValueType* arr) {
    this->info = nullptr;
    this->size = _msize(arr)/sizeof(ValueType);
    for(size_t i = 0; i < this->size; ++i)
        this->push_back(arr[i]);
}
template <typename ValueType>
MyContainer<ValueType>::MyContainer(const MyContainer &obj) {
    this->info = nullptr;
    this->size = obj.size;
    for(size_t i = 0; i < this->size; ++i)
        this->push_back(obj[i]);
}
template <typename ValueType>
MyContainer<ValueType>::~MyContainer() {
    delete this->info;
}
//iter
template <typename ValueType>
typename MyContainer<ValueType>::iterator MyContainer<ValueType>::begin()
{  return  iterator(info);  }
template <typename ValueType>
typename MyContainer<ValueType>::iterator MyContainer<ValueType>::end()
{  return iterator(info+size);  }
//Vector-like
template <typename ValueType>
size_t MyContainer<ValueType>::length()
{  return this->size;  }
template <typename ValueType>
int MyContainer<ValueType>::push_back(const ValueType &obj) {
    ValueType* temp;
    temp = new ValueType [this->size + 1];
    for(size_t i=0; i < this->size; ++i)
        temp[i] = this->info[i];
    temp[this->size] = obj;
    delete this->info;
    this->info = temp;
    this->size++;

    return 1;
}
template <typename ValueType>
int MyContainer<ValueType>::push_front(const ValueType &obj) {
    ValueType* temp;
    temp = new ValueType[++this->size];
    temp[0] = obj;
    for(size_t i= 1;i<this->size;i++)
        temp[i] = this->info[i];
    delete this->info;
    this->info = temp;
    return 1;
}
template <typename ValueType>
int MyContainer<ValueType>::pop_back() {
    if(this->size)
    {
        size--;
        delete info[size];
        return 1;
    }
    return 0;
}
template <typename ValueType>
int MyContainer<ValueType>::pop_front() {
    if(!this->size)
        return 0;
    this->size--;
    for(size_t i=0; i<this->size;++i)
        this->info[i] = this->info[i+1];
    return 1;
}
template <typename ValueType>
int MyContainer<ValueType>::swap(index a, index b) {
    if(std::max(a,b) > this->size)
        return 0;
    ValueType t = this->info[a];
    this->info[a] = this->info[b];
    this->info[b] = t;
    return 1;
}
template <typename ValueType>
int MyContainer<ValueType>::swap(MyContainer::iterator a, MyContainer::iterator b) {
    std::swap(a, b);
    return 1;
}

template <typename ValueType>
void MyContainer<ValueType>::clear(void) {
    this->size = 0;
    delete this->info;
    this->info = nullptr;
}
template <typename ValueType>
bool MyContainer<ValueType>::empty() {
    return !this->size;
}
template <typename ValueType>
index MyContainer<ValueType>::at(const ValueType &obj) {
    for(size_t i=0;i<this->size;i++)
        if(info[i] == obj)
            return i;
    return -1;
}
template <typename ValueType>
int MyContainer<ValueType>::insert(index after,const ValueType &obj) {
    if(after >= this->size)
    {
        this->push_back(obj);
        return 1;
    }
    ValueType* temp = new ValueType[++this->size];
    for(size_t i =0; i < static_cast<size_t>(after);++i)
        temp[i] = this->info[i];
    temp[after] = obj;
    for(size_t i = after+1;i<this->size;i++)
        temp[i] = this->info[i-1];
    delete this->info;
    this->info = temp;
    return 1;
}
template <typename ValueType>
ValueType MyContainer<ValueType>::back() {
    return *(this->info+(this->size-1));
}
template <typename ValueType>
ValueType MyContainer<ValueType>::front() {
    return *(this->info);
}
//opers
template <typename ValueType>
ValueType MyContainer<ValueType>::operator[](const size_t &n) {
    if( n < this->size )
        return this->info[n];
    throw new RangeException(n);
}

template <typename ValueType>
MyContainer<ValueType>& MyContainer<ValueType>::operator=(MyContainer<ValueType> &other) {
    this->clear();
    for(unsigned i = 0; i < other.length();++i)
        this->push_back(other[i]);
}
