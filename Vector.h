//
// Created by askat on 2/23/2021.
//

#ifndef PROJECT518_VECTOR_H
#define PROJECT518_VECTOR_H

template<typename T>
class Vector {
    int insertionPoint;
    T *store;

public:
    explicit Vector(int len) {
        insertionPoint = 0;
        store = new T[len];
    }

    void push_back(T el) {
        store[insertionPoint] = el;
        insertionPoint++;
    }

    ~Vector() {
        delete[] store;
    }

    T get(int i) {
        return store[i];
    }
};


#endif //PROJECT518_VECTOR_H
