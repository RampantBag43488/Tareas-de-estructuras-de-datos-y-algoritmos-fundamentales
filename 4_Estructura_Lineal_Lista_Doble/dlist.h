#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>

template <class T>
class DLink {
public:
    T value;
    DLink<T>* previous;
    DLink<T>* next;

    DLink(T v);
    DLink(const T& v, DLink<T> *p, DLink<T> *n);
};


template <class T>
class DList {
private:
    DLink<T>* head;
    DLink<T>* tail;
    int size;


public:
    DList();

    void insertion(const T& val);
    int  search(const T& val) const;
    void update(int index, const T& val);
    void deleteAt(int index);

    std::string toStringForward() const;
    std::string toStringBackward() const;
};



// DLink<T>
template <class T>
DLink<T>::DLink(T v) : value(v), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(const T& v, DLink<T> *p, DLink<T> *n) : value(v), previous(p), next(n) {}

// DList<T>
template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}


template <class T>
void DList<T>::insertion(const T& val) {
    DLink<T> *p = new DLink<T>(val);
    if (head == 0) {
        head = tail = p;
    } else {
        p->previous = tail;
        tail->next = p;
        tail = p;
    }
    ++size;
}

template <class T>
int DList<T>::search(const T& val) const {
    DLink<T> *p = head;
    int i = 0;
    while (p != 0) {
        if (p->value == val) return i;
        p = p->next;
        ++i;
    }
    return -1;
}

template <class T>
void DList<T>::update(int index, const T& val) {
    if (index < 0 || index >= size) return;
    DLink<T> *p = head;
    for (int i = 0; i < index; ++i) {
        p = p->next;
    }
    p->value = val;
}

template <class T>
void DList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) return;

    DLink<T> *p = head;
    for (int i = 0; i < index; ++i) {
        p = p->next;
    }

    if (p->previous != 0) {
        p->previous->next = p->next;
    } else {
        head = p->next;
    }

    if (p->next != 0) {
        p->next->previous = p->previous;
    } else {
        tail = p->previous;
    }

    delete p;
    --size;
}

template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

#endif // DLIST_H
