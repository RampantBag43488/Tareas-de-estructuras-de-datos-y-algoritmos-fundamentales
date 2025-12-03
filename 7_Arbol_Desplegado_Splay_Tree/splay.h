#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
	if (val > value) {
		if (right != 0){
			return right->add(val);
		}
		else {
			right = new Node<T>(val);
			right->parent = this;
		}
		return right;
	}
	else {
		if (left != 0){
			return left->add(val);
		}
		else {
			left = new Node<T>(val);
			left->parent = this;
		}
		return left;
	}
}

template <class T>
Node<T>* Node<T>::find(T val) {
    if (val == value) {
        return this;
    }
    if (val > value) {
        if (right == 0) {
			return 0;
		}
        return right->find(val);
    } else {
        if (left == 0) {
			return 0;
		}
        return left->find(val);
    }
}

template <class T> 
Node<T>* Node<T>::succesor() {
    if (right == 0) {
        return 0;
    }

    if (right->left == 0) {
        Node<T>* succ = right;
        right = succ->right;
        if (right != 0) {
            right->parent = this;
        }
        succ->right = 0;
        succ->parent = 0;
        return succ;
    }

    Node<T>* parent = right;
    Node<T>* child  = right->left;

    while (child->left != 0) {
        parent = child;
        child  = child->left;
    }

    parent->left = child->right;
    if (child->right != 0) {
        child->right->parent = parent;
    }

    child->right  = 0;
    child->parent = 0;

    return child;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
    if (val < value) {
        if (left == 0) {
			return this;
		}

        if (left->value == val) {
            Node<T>* target = left;
            Node<T>* ret    = this;

            if (target->left == 0 || target->right == 0) {
				Node<T>* child;

				if (target->left != 0) {
					child = target->left;
				}
				else {
					child = target->right;
				}
                left = child;
                if (child != 0) {
                    child->parent = this;
                }
                delete target;
                return ret;
            }

            Node<T>* succ = target->right;
            while (succ->left != 0) {
                succ = succ->left;
            }

            Node<T>* succParent = succ->parent;
            Node<T>* succRight  = succ->right;

            if (succParent != target) {
                succParent->left = succRight;
                if (succRight != 0) {
                    succRight->parent = succParent;
                }

                succ->right = target->right;
                succ->right->parent = succ;
            } 

            succ->left = target->left;
            succ->left->parent = succ;

            left = succ;
            succ->parent = this;

            delete target;
            return succ;
        } 
        return left->remove(val);
    }


    else if (val > value) {
        if (right == 0) {
			return this;
		}

        if (right->value == val) {
            Node<T>* target = right;
            Node<T>* ret    = this;

            if (target->left == 0 || target->right == 0) {
				Node<T>* child;

				if (target->left != 0) {
					child = target->left;
				}
				else {
					child = target->right;
				}
                right = child;
                if (child != 0) {
                    child->parent = this;
                }
                delete target;
                return ret;
            }

            Node<T>* succ = target->right;
            while (succ->left != 0) {
                succ = succ->left;
            }

            Node<T>* succParent = succ->parent;
            Node<T>* succRight  = succ->right;

            if (succParent != target) {
                succParent->left = succRight;
                if (succRight != 0) {
                    succRight->parent = succParent;
                }

                succ->right = target->right;
                succ->right->parent = succ;
            }

            succ->left = target->left;
            succ->left->parent = succ;

            right = succ;
            succ->parent = this;

            delete target;
            return succ;
        }
        return right->remove(val);
    }

    return this;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent; // parent
			Node<T>*g = p->parent; // granparent
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	std::string inorder() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}



template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {

	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		if (found != 0) {
			root = root->splay(root,found);
			return (root->value == val);
		}
		return false;
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif