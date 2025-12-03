#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

template <class T>
class Node {
    public:
		T data;
        Node* left;
        Node* right;
        Node(T d) {data = d, left = 0, right = 0;};
		void add(T);
		void inorder(stringstream&, bool &);
		void preorder(stringstream&, bool &);
		void postorder(stringstream&, bool &);
		void levelbylevel(stringstream&, bool &);
		int height();
		void ancestors(stringstream&, int, bool&);
		int whatlevelamI(int);
};

template <class T>
void Node<T>::add(T val) {

    if (this->data > val){
		if (this->left != 0){
			this->left->add(val);
		}
		else {
			this->left = new Node<T>(val);
		}
	}
	else {
		if (this->right != 0){
			this->right->add(val);
		}
		else {
			this->right = new Node<T>(val);
		}
	}
}

template <class T>
void Node<T>::inorder(stringstream &aux, bool &first) {
	if (left != 0) {
		left->inorder(aux, first);
	}
	if(!first) {
		aux << " ";
	}
	aux << data;
	first = false;
	if (right != 0) {
		right->inorder(aux, first);
	}
}

template <class T>
void Node<T>::preorder(stringstream &aux, bool &first) {
	if(!first) {
		aux << " ";
	}
	aux << data;
	first = false;
	if (left != 0) {
		left->preorder(aux, first);
	}
	if (right != 0) {
		right->preorder(aux, first);
	}
}

template <class T>
void Node<T>::levelbylevel(stringstream &aux, bool &first) {
	queue<Node<T>*> q;
    q.push(this);

    while (!q.empty()) {
        Node<T>* cur = q.front();
        q.pop();

        if(!first) {
		aux << " ";
		}
        aux << cur->data;
		first = false;

        if (cur->left != 0) {
            q.push(cur->left);
        }
        if (cur->right != 0) {
            q.push(cur->right);
        }
    }
}

template <class T>
int Node<T>::height() {
	int lefth, righth;
	if(left != 0) {
		lefth = left->height();
	}
	else {
		lefth = 0;
	}

	if(right != 0) {
		righth = right->height();
	}
	else {
		righth = 0;
	}
    return 1 + max(lefth, righth);
}

template <class T>
void Node<T>::postorder(stringstream &aux, bool &first) {
	if (left != 0) {
		left->postorder(aux, first);
	}
	if (right != 0) {
		right->postorder(aux, first);
	}
	if(!first) {
		aux << " ";
	}
	aux << data;
	first = false;
}

template <class T>
void Node<T>::ancestors(stringstream &aux, int val, bool &first) {
	queue<Node<T>*> q;
	Node<T>* curr = this;

    while (curr != 0 && curr->data != val) {  
		q.push(curr);

        if (curr->data > val) {
            curr = curr->left;
        }
        if (curr->data < val) {
            curr = curr->right;
        }
    }

	if (curr != 0) {
		while (!q.empty()){
			if(!first) {
				aux << " ";
			}
			aux << q.front()->data;
			first = false;
			q.pop();
		}
	}
	else {
		return;
	}
}

template <class T>
int Node<T>::whatlevelamI(int val) {
	if(data == val) {
		return 1;
	}
	if(left != 0 && data > val) {
		int level = left->whatlevelamI(val);
		if (level != 0) {
			return level + 1;
		}
	}

	if(right != 0 && data < val) {
		int level = right->whatlevelamI(val);
		if (level != 0) {
			return level + 1;
		}
	}
	return 0;
}


template <class T>
class BST {
    private:
        Node<T>* root;

    public:
        BST();
        BST(T);
        void add(T);
		string visit();
		int height();
		string ancestors(int);
		int whatlevelamI(int);
		bool empty();
};

template <class T>
BST<T>::BST(T d) {
    root = new Node<T>(d);
}
template <class T>
BST<T>::BST() {
    root = 0;
}

template <class T>
void BST<T>::add(T val) {
	if (root != 0) {
		root->add(val);
	}
	else {
		root = new Node<T>(val);
	}
}

template <class T>
bool BST<T>::empty() {
	return (root == 0);
}

template <class T>
string BST<T>::visit() {
	stringstream aux;
	bool first = true;

	aux << "[";
	if (!empty()) {
		root->preorder(aux, first);
	}
	aux << "]\n";

	aux << "[";
	if (!empty()) {
		first = true;
		root->inorder(aux, first);
	}
	aux << "]\n";

	aux << "[";
	if (!empty()) {
		first = true;
		root->postorder(aux, first);
	}
	aux << "]\n";

	aux << "[";
	if (!empty()) {
		first = true;
		root->levelbylevel(aux, first);
	}

	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::height() {
	return root->height();
}

template <class T>
string BST<T>::ancestors(int v) {
	stringstream aux;
	bool first = true;

	aux << "[";
	if (!empty()) {
		root->ancestors(aux, v, first);
	}

	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(int v) {
	return root->whatlevelamI(v);
}



#endif