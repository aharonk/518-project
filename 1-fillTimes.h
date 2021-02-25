#ifndef PROJECT518_FILLTIMES_H
#define PROJECT518_FILLTIMES_H

#include "LinkedList.h"
#include "Vector.h"

template <typename T>
int fasterFill(T randEls[], int len) {
    int beginTime, vectTime;

    auto *v = new Vector<T>(len);
    beginTime = clock();
    for (int j = 0; j < len; ++j) {
        v->push_back(randEls[j]);
    }
    delete v;
    vectTime = clock() - beginTime;

    LinkedList<T> l;
    beginTime = clock();
    for (int j = 0; j < len; ++j) {
        l.push_back(randEls[j]);
    }

    return (clock() - beginTime) - vectTime;
}

#endif //PROJECT518_FILLTIMES_H
