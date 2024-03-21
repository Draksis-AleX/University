#include <iostream>
#include <fstream>
using namespace std;

#define BLACK 'B'
#define RED 'R'
#define PREORDER 0
#define INORDER 1
#define POSTORDER 2

template <class T> class Node{
    private:
        T key;
        char color;
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;
    public:
        Node(T _key, char _color) : key(_key), color(_color){ parent = left = right = NULL; }

        T getKey(){return key;}
        char getColor(){return color;}
        Node<T>* getParent(){return parent;}
        Node<T>* getLeft(){return left;}
        Node<T>* getRight(){return right;}
        bool isBlack(){return color == BLACK;}

        void setKey(T _key){key = _key;}
        void setColor(char _color){color = _color;}
        void setParent(Node<T>* _parent){parent = _parent;}
        void setLeft(Node<T>* _left){left = _left;}
        void setRight(Node<T>* _right){right = _right;}
};

template <class T> class RBT{
    private:
        Node<T>* root;

        double compare(T _a, T _b){return (double)_a - (double)_b;}

        Node<T>* search(T _key){
            Node<T>* iter = root;
            while (iter != NULL && compare(iter->getKey(), _key) != 0)
            {
                if(compare(_key, iter->getKey()) > 0){
                    if(iter->getRight() != NULL) iter = iter->getRight();
                    else break;
                }
                else{
                    if(iter->getLeft() != NULL) iter = iter->getLeft();
                    else break;
                }
            }
            return iter;
        }

        bool isLeftChild(Node<T>* _node){return _node == _node->getParent()->getLeft();}

        Node<T>* getUncle(Node<T>* _node){
            if(_node->getParent() == NULL || _node->getParent()->getParent() == NULL) return NULL;

            if(isLeftChild(_node->getParent())) return _node->getParent()->getParent()->getRight();
            else return _node->getParent()->getParent()->getLeft();
        }

        void swapColors(Node<T>* _node1, Node<T>* _node2){
            char tmp = _node1->getColor();
            _node1->setColor(_node2->getColor());
            _node2->setColor(tmp);
        }

        void insertNodeUp(Node<T>* _parent, Node<T>* _newParent){
            if(_parent->getParent() != NULL){
                if(isLeftChild(_parent)) _parent->getParent()->setLeft(_newParent);
                else _parent->getParent()->setRight(_newParent);
            }
            else root = _newParent;
            _newParent->setParent(_parent->getParent());
            _parent->setParent(_newParent);
        }

        void leftRotate(Node<T>* _node){
            Node<T>* newParent = _node->getRight();
            insertNodeUp(_node, newParent);
            _node->setRight(newParent->getLeft());
            if(newParent->getLeft() != NULL) newParent->getLeft()->setParent(_node);
            newParent->setLeft(_node);
        }

        void rightRotate(Node<T>* _node){
            Node<T>* newParent = _node->getLeft();
            insertNodeUp(_node, newParent);
            _node->setLeft(newParent->getRight());
            if(newParent->getRight() != NULL) newParent->getRight()->setParent(_node);
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
                        if(isLeftChild(_node)){
                            swapColors(parent, grandparent);
                        }
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
                        else{
                            swapColors(parent, grandparent);
                        }
                        leftRotate(grandparent);
                    }
                }
            }
        }
    
        void printPreOrder(Node<T>* _node, bool _printNIL, ofstream &_out){
            if(_node == NULL){
                if(_printNIL) _out << "(NIL) ";
                return;
            }
            _out << "(" << _node->getKey() << " " << _node->getColor() << ") ";
            printPreOrder(_node->getLeft(), _printNIL, _out);
            printPreOrder(_node->getRight(), _printNIL, _out);
        }

        void printInOrder(Node<T>* _node, bool _printNIL, ofstream &_out){
            if(_node == NULL){
                if(_printNIL) _out << "(NIL) ";
                return;
            }
            printInOrder(_node->getLeft(), _printNIL, _out);
            _out << "(" << _node->getKey() << " " << _node->getColor() << ") ";
            printInOrder(_node->getRight(), _printNIL, _out);
        }

        void printPostOrder(Node<T>* _node, bool _printNIL, ofstream &_out){
            if(_node == NULL){
                if(_printNIL) _out << "(NIL) ";
                return;
            }
            printPostOrder(_node->getLeft(), _printNIL, _out);
            printPostOrder(_node->getRight(), _printNIL, _out);
            _out << "(" << _node->getKey() << " " << _node->getColor() << ") ";
        }

        int height(Node<T>* _node){
            if(_node == NULL) return 0;
            int sx = height(_node->getLeft());
            int dx = height(_node->getRight());

            return 1 + max(sx, dx);
        }

        int BlackHeight(Node<T>* _node) { 
            if (_node == NULL)    
                return 1;     
            int leftBlackHeight = BlackHeight(_node->getLeft()); 
            if (leftBlackHeight == 0) 
                return 0;
            int rightBlackHeight = BlackHeight(_node->getRight()); 
            if (rightBlackHeight == 0) 
                return 0;
            return leftBlackHeight + _node->isBlack(); 
        } 

    public:
        RBT() : root(NULL) {}

        RBT<T>* insertKey(T _key){
            Node<T>* newNode = new Node<T>(_key, RED);

            if(root == NULL) root = newNode;
            else{
                Node<T>* tmp = search(_key);
                if(compare(_key, tmp->getKey()) == 0) return this;

                if(compare(_key, tmp->getKey()) > 0) tmp->setRight(newNode);
                else tmp->setLeft(newNode);
                newNode->setParent(tmp);
            }
            insertFixUp(newNode);
            return this;
        }

        void print(int _printType, bool _printNIL, ofstream &_out){
            if(_printType == PREORDER) printPreOrder(root, _printNIL, _out);
            else if(_printType == INORDER) printInOrder(root, _printNIL, _out);
            else if(_printType == POSTORDER) printPostOrder(root, _printNIL, _out);
        }

        int getHeight(){
            return height(root);
        }

        int getBlackHeight(){
            return BlackHeight(root);
        }
};