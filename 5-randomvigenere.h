#ifndef PROJECT518_NAIVEVIGENERE_H
#define PROJECT518_NAIVEVIGENERE_H

#include <map>
#include <algorithm>
#include <vector>

std::string text;
double englishFrequencies[] = {.082, .015, .028, .043, .13, .022, .02, .061, .07, .0015, .0077, .04, .024, .067, .075,
                               .019,
                               .00095, .06, .063, .091, .028, .0098, .024, .0015, .02, .00074};

double totaldeviation(std::vector<char> key) {
    std::array<double, 26> keyFrequencies{};
    //find the frequency of each letter using the current key
    for (int i = 0; i < text.length(); ++i) {
        keyFrequencies[(tolower(text[i]) - 'a' + 26 - (key[i % key.size()] - 'a')) % 26] += 1.0 / text.length();
    }

    double deviation = 0;
    //return the frequency difference between this text and english
    for (int i = 0; i < keyFrequencies.size(); ++i) {
        deviation += abs(keyFrequencies[i] - englishFrequencies[i]);
    }

    return deviation;
}


void decode(std::string *msg, const int KEY_LEN = 32, const double TOTAL_DEVIATION_THRESHOLD = 1) {
    text = *msg;
    if (text.length() < 1 || KEY_LEN < 1) {
        throw std::invalid_argument("Invalid param.");
    }

    srand(time(nullptr));
    const int NUM_TRIES = 1000000;
    double deviation;
    std::map<std::vector<char>, double> possibleKeys;

    for (int i = 0; i < NUM_TRIES; ++i) {
        std::vector<char> currKey(KEY_LEN);
        //create a random key
        for (char &c : currKey) {
            c = (char) (rand() % 26 + 'a');
        }

        //get the difference in letter frequencies between this message decoded using the key and english
        deviation = totaldeviation(currKey);

        if (deviation < TOTAL_DEVIATION_THRESHOLD) {
            possibleKeys.emplace(currKey, deviation);
        }
    }

    if (possibleKeys.empty()) {
        std::cout << "No possibilities found, try a higher threshold.";
        std::exit(0);
    }

    std::map<std::vector<char>, double>::iterator it;
    for (it = possibleKeys.begin(); it != possibleKeys.end(); it++) {
        for (int i = 0; i < std::max<unsigned int>(NUM_TRIES / possibleKeys.size(), 1); ++i) {

            std::vector<char> newKey(it->first);
            bool same = true;
            //possibly mutate the key
            for (int j = 0; j < KEY_LEN; ++j) {
                if (rand() % 100 <= 4) newKey[j] = rand() % 26 + 'a';
                if (same) same = newKey[j] == it->first[j];
            }

            if (!same) {
                //then add it as a possibility if it's an improvement;
                deviation = totaldeviation(newKey);
                if (deviation < it->second) {
                    possibleKeys.emplace(newKey, deviation);
                }
            }
        }
    }

    //narrow possibilities
    std::map<std::vector<char>, double> probableKeys;
    for (it = possibleKeys.begin(); it != possibleKeys.end(); it++) {
        if (it->second < TOTAL_DEVIATION_THRESHOLD / 2) {
            probableKeys.emplace(*it);
        }
    }

    if (probableKeys.empty()) {
        std::cout << "No probabilities found, try a higher threshold.";
        std::exit(0);
    }

    //recombine
    for (int i = 0; i < NUM_TRIES; ++i) {
        //two random keys
        it = probableKeys.begin();
        std::advance(it, rand() % probableKeys.size());
        std::pair<std::vector<char>, double> pair1 = *it;
        it = probableKeys.begin();
        std::advance(it, rand() % probableKeys.size());
        std::pair<std::vector<char>, double> pair2 = *it;

        std::vector<char> newKey;
        //randomly copy elements from the two keys into a new key
        for (int j = 0; j < KEY_LEN; ++j) {
            newKey.push_back((rand() % 100 < 50) ? pair1.first[j] : pair2.first[j]);
        }

        deviation = totaldeviation(newKey);
        //add to probabilities if it's an improvement
        if (deviation < std::min(pair1.second, pair2.second)) {
            probableKeys.emplace(newKey, deviation);
        }
    }

    //print keys sorted by probability
    std::vector<std::pair<std::vector<char>, double>> vMap;
    for (it = probableKeys.begin(); it != probableKeys.end(); it++) {
        vMap.emplace_back(*it);
    }

    std::sort(vMap.begin(), vMap.end(), []
            (std::pair<std::vector<char>, double> &p1, std::pair<std::vector<char>, double> &p2) {
        return p1.second < p2.second;
    });

    std::vector<std::pair<std::vector<char>, double>>::iterator alsoIt;
    for (alsoIt = vMap.begin(); alsoIt != vMap.end(); alsoIt++) {
        for (char c : alsoIt->first) {
            std::cout << c;
        }
        std::cout << std::endl;

        for (int i = 0; i < text.length(); ++i) {
            std::cout << (char) (((tolower(text[i]) - 'a') + 26 - (alsoIt->first[i % KEY_LEN] - 'a')) % 26 + 'a');
        }
        std::cout << std::endl;
    }
}

#endif //PROJECT518_NAIVEVIGENERE_H
