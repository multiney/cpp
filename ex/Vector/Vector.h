#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

using std::cout;
using std::endl;

template<class T>
class Vector {
public:
// iterator
    typedef Vector<T> Self;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;

    iterator begin() { return _start; }
    // attention: const obj must return const_iterator
    const_iterator begin() const { return _start; }
    const_iterator cbegin() const { return _start; }

    iterator end() { return _finish; }
    const_iterator end() const { return _finish; }
    const_iterator cend() const { return _finish; }

public:
// init
    Vector(size_type size = 0, const T &data = T());
    Vector(const Self &other);
    template<class Iterator>
    Vector(Iterator first, Iterator last);
    ~Vector();

// overloaded operation function
    Vector& operator=(const Vector<T> &other);
    T& operator[](size_type i);
    const T& operator[](size_type i) const;

// function
    void push_back(const T &item);
    void pop_back();
    T& back();
    const T& back() const;
    size_type size() const;
    bool empty() const;
    size_type capacity() const;
    void clear();
    void reserve(size_type n);
    void resize(size_type newSize, const T &item);
    iterator insert(iterator pos, size_type n, const T &item);

private:
    T *_start;
    T *_finish;
    T *_endofstorage;
};

// constructor function

template<class T>
Vector<T>::Vector(size_type size, const T &data) :
    _start(nullptr),
    _finish(nullptr),
    _endofstorage(nullptr)
{
    if (size == 0)// 若size是0，那么capacity以及arr是否赋值为上一行的值？ Ans:是的
        return;
    _start = new T[size];
    for (size_type i = 0; i < size; ++i)
        _start[i] = data;
    _endofstorage = _finish = _start + size;
}

template<class T>
Vector<T>::Vector(const Self &other) {
    _start = _finish = new T[other.size()];
    _endofstorage = _start + other.size();
    const_iterator it = other.begin();
    while (_finish != _endofstorage)
        *_finish++ = *it++;
}

template<class T>
template<class Iterator>
Vector<T>::Vector(Iterator first, Iterator last) {
    size_type count = 0;
    auto it = first;
    while (it++ != last)
        ++count;
    _start = _finish = new T[count];
    _endofstorage = _start + count;
    while (_finish != _endofstorage)
        *_finish++ = *first++;
}

template<class T>
Vector<T>::~Vector() {
    if (_start != nullptr)
        delete [] _start;
}

// overloading operator function
template<class T>
Vector<T>& Vector<T>::operator=(const Self &other) {
    clear();
    _start = _finish = new T[other.size()];
    _endofstorage = _start + other.size();
    iterator it = other.begin();
    while (_finish != _endofstorage) {
        *_finish = *it;
        ++_finish;
        ++it;
    }
}

template<class T>
T& Vector<T>::operator[](size_type i) {
    if (i < 0 || i + _start >= _finish) // 异常处理
        ;
    return *(_start + i);
}

template<class T>
const T& Vector<T>::operator[](size_type i) const {
    if (i < 0 || i + _start >= _finish)
        ;
    return *(_start + i);
}

// function
template<class T>
void Vector<T>::push_back(const T &item) {
    if (_finish == _endofstorage)
        reserve(_start == _finish ? 1 : ((_finish - _start) << 1));
    *_finish++ = item;
}

template<class T>
void Vector<T>::pop_back() {
    --_finish;
}

template<class T>
T& Vector<T>::back() {
    if (_finish == _start)
        ;// exception
    return *(_finish - 1);
}

template<class T>
const T& Vector<T>::back() const {
    if (empty())
        ; //exception
    return *(_finish - 1);
}

template<class T>
size_t Vector<T>::size() const {
    return size_type(_finish - _start);
}

template<class T>
bool Vector<T>::empty() const {
    return _start == _finish;
}

template<class T>
size_t Vector<T>::capacity() const {
    return size_type(_endofstorage - _start);
}

template<class T>
void Vector<T>::clear() {
    if (_start != nullptr) {
        delete [] _start;
        _start = _finish = _endofstorage = nullptr;
    }
}

// reserve capacity

template<class T>
void Vector<T>::reserve(size_type n) {
    if (_start != nullptr) {
        if (n <= _endofstorage - _start)
            return;
        else {
            T *temp = new T[n];
            for (iterator it = _start; it < _finish; ++it)
                *temp++ = *it;
            delete [] _start;
            _start = temp - (_finish - _start);
            _finish = temp;
            _endofstorage = _start + n;
        }
    }
    else {
        _start = _finish = new T[n];
        _endofstorage = _start + n;
    }
}

template<class T>
void Vector<T>::resize(size_type newSize, const T &item) {
    if (_start == nullptr) {
        _start = _finish = new T[newSize];
        _endofstorage = _start + newSize;
        while (newSize--)
            *_finish++ = item;
    }
    else {
        if (newSize > _finish - _start)
            insert(_finish, newSize - (_finish - _start), item);
        else
            _finish = newSize + _start;
    }
}

template<class T>
T* Vector<T>::insert(iterator pos, size_type n, const T &item) {
    if (_start == nullptr) {
        _start = _finish = new T[n];
        _endofstorage = _start + n;
        while (_finish != _endofstorage)
            *_finish++ = item;
        return _start;
    }
    else {
        if (_finish + n > _endofstorage) {
            T *temp = new T[_endofstorage - _start + n];
            _finish = temp;
            iterator it = _start;
            _endofstorage = _finish + (_endofstorage - _start + n);
            while (it != pos)
                *_finish++ = *it++;
            while (n--)
                *_finish++ = item;
            while (_finish != _endofstorage)
                *_finish++ = *it++;
            size_type offset = pos - _start;
            delete [] _start;
            _start = temp;
            return _start + offset;
        }
        else {
            if (pos < _finish) {
                _finish += n;
                T *it = _finish;
                T *endInsert = pos + n;
                while (it-- != endInsert)
                    *it = *(it - n);
                while (it-- != pos)
                    *it = item;
            }
            else
                while (n--)
                    *_finish++ = item;
            return pos;
        }
    }
}

/*
template<class T>
void Vector<T>::reserve(size_type n, bool copy) {
    T *newArr = new T[n];
    if (newArr == nullptr) {
        // exception handler
    }
    if (copy)
        for (size_type i = 0; i < vSize; ++i)
            newArr[i] = arr[i];
    if (arr != nullptr)
        delete [] arr;
    vCapacity = n;
    arr = newArr;
}
*/

#endif // !VECTOR_H_
