//
// Created by tianq on 24-11-27.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <bits/ranges_algo.h>
using namespace std;

double PickMedian(vector<int> arr) {
    return ranges::sort(arr)[arr.size() / 2];
}

double PickBFPRT(vector<int> arr) {
    int size = arr.size();
    vector<int> temp(size);

}