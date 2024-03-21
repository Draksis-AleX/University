#include <iostream>
#include <fstream>
using namespace std;

#define RED 'R'
#define BLACK 'B'

template <class T> class Node{
    private:
        T key;
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;
        char color;
    public:
        Node(T _key, char _color) : key(_key), color(_color){
            parent = left = right = NULL;
        }

        T getKey(){return key;}
        Node<T>* getParent(){return parent;}
        Node<T>* getLeft(){return left;}
        Node<T>* getRigth(){return right;}
        char getColor(){return color;}

        void setKey(T _key){key = _key;}
        void setParent(Node<T>* _parent){parent = _parent;}
        void setLeft(Node<T>* _left){left = _left;}
        void setRight(Node<T>* _right){right = _right;}
        void setColor(char _color){color = _color;}
};

template <class T> class RBT{
    private:
        Node<T>* root;

        double compare(T _a, T _b){return (double)_a - (double)_b;}

        Node<T>* search(T _key){
            Node<T>* iter = root;
            while(iter != NULL && compare(iter->getKey(), _key) != 0){
                if(compare(_key, iter->getKey()) > 0){
                    if(iter->getRigth() != NULL) iter = iter->getRigth();
                    else break;
                }
                else{
                    if(iter->getLeft() != NULL) iter = iter->getLeft();
                    else break;
                }
            }
            return iter;
        }

        bool isLeftChild(Node<T>* _node){return _node->getParent()->getLeft() == _node;}

        Node<T>* getUncle(Node<T>* _node){
            if(_node->getParent() == NULL || _node->getParent()->getParent() == NULL) return NULL;
            if(isLeftChild(_node->getParent())) return _node->getParent()->getParent()->getRigth();
            else return _node->getParent()->getParent()->getLeft();
        }

        void swapColors(Node<T>* _node1, Node<T>* _node2){
            char tmp = _node1->getColor();
            _node1->setColor(_node2->getColor());
            _node2->setColor(tmp);
        }

        void insertNodeUp(Node<T>* parent, Node<T>* newParent){
            if(parent->getParent() == NULL) root = newParent;
            else{
                if(isLeftChild(parent)) parent->getParent()->setLeft(newParent);
                else parent->getParent()->setRight(newParent);
            }

            newParent->setParent(parent->getParent());
            parent->setParent(newParent);
        }

        void leftRotate(Node<T>* _node){
            Node<T>* newParent = _node->getRigth();
            insertNodeUp(_node, newParent);
            _node->setRight(newParent->getLeft());
            if(newParent->getLeft() != NULL) newParent->getLeft()->setParent(_node);
            newParent->setLeft(_node);
        }

        void rightRotate(Node<T>* _node){
            Node<T>* newParent = _node->getLeft();
            insertNodeUp(_node, newParent);
            _node->setLeft(newParent->getRigth());
            if(newParent->getRigth() != NULL) newParent->getRigth()->setParent(_node);
            newParent->setRight(_node);
        }

        void insertFixUp(Node<T>* _node){
            if(_node == root){
                _node->setColor(BLACK);
                return;
            }

            Node<T>* parent = _node->getParent();
            Node<T>* grandparent = parent->getParent();
            Node<T>* uncle = getUncle(_node);

            if(parent->getColor() == RED){
                if(uncle != NULL && uncle->getColor() == RED){
                    grandparent->setColor(RED);
                    parent->setColor(BLACK);
                    uncle->setColor(BLACK);
                    insertFixUp(grandparent);
                }
                else{
                    if(isLeftChild(parent)){
                        if(isLeftChild(_node))
                            swapColors(parent, grandparent);
                        else{
                            leftRotate(parent);
                            swapColors(_node, grandparent);
                        }
                        rightRotate(grandparent);
                    }
                    else{
                        if(isLeftChild(_node)){
                            rightRotate(parent);
                            swapColors(_node, grandparent);
                        }
                        else
                            swapColors(parent, grandparent);
                        leftRotate(grandparent);
                    }
                }
            }
        }

        void printPreOrder(Node<T>* _node, bool _printNIL, ofstream &out){
            if(_node == NULL){ 
                if(_printNIL) out << "(NIL) ";
                return;
            }
            out << "(" << _node->getKey() << " " << _node->getColor() << ") ";
            printPreOrder(_node->getLeft(), _printNIL, out);
            printPreOrder(_node->getRigth(), _printNIL, out);
        }

        void printInOrder(Node<T>* _node, bool _printNIL, ofstream &out){
            if(_node == NULL){ 
                if(_printNIL) out << "(NIL) ";
                return;
            }
            printInOrder(_node->getLeft(), _printNIL, out);
            out << "(" << _node->getKey() << " " << _node->getColor() << ") ";
            printInOrder(_node->getRigth(), _printNIL, out);
        }

        void printPostOrder(Node<T>* _node, bool _printNIL, ofstream &out){
            if(_node == NULL){ 
                if(_printNIL) out << "(NIL) ";
                return;
            }
            printPostOrder(_node->getLeft(), _printNIL, out);
            printPostOrder(_node->getRigth(), _printNIL, out);
            out << "(" << _node->getKey() << " " << _node->getColor() << ") ";
        }
    
    public:
        RBT() : root(NULL) {}

        RBT<T>* insertKey(T _key){
            Node<T>* newNode = new Node<T>(_key, RED);
            if(root == NULL) root = newNode;
            else{
                Node<T>* tmp = search(_key);
                if(compare(_key, tmp->getKey()) == 0) return this;
                newNode->setParent(tmp);
                if(compare(_key, tmp->getKey()) > 0) tmp->setRight(newNode);
                else tmp->setLeft(newNode);
            }
            insertFixUp(newNode);
            return this;
        }

        void print(string _print_type, bool _printNIL, ofstream &out){
            if(_print_type == "preorder") printPreOrder(root, _printNIL, out);
            else if(_print_type == "postorder") printPostOrder(root, _printNIL, out);
            else if(_print_type == "inorder") printInOrder(root, _printNIL, out);
        }
};