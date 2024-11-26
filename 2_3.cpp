/**
 * 2_3.cpp
 *
 * 题目：
 * 给定一个由n个互不相同的数组成的集合S，及一个正整数k≤n，
 * 试设计一个O(n)时间算法找出S中最接近S的中位数的k个数
 *
 * 思想：
 * 本题目是典型的线性查找+topK排序问题
 * step.1 线性查找算法(BFPRT)，确定中位数的大小
 * step.2 按照和中位数的差值做topK排序，输出结果
 *
 */

#include <iostream>
#include <random>  // 为了在PCG算法中使用C11风格的 random device 安全初始化
#include <limits>  // 在CountedNth中使用，确定对应类型的最小值和最大值
#include "pcg_random.hpp"  // 非常优秀的现代伪随机生成器

double numbers[10000] = {0};

/**
 * get the median number by counting occurrence.
 * change lr in real world cases, e.g. last group of 5 in BFPRT.
 * beware we're not checking array boundaries here.
 * this function has no side effects, have fun multithreading.
 * average time: O(n^2), space: O(1)
 * when t<<n, average time O(n)
 * @param arr the array you want to determine its median
 * @param l left offset, search would start at arr[l]
 * @param r right offset, search ends at arr[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be a number in array between l and r. on error return -1
 */
template<typename NumType>
NumType CountedNth(const NumType arr[], int l = 0, int r = 4, int t = -1);

/**
 * Another implementation of median.
 * It performs bubble sort on given range of array to get median number, leaving some side effect
 * average time: O(n^2), space: O(1)
 * @param arr the array you want to determine its median
 * @param l left offset, search would start at arr[l]
 * @param r right offset, search ends at arr[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be a number in array between l and r. on error return -1
 */
template<typename NumType>
NumType SortedNth(NumType arr[], int l = 0, int r = 4, int t = -1);

/**
 * get median using std sort.
 * @param arr the array you want to determine its median
 * @param l left offset, search would start at arr[l]
 * @param r right offset, search ends at arr[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be a number in array between l and r. on error return -1
 */
template<typename NumType>
NumType StdSortedNth(NumType arr[], int l = 0, int r = 4, int t = -1);

/**
 * wrapper for bruteforce nth
 * @param arr the array you want to determine its median
 * @param l left offset, search would start at arr[l]
 * @param r right offset, search ends at arr[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be a number in array between l and r. on error return -1
 */
template<typename NumType>
NumType BruteNth(NumType arr[], int l = 0, int r = 4, int t = -1) {
    return SortedNth(arr, l, r, t);
}

/**
 * get median in given arr
 * wrap up BruteNth, calculate targeted median index, if duplicated, return their average
 * @param arr the array you want to determine its median
 * @param l left offset, search would start at arr[l]
 * @param r right offset, search ends at arr[r]
 * @return median number
 */
template<typename NumType>
NumType BruteMedian(NumType arr[], int l = 0, int r = 4);

template<typename NumType>
NumType CountedNth(const NumType arr[], const int l, const int r, const int t) {
    // idea: find smallest each time until desired rank.
    if (l > r || t > r - l) return NumType(); // Return default value of T on error
    const int targetRank = t < 0 ? (l + r) / 2 : t;
    // std::cout << "TargetRank:" << targetRank << "(" << targetRank + 1 << "th ranked)" << std::endl;
    NumType lastMin = std::numeric_limits<NumType>::min(), curRanked = 0;
    // +1是因为targetRank从0开始，而curRanked是计数从1开始
    while (curRanked < targetRank + 1) {
        NumType newMin = std::numeric_limits<NumType>::max();
        int newRanked = 0;
        for (int i = l; i <= r; i++) {
            if (arr[i] > lastMin & arr[i] < newMin) {
                newMin = arr[i];
                newRanked = 1;
            } else if (arr[i] == newMin) {
                newRanked++;
            }
        }
        curRanked += newRanked;
        lastMin = newMin;
        // std::cout << "CurRanked:" << curRanked << "\tNewRanked:" << newRanked << "\tValue:" << newMin << std::endl;
    }

    return lastMin;
}

