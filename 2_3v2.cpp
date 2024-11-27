//
// Created by tianq on 24-11-27.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include <random>  // 为了在PCG算法中使用C11风格的 random device 安全初始化
#include "pcg_random.hpp"  // 非常优秀的现代伪随机生成器
using namespace std;

constexpr int groupSize = 5;

/**
 * pick median of given array
 * @param arr the array to be parsed
 * @return median of given array, when arr size is odd, bigger one is chosen
 */
double BruteMedian(vector<double> arr) {
    ranges::sort(arr);
    return arr[arr.size() / 2];
}

/**
 * pick first element from vector
 * @param arr the array to be parsed
 * @return first element from array
 */
double PickFirst(vector<double> arr) {
    return arr.front();
}

/**
 * pick a random element from vector
 * @param arr the array to be parsed
 * @return random element from array
 */
double PickRandom(vector<double> arr) {
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    pcg32 rng(seed_source);
    uniform_int_distribution<> dist(0, arr.size() - 1);
    return arr[dist(rng)];
}

/**
 * pick a likely median element from vector,used by BFPRT
 * @param arr the array to be parsed
 * @return element from array
 */
double PickBfprt(vector<double> arr) {
    if (arr.size() == 1) return arr[0];
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
 *
 * @param arr
 * @param targetIndex
 * @param PickPivot
 * @return
 */
double QuickSelect(vector<double> arr, int targetIndex, auto PickPivot = PickFirst) {

    // cout << endl << "targetIndex" << targetIndex << endl;
    // for (const auto &num: arr) cout << num << ", ";
    // cout << endl;

    if (arr.size() == 1) return arr.front();

    const double pivot = PickPivot(arr);
    // cout << "pivot: " << pivot << endl;

    vector<double> left, right;
    for (double &num: arr) {
        if (num < pivot) left.push_back(num);
        else right.push_back(num);
    }

    if (left.size() >= targetIndex) {
        // 目标在左半
        return QuickSelect(left, targetIndex, PickPivot);
    } else {
        return QuickSelect(right, targetIndex - left.size(), PickPivot);
    }
}

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

    cout << PickRandom(arr) << endl;
    cout << BruteMedian(arr) << endl;
    cout << PickBfprt(arr) << endl;
    cout << QuickSelect(arr, 5, PickBfprt) << endl;
    // cout << QuickSelect(arr, 5, PickFirst) << endl;
    // cout << QuickSelect(arr, 5, PickRandom) << endl;

    ranges::sort(arr);
    for (const auto &num: arr) cout << num << ", ";
}
