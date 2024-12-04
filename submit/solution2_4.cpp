//
// Created by tianq on 24-11-29.
//
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    cout.precision(4);
    int N = 0;
    vector<int> arr;

    cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }

    unordered_map<int, int> map;
    for (const int &i: arr) {
        if (!map.contains(i))
            map[i] = 1;
        else
            map[i] = map[i] + 1;
    }
    int modeValue = 0, modeCount = 0;
    for (const auto &[fst, snd]: map) {
        if (snd <= modeCount) continue;
        modeCount = snd;
        modeValue = fst;
    }

    cout << modeValue << endl;
    return 0;
}