template<typename NumType>
NumType SortedNth(NumType arr[], const int l, const int r, const int t) {
    if (l > r || t > r - l) return -1;
    for (int i = l; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            if (arr[i] <= arr[j]) continue;
            NumType temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    if (t < 0) return arr[(l + r) / 2];
    return arr[t];
}

template<typename NumType>
NumType StdSortedNth(NumType arr[], const int l, const int r, const int t) {
    if (l > r || t > r - l) return -1;
    std::sort(arr + l, arr + r);
    if (t < 0) return arr[(l + r) / 2];
    return arr[t];
}

template<typename NumType>
NumType BruteMedian(NumType arr[], const int l, const int r) {
    if (l > r) return -1;
    const int midL = (l + r) / 2;
    const int midR = (l + r + 1) / 2;

    if (midL == midR)
        return BruteNth(arr, l, r, midL);

    return (BruteNth(arr, l, r, midL) + BruteNth(arr, l, r, midR)) / NumType(2);
}


// int main() {
//     // PCG RNG magic, see https://www.pcg-random.org/using-pcg-cpp.htm
//     pcg_extras::seed_seq_from<std::random_device> seed_source;
//     pcg32 rng(seed_source);
//     std::uniform_int_distribution<int> uniform_dist(1, 100);
//
//     int numbers[100] = {0};
//     for (int i = 0; i < 10; i++) {
//         numbers[i] = uniform_dist(rng);
//         // std::cout << i << ":\t" << numbers[i] << std::endl;
//         std::cout << numbers[i] << ",\t";
//     }
//
//     double median = BruteMedian(numbers, 0, 10);
//     std::cout << median << std::endl;
//
//     double variations[100];
//
//     for (int i=0; i<100; i++) {
//         variations[i] = numbers[i] > median ? (numbers[i] - median) : (median - numbers[i]);
//     }
//
//     return 0;
// }

int main() {

    std::cout.precision(4);
    // PCG RNG magic, see https://www.pcg-random.org/using-pcg-cpp.htm
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    pcg32 rng(seed_source);
    std::uniform_real_distribution<double> uniform_dist(1, 100);

    double numbers[100] = {0};
    for (int i = 0; i < 10; i++) {
        numbers[i] = uniform_dist(rng);
        // std::cout << i << ":\t" << numbers[i] << std::endl;
        std::cout << numbers[i] << "/ ";
    }
    std::cout << std::endl;
    const double median1 = CountedNth(numbers, 0, 9);
    const double median2 = BruteNth(numbers, 0, 9);
    const double median3 = SortedNth(numbers, 0, 9);
    const double median4 = BruteMedian(numbers, 0, 9);
    std::cout << "median1:" << median1 << std::endl;
    std::cout << "median2:" << median2 << std::endl;
    std::cout << "median3:" << median3 << std::endl;
    std::cout << "median4:" << median4 << std::endl;
    for (int i = 0; i < 10; i++)
        // std::cout << i << ":\t" << numbers[i] << std::endl;
        std::cout << numbers[i] << "/ ";
    return 0;
}

/**
 * BFPRT算法：
 * 相当于快速选择算法，但不同的是每次选择近似中位数作为轴值
 * 为了选择中位数，我们将数据每5个分组，分别计算中位数，并取这些中位数们的中位数（递归BFPRT）
 * 让我们来看一下如何实现这个算法：
 * 1. BFPRT函数： 输入可比较的数组和目标序号n，输出第n大的元素元素
 *    其中
 *    - 每次选择中位数作为轴值，将数组划分为两块，判断目标所处的区间，选择对应的区间进行下一步BFPRT定位
 *    - 在选择中位数时，将数组每5个元素分块各自取中位数
 */