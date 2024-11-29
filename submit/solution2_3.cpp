//
// Created by tianq on 24-11-29.
//
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int groupSize = 5;

/**
 * pick median of given array
 * @param arr the array to be parsed
 * @return median of given array, when arr size is odd, bigger one is chosen
 * @attention not a mathematical median,
 */
template<typename NumType>
NumType BruteMedian(vector<NumType> arr) {
    ranges::sort(arr);
    return arr[arr.size() / 2];
}

/**
 * pick a likely median element from vector,used by BFPRT
 * @param arr the array to be parsed
 * @return element from array
 */
template<typename NumType>
NumType PickBfprt(const vector<NumType> &arr) {
    if (arr.size() <= groupSize) return BruteMedian(arr);

    auto it = arr.begin();
    vector<NumType> medians;
    while (it != arr.end()) {
        vector<NumType> group;
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
template<typename NumType>
NumType QuickSelect(vector<NumType> arr, const unsigned long long targetIndex, NumType (*PickPivot)(const vector<NumType>&) = PickBfprt) {
    if (arr.size() == 1) return arr.front();

    const NumType pivot = PickPivot(arr);

    vector<NumType> left, mid, right;
    for (NumType &num: arr) {
        if (num < pivot) left.push_back(num);
        else if (num > pivot) right.push_back(num);
        else mid.push_back(num);
    }

    if (targetIndex < left.size())
        return QuickSelect(left, targetIndex, PickPivot);
    if (targetIndex < left.size() + mid.size())
        return mid.front();
    return QuickSelect(right, targetIndex - left.size() - mid.size(), PickPivot);
}

int main (){

    int k = 0, N = 0;
    vector<double> arr;  // 考虑到中位数出现0.5的情况，double更合适

    cin >> k >> N;
    for (int i = 0; i < N; i++) {
        int tmp = 0;
        cin >> tmp;
        arr.push_back (tmp);
    }

    const double lmid = QuickSelect (arr, (arr.size () - 1) / 2);
    const double rmid = QuickSelect (arr, arr.size () / 2);
    const double mid = (lmid + rmid) / 2;

    vector<double> variations;
    for (const double &i : arr)
        variations.push_back (abs (i - mid));

    double maxVar = QuickSelect (variations, k-1);

    vector<double> ans, ge;
    for (double &i : arr) {
        if (abs (i - mid) < maxVar)
            ans.push_back (i);
        else
            ge.push_back (i);
    }
    for (double &i : ge) { // deal with numbers equal to boundaries
        if (abs (i - mid) <= maxVar && ans.size () < k)
            ans.push_back (i);
    }
    for (const auto &i : ans)
        cout << i << " ";
    cout << endl;
}