#ifndef MYITERATOR_H
#define MYITERATOR_H

#include <stdlib.h>
#include <iterator>
template <typename ValueType>
class MyIterator : public std::iterator<std::input_iterator_tag, ValueType> {
    template <typename>
    friend class MyContainer;

    ValueType* p;

public:
    MyIterator(ValueType* p) :  p(p){}
    MyIterator() : p(nullptr){}
    MyIterator(const MyIterator &it): p(it.p){}

    bool operator != (MyIterator const& other) const
    {  return p != other.p;  }
    bool operator == (MyIterator const& other) const
    {  return p == other.p;  }
    typename MyIterator::reference operator*() const
    {  return *p;  }
    typename MyIterator::pointer operator->() const
    {  return &*p;  }
    MyIterator& operator++() {
        ++p;
        return *this;
    }
    MyIterator& operator--() {
        --p;
        return *this;
    }
};
#endif // MYITERATOR_H
