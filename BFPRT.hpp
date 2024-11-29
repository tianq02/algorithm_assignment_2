//
// Created by tianq on 24-11-27.
//
#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

#include <random>  // 为了在PCG算法中使用C11风格的 random device 安全初始化
#include "pcg_random.hpp"  // 非常优秀的现代伪随机生成器
using namespace std;

constexpr int groupSize = 5;

/**
 * get nth element in given array.
 * brute forced, for comparison purpose
 * @param arr the array you want to determine its nth element
 * @param N [0,arr.size()-1], return nth smallest
 * @return nth smallest element
 */
inline double BruteNth(vector<double> &arr, const unsigned long long N) {
    ranges::sort(arr);
    return arr[N];
}

/**
 * pick median of given array
 * @param arr the array to be parsed
 * @return median of given array, when arr size is odd, bigger one is chosen
 * @attention not a mathematical median,
 */
inline double BruteMedian(vector<double> arr) {
    ranges::sort(arr);
    return arr[arr.size() / 2];
}

/**
 * pick first element from vector
 * @param arr the array to be parsed
 * @return first element from array
 */
inline double PickFirst(const vector<double> &arr) {
    return arr[0];
}

/**
 * pick a random element from vector
 * @param arr the array to be parsed
 * @return random element from array
 */
inline double PickRandom(const vector<double> &arr) {
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    pcg32 rng(seed_source);
    uniform_int_distribution<> dist(0, static_cast<int>(arr.size() - 1));
    return arr[dist(rng)];
}

/**
 * pick a likely median element from vector,used by BFPRT
 * @param arr the array to be parsed
 * @return element from array
 */
inline double PickBfprt(const vector<double> &arr) {
    if (arr.size() <= 5) return BruteMedian(arr);

    auto it = arr.begin();
    vector<double> medians;
    while (it != arr.end()) {
        vector<double> group;
        while (group.size() < groupSize && it != arr.end()) {
            group.push_back(*it);
            ++it;
        }
        medians.push_back(BruteMedian(group));
    }

    return PickBfprt(medians);
}

/**
 * get nth element in given array
 * @param arr the array you want to determine its nth element
 * @param targetIndex [0,arr.size()-1], return nth smallest
 * @param PickPivot Pivot Picking strategy, PickRandom should be good enough
 * @return nth smallest element
 */
inline double QuickSelect(vector<double> arr, const unsigned long long targetIndex, double (*PickPivot)(const vector<double>&) = PickBfprt) {
    // cout << endl << "targetIndex" << targetIndex << endl;
    // for (const auto &num: arr) cout << num << ", ";
    // cout << endl;

    if (arr.size() == 1) return arr.front();

    const double pivot = PickPivot(arr);
    // cout << "pivot: " << pivot << endl;

    vector<double> left, mid, right;
    for (double &num: arr) {
        if (num < pivot) left.push_back(num);
        else if (num > pivot) right.push_back(num);
        else mid.push_back(num);
    }

    if (targetIndex < left.size()) {
        return QuickSelect(left, targetIndex, PickPivot);
    } else if (targetIndex < left.size() + mid.size()) {
        return mid.front();
    } else {
        return QuickSelect(right, targetIndex - left.size() - mid.size(), PickPivot);
    }
}

/*
int main() {
    cout.precision(4);
    // PCG RNG magic, see https://www.pcg-random.org/using-pcg-cpp.htm
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    pcg32 rng(seed_source);
    uniform_real_distribution<> uniform_dist(1, 100);

    vector<double> arr;
    for (int i = 0; i < 10; i++) {
        arr.push_back(uniform_dist(rng));
        cout << arr[i] << ", ";
    }
    cout << endl;

    // cout << PickRandom(arr) << endl;
    // cout << PickFirst(arr) << endl;
    // cout << PickBfprt(arr) << endl;
    // cout << BruteMedian(arr) << endl;
    cout << "BFPRT:\t" << QuickSelect(arr, 5, PickBfprt) << endl;
    cout << "First:\t" << QuickSelect(arr, 5, PickFirst) << endl;
    cout << "Random:\t" << QuickSelect(arr, 5, PickRandom) << endl;
    cout << "Brute:\t" << BruteNth(arr, 5) << endl;

    ranges::sort(arr);
    for (const auto &num: arr) cout << num << ", ";
}
*/
