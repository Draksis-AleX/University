#include <iostream>
#include <fstream>
using namespace std;

template <class T> class Node{
    private:
        T key;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
    public:
        Node(T _key) : key(_key) {parent = left = right = NULL;}

        Node<T>* getLeft(){return left;}
        Node<T>* getRight(){return right;}
        Node<T>* getParent(){return parent;}
        T getKey(){return key;}

        void setLeft(Node<T>* _left){left = _left;}
        void setRight(Node<T>* _right){right = _right;}
        void setParent(Node<T>* _parent){parent = _parent;}
        void setKey(T _key){key = _key;}
};

template <class T> class BST{
    private:
        Node<T>* root;

        Node<T>* search(T _key){
            Node<T>* iter = root;
            while (iter != NULL && _key != iter->getKey())
            {
                if(_key > iter->getKey()) iter = iter->getRight();
                else iter = iter->getLeft();
            }
            return iter;
        }

        bool isLeftChild(Node<T>* _node){return _node == _node->getParent()->getLeft();}

        void insertNodeUp(Node<T>* parent, Node<T>* newParent){
            if(parent->getParent() == NULL) root = newParent;
            else if(isLeftChild(parent)) parent->getParent()->setLeft(newParent);
            else parent->getParent()->setRight(newParent);

            newParent->setParent(parent->getParent());
            parent->setParent(newParent);
        }

        void rotateLeft(Node<T>* _node){
            if(_node == NULL || _node->getRight() == NULL) return;

            Node<T>* newParent = _node->getRight();
            insertNodeUp(_node, newParent);
            _node->setRight(newParent->getLeft());
            if(newParent->getLeft() != NULL) newParent->getLeft()->setParent(_node);
            newParent->setLeft(_node);
        }

        void rotateRight(Node<T>* _node){
            if(_node == NULL || _node->getLeft() == NULL) return;
            
            Node<T>* newParent = _node->getLeft();
            insertNodeUp(_node, newParent);
            _node->setLeft(newParent->getRight());
            if(newParent->getRight() != NULL) newParent->getRight()->setParent(_node);
            newParent->setRight(_node);
        }

        void printPreOrder(Node<T>* _node, ofstream &out){
            if(_node == NULL) return;

            out << _node->getKey() << " ";
            printPreOrder(_node->getLeft(), out);
            printPreOrder(_node->getRight(), out);
        }

        void printPostOrder(Node<T>* _node, ofstream &out){
            if(_node == NULL) return;

            printPostOrder(_node->getLeft(), out);
            printPostOrder(_node->getRight(), out);
            out << _node->getKey() << " ";
        }

        void printInOrder(Node<T>* _node, ofstream &out){
            if(_node == NULL) return;

            printInOrder(_node->getLeft(), out);
            out << _node->getKey() << " ";
            printInOrder(_node->getRight(), out);
        }

    public:
        BST<T>* addNode(T _key){
            if(search(_key) != NULL) return this;

            Node<T>* newNode = new Node<T>(_key);
            if(root == NULL){
                root = newNode;
                return this;
            }

            Node<T>* iter = root;
            Node<T>* tmp = NULL;
            while (iter != NULL)
            {
                tmp = iter;
                if(_key > iter->getKey()) iter = iter->getRight();
                else iter = iter->getLeft();
            }

            newNode->setParent(tmp);
            if(_key > tmp->getKey()) tmp->setRight(newNode);
            else tmp->setLeft(newNode);
            
            return this;
        }

        Node<T>* findMin(Node<T>* _node){
            Node<T>* iter = _node;
            while (iter->getLeft() != NULL)
                iter = iter->getLeft();
            return iter;
        }

        BST<T>* deleteNode(T _key){
            Node<T>* node = search(_key);
            if(node == NULL) return this;

            if(node->getLeft() == NULL) insertNodeUp(node, node->getRight());
            else if(node->getRight() == NULL) insertNodeUp(node, node->getLeft());
            else{
                T sucKey = findMin(node->getRight())->getKey();
                deleteNode(sucKey);
                node->setKey(sucKey);
            }
            return this;
        }

        void rotateLeft(T _key){
            Node<T>* _node = search(_key);
            if(_node == NULL) return;

            rotateLeft(_node);
        }

        void rotateRight(T _key){
            Node<T>* _node = search(_key);
            if(_node == NULL) return;

            rotateRight(_node);
        }

        void print(string type, ofstream &out){
            cout << "Print Type = " << type << " : ";
            if(type == "preorder") printPreOrder(root, out);
            else if(type == "inorder") printInOrder(root, out);
            else if(type == "postorder") printPostOrder(root, out);
        }
};