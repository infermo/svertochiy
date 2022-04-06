#pragma once

#include <QList>
/*
#include <Node.hpp>

template<typename T>
class List {
public:
    List();
    ~List();

    void pushBack(const T &value);
    void pushFront(const T &value);
    void clear();
    T popFront();
    int getLen() const;

    T operator[](int i) const;
    List<T>& operator <<(const T &value);

private:
    int _len = 0;
    Node<T> *_first = nullptr;
};

template<typename T> List<T>::List() {}

template<typename T> List<T>::~List() {
    clear();
}


template<typename T>
List<T>& List<T>::operator <<(const T &value) {
    pushBack(value);
    return *this;
}
template<typename T>
void List<T>::pushBack(const T & value) {
    if (_first == nullptr) {
        _first = new Node<T>(value);
    }
    else {
        auto *current = this->_first;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = new Node<T>(value);
    }

    _len++;
}
template<typename T>
void List<T>::pushFront(const T & value) {
    _first = new Node<T>(value, _first);
    _len++;
}
template<class T>
T List<T>::popFront() {
    auto temp = _first;
    _first = _first->next;

    T ret = temp->value;

    delete temp;
    _len--;

    return ret;
}
template<class T>
void List<T>::clear() {
    while (_len) {
        popFront();
    }
}
template<class T>
T List<T>::operator[](int i) const {
    auto node = _first;

    while(i != 0) {
        node = node->next;
        --i;

        if(node == nullptr) {
            return T();
        }
    }

    return node->value;
}

template<class T>
int List<T>::getLen() const {
    return _len;
}
//*/
