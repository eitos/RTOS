#ifndef __SWAPTABLE_HPP__
#define __SWAPTABLE_HPP__
#include <inttypes.h>

template<class T, uint8_t MaxSize>
class SwapTable_t {
 private:
    uint8_t actualSize;
    T elements[MaxSize];
 public:
    SwapTable_t();
    void add(const T & element);
    T & operator[](const uint8_t & index);
    void remove(uint8_t index);
    uint8_t size();
};

template<class T, uint8_t MaxSize>
SwapTable_t<T, MaxSize>::SwapTable_t() {
    this->actualSize = 0;
}

template<class T, uint8_t MaxSize>
void SwapTable_t<T, MaxSize>::add(const T & element) {
    this->elements[this->actualSize] = element;
    this->actualSize++;
}

template<class T, uint8_t MaxSize>
T & SwapTable_t<T, MaxSize>::operator[](const uint8_t & index) {
    return this->elements[index];
}

template<class T, uint8_t MaxSize>
void SwapTable_t<T, MaxSize>::remove(uint8_t index) {
    this->elements[index] = this->elements[this->actualSize-1];
    this->actualSize--;
}

template<class T, uint8_t MaxSize>
uint8_t SwapTable_t<T, MaxSize>::size() {
    return this->actualSize;
}

#endif
