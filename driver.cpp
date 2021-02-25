#include <iostream>
#include <vector>
#include "fillTimes.h"
#include "MatrixSort.h"
#include "naivevigenere.h"

void fillTimes() {
    srand(time(nullptr));

    const int RUNS = 10000;
    int total = 0;
    for (int i = 1; i < RUNS; ++i) {
        int *randNums = new int[i];

        for (int j = 0; j < i; ++j) {
            randNums[j] = rand();
        }

        total += fasterFill(randNums, i);
        delete[] randNums;
    }
    printf("After %d runs, an int %s is faster by %ld seconds, an average of %d ticks.\n",
           RUNS, ((total >= 0) ? "List" : "Vector"), total / CLOCKS_PER_SEC, total / RUNS);

    total = 0;
    std::string s;
    for (int i = 1; i < RUNS; ++i) {
        auto *randStrs = new std::string[i];

        for (int j = 0; j < i; ++j) {
            int len = rand() % 8 + 1;
            s.resize(len);
            for (int k = 0; k < len; ++k) {
                //ascii printables are 32 - 127
                s[k] = rand() % 96 + 32;
            }
            randStrs[j] = s;
        }

        total += fasterFill(randStrs, i);
        delete[] randStrs;
    }

    printf("After %d runs, an string %s is faster by %ld seconds, an average of %d ticks.\n",
           RUNS, ((total >= 0) ? "List" : "Vector"), abs(total) / CLOCKS_PER_SEC, abs(total) / RUNS);
}

void sorts() {
    srand(time(nullptr));
    const int SIZE = 10;
    int *randNums1[SIZE], *randNums2[SIZE], *randNums3[SIZE];
    for (int i = 0; i < SIZE; i++) {
        randNums1[i] = new int[SIZE];
        randNums2[i] = new int[SIZE];
        randNums3[i] = new int[SIZE];
    }

    int r;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; ++j) {
            r = rand();
            randNums1[i][j] = r;
            randNums2[i][j] = r;
            randNums3[i][j] = r;
        }
    }

    bubbleSort(randNums1, SIZE);
    insertionSort(randNums2, SIZE);
    selectionSort(randNums3, SIZE);

    bool wrong = false;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (randNums1[i][j] != randNums2[i][j] || randNums1[i][j] != randNums3[i][j] ||
                randNums2[i][j] != randNums3[i][j]) {
                printf("1: %d, 2: %d, 3: %d\n", randNums1[i][j], randNums2[i][j], randNums3[i][j]);
                wrong = true;
            }
        }
    }
    if (!wrong) std::cout << "All sorted.";
}

void vigenere() {
    std::string s = "adevydfdeuwyfbxsxjmceddajtgmdtpegpbdsoqhwmexkdikrjizhpvleykjlcpezoibkyderepnjdrodxcnhhvbxqgfdeezxl"
                    "mgoodhwmexkdioatwbzmlvsdgtjnfeqsbrgcrghiifjkryqqcasalbmmujwgppscwiupbzuarjjomdhfmnslvxhupwdhezhoqo"
                    "ckqskuanepibzkxydwdqhigxpfbgwbgonslfeujtiaychjbuourbxupwqgczjocncouduueqccssylxcclfbjajupxbyooezxo"
                    "ykowsnechscjwneohwjtghlcvtfcpjxdrghfiwzkhglxmiqhutywgjwgmcwcmizzcqlehyywxczryiqpwadakixgpesebcubgs"
                    "luwneomcejxiypwarqkdvtbnwsdzjpmqjesifnjycjpcwpqbxqukegowsdqqkncfuuitwyswaflcdvqwdxa";
    decode(&s, 32, 1);
}

int main() {
    fillTimes();
}
