#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template <typename T> 
class BSTree {
    Node<T> *root;

    public:
        BSTree() : root(nullptr) {};

        bool find(T data) {
            auto* aux = root;
            size_t tall = height();
            for (size_t i = 0; i < tall; ++i) {
                if (data == aux->data){
                    return true;
                }
                else if (data > aux->data && aux->right){
                    aux = aux->right;
                } else if (data < aux->data && aux->left){
                    aux = aux->left;
                } else return false;
            }
            return false;
        }

        bool insert(T data) {
            auto* ans = new Node<T>;
            ans->data = data;
            if (root == nullptr){
                root = ans;
            } else {
                auto* aux = root;
                while (true) {
                    if (data <= aux->data) {
                        if (aux->left) {
                            aux = aux->left;
                        } else {
                            aux->left = ans;
                            return true;
                        }
                    } else {
                        if (aux->right) {
                            aux = aux->right;
                        } else {
                            aux->right = ans;
                            return true;
                        }
                    }
                }
            }
        }
        bool remove(T data) {
            if (!find(data)) return false;
            else {
                auto *x = root;
                Node<T> *xfather;
                while (true) {
                    if (x->data == data) break;
                    else if (x->data > data) {
                        xfather = x;
                        x = x->left;
                    } else {
                        xfather = x;
                        x = x->right;
                    }
                }
                if (!x->left) {
                    if (!x->right) {
                        if (x != root) {
                            if (xfather->left == x) xfather->left = nullptr;
                            else xfather->right = nullptr;
                        } else root = nullptr;
                    } else {
                        if (x != root) {
                            if (xfather->left == x) xfather->left = x->right;
                            else xfather->right = x->right;
                        } else root = x->right;
                    }
                } else {
                    if (!x->right) {
                        if (x != root) {
                            if (xfather->left == x) xfather->left = x->left;
                            else xfather->right = x->left;
                        } else root = x->left;
                    } else {
                        auto* y = x->right;
                        auto* yfather = x;
                        while (y->left) {
                            yfather = y;
                            y = y->left;
                        }
                        if (x == yfather){
                            if (y->right) yfather->right = y->right;
                            else yfather->right = nullptr;
                        }else {
                            if (y->right) yfather->left = y->right;
                            else yfather->left = nullptr;
                        }
                        if (x != root) {
                            if (xfather->left == x) xfather->left = y;
                            else xfather->right = y;
                        } else {
                            root = y;
                        }
                        y->right = x->right;
                        y->left = x->left;
                    }
                }
                x->right = nullptr;
                x->left = nullptr;
                delete x;
            }
            return true;
        }

        size_t getSizeFromNode(Node<T>* pos){
            if(!pos->left) {
                if (!pos->right) {
                    return 1;
                } else {
                    return getSizeFromNode(pos->right)+1;
                }
            } else if (!pos->right) {
                return getSizeFromNode(pos->left)+1;
            } else {
                return 1 + getSizeFromNode(pos->left) + getSizeFromNode(pos->right);
            }
        }

        size_t size() {
            if(!root) return 0;
            else return getSizeFromNode(root);
        }

        size_t getNodeHeight(Node<T>* pos) {
            if(!pos->left) {
                if (!pos->right) {
                    return 1;
                } else {
                    return getNodeHeight(pos->right)+1;
                }
            }else if (!pos->right) {
                return getNodeHeight(pos->left)+1;
            } else {
                return max(1 + getNodeHeight(pos->left), 1 + getNodeHeight(pos->right));
            }

        }

        size_t height() {
            if (!root) return 0;
            else return getNodeHeight(root);
        }

        void recTPreO(Node<T>* pos){
            if (pos->left) recTInO(pos->left);
            cout << pos->data << " ";
            if (pos->right) recTInO(pos->right);
        }

        void traversePreOrder() {
            if (root) recTPreO(root);
        }

        void recTInO(Node<T>* pos){
            if (pos->left) recTInO(pos->left);
            cout << pos->data << " ";
            if (pos->right) recTInO(pos->right);
        }

        void traverseInOrder() {
            if (root) recTInO(root);
        }

        void recTPosO(Node<T>* pos){
            if (pos->left) recTInO(pos->left);
            if (pos->right) recTInO(pos->right);
            cout << pos->data << " ";
        }

        void traversePostOrder() {
            if (root) recTPosO(root);
        }

        Iterator<T> begin() {
            auto* aux = root;
            while (aux->left){
                aux = aux->left;
            }
            Iterator<T> x(aux);
            x.setstackpp(root);
            return x;
        }

        Iterator<T> end() {
            auto* aux = root;
            while (aux->right){
                aux = aux->right;
            }
            aux->right = new Node<T>;
            aux = aux->right;
            return Iterator<T>(aux);
        }

        void destroyUnder(Node<T>* head){
            if (head->left){
                destroyUnder(head->left);
            }
            if (head->right){
                destroyUnder(head->right);
            }
            delete(head);
        }

        ~BSTree() {
            destroyUnder(root);
        }
};

#endif
