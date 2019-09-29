#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include "node.h"

template <typename T> 
class Iterator {
    private:
        Node<T> *current;
        stack<Node<T>*> pp;

    public:
        Iterator() {
            current = nullptr;
        }

        explicit Iterator(Node<T> *node) {
            current = node;
        }

        Iterator<T>& operator=(const Iterator<T> &other) {
            // Estás creando un nuevo iterador
            current = Iterator<T>(other.current);
            return *this;
        }

        bool operator!=(Iterator<T> other) {
            return current->data != other.current->data;
        }

        void setstackpp(Node<T>* theRoot){
            pp.push(theRoot);
            while(theRoot->left){
                theRoot = theRoot->left;
                pp.push(theRoot);
            }
            pp.pop();
        }

        Iterator<T>& operator++() {
            auto* aux = current;
            if (aux->right){
                aux = aux->right;
                pp.push(aux);
                while (aux->left){
                    aux = aux->left;
                    pp.push(aux);
                }
            }
            current = pp.top();
            pp.pop();
            return *this;
        }

        Iterator<T>& operator--() {

        }

        T operator*() {
            // Caso de null?
            return current->data;
        }
};

#endif
