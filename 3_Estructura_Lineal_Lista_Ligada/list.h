#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;

template <class T>
class Link {
private:
	Link(T val, Link<T> *nxt = 0) : value(val), next(nxt) {}
	Link(const Link<T> &source) : value(source.value), next(source.next) {}
	T value;
	Link<T> *next;

	friend class List<T>;
};

template <class T>
class List {
public:
	List();
	~List();

	void insertion(T val);
	int search(T val) const;
	void update(int index, T val);
	void deleteAt(int index);
    void clear();

	std::string toString() const;

private:
	Link<T> *head;
	int size;
};

// Implementación

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
void List<T>::clear() {
	Link<T> *p; 
    Link<T> *pt;
	p = head;
	while (p != 0) {
		pt = p->next;
		delete p;
		p = pt;
	}
	head = 0;
	size = 0;
}

template <class T>
void List<T>::insertion(T val) {
	if (head == 0) {
		head = new Link<T>(val);
	} 
    else {
		Link<T> *p = head;
		while (p->next != 0) {
			p = p->next;
		}
		p->next = new Link<T>(val);
	}
	size++;
}

template <class T>
int List<T>::search(T val) const {
	int pos = 0;
	Link<T> *p = head;
	while (p != 0) {
		if (p->value == val) {
			return pos;
		}
		p = p->next;
		pos++;
	}
	return -1;
}

template <class T>
void List<T>::update(int index, T val) {
	if (index < 0 || index >= size) {
		return;
	}
	Link<T> *p = head;
	int pos = 0;
	while (pos < index) {
		p = p->next;
		pos++;
	}
	p->value = val;
}

template <class T>
void List<T>::deleteAt(int index) {
	if (index < 0 || index >= size) {
		return;
	}

	Link<T> *p = head;
    Link<T> *pt = 0;

	if (index == 0) {
		head = head->next;
		delete p;
	} 
    else {
		int pos = 0;
		while (pos < index) {
			pt = p;
			p = p->next;
			pos++;
		}
		pt->next = p->next;
		delete p;
	}

	size--;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p = head;

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

#endif /* LIST_H_ */
