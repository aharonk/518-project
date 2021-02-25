//
// Created by askatz on 2/15/2021.
//

#ifndef PROJECT518_MATRIXSORT_H
#define PROJECT518_MATRIXSORT_H

#include <array>

template <typename T>
void swap(T *x, T *y) {
    T temp = *x;
    *x = *y;
    *y = temp;
}

template <typename T>
void bubbleSort(T **matrix, int size) {
    T *lastEl;
    bool sorted;
    while (true) {
        sorted = true;
        //cannot do single for loop j < size * size, because there is overhead in between the separate subarrays.
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                if (j != 0 || k != 0) {
                    //swap every two if out of order
                    lastEl = (k - 1 < 0) ? &matrix[j - 1][size - 1] : &matrix[j][k - 1];
                    if (*lastEl > matrix[j][k]) {
                        swap(lastEl, &matrix[j][k]);
                        sorted = false;
                    }
                }
            }
        }
        if (sorted) {
            break;
        }
    }
}

template <typename T>
void insertionSort(T **matrix, int size) {
    T curr;
    int kx, ky;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != 0 || j != 0) {
                curr = matrix[i][j];
                if (j - 1 < 0) {
                    kx = i - 1;
                    ky = size - 1;
                } else {
                    kx = i;
                    ky = j - 1;
                }
                //while smaller than preceding, switch them
                while ((kx >= 0 && ky >= 0) && matrix[kx][ky] > curr) {
                    if (ky + 1 >= size) {
                        matrix[kx + 1][0] = matrix[kx][ky];
                    } else {
                        matrix[kx][ky + 1] = matrix[kx][ky];
                    }

                    if (ky - 1 < 0) {
                        kx--;
                        ky = size - 1;
                    } else {
                        ky--;
                    }
                }
                if (ky + 1 >= size) {
                    matrix[kx + 1][0] = curr;
                } else {
                    matrix[kx][ky + 1] = curr;
                }
            }
        }
    }
}

template <typename T>
void selectionSort(T **matrix, int size) {
    T *min;
    int walkx, walky;
    for (int i = 0, nextx = 0; i < size; ++i) {
        for (int j = 0, nexty = 0; j < size; ++j) {
            nexty++;
            min = &matrix[i][j];
            if (nexty >= size) {
                nextx++;
                nexty = 0;
            }
            walkx = nextx;
            walky = nexty;

            while (walkx < size) {
                while (walky < size) {
                    if (walkx >= size) break;
                    if (matrix[walkx][walky] < *min) {
                        min = &matrix[walkx][walky];
                    }
                    walky++;
                    if (walky >= size) {
                        walkx++;
                        walky = 0;
                    }
                }
            }
            swap(min, &matrix[i][j]);
        }
    }
}


#endif //PROJECT518_MATRIXSORT_H
