#ifndef PROJECT518_LINKEDLIST_H
#define PROJECT518_LINKEDLIST_H

template <typename T>
struct Node {
public:
    T data;
    Node *next;
};

template <typename T>
class LinkedList {
    Node<T> *head, *tail;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    void push_back(T el) {
        auto *n = new Node<T>;
        n->data = el;
        n->next = NULL;
        if (head == NULL) {
            head = n;
            tail = n;
            n = NULL;
        } else {
            tail->next = n;
            tail = n;
        }
    }
};


#endif //PROJECT518_LINKEDLIST_H
