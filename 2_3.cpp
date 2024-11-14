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
#include <random>
#include <climits>
#include "pcg_random.hpp"

int numbers[10000] = {0};

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
int CountedNth(const int arr[], int l = 0, int r = 4, int t = -1);

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
int SortedNth(int arr[], int l = 0, int r = 4, int t = -1);

/**
 * get median using std sort.
 * @param arr the array you want to determine its median
 * @param l left offset, search would start at arr[l]
 * @param r right offset, search ends at arr[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be a number in array between l and r. on error return -1
 */
int StdSortedNth(int arr[], int l = 0, int r = 4, int t = -1);

/**
 * wrapper for bruteforce nth
 * @param arr the array you want to determine its median
 * @param l left offset, search would start at arr[l]
 * @param r right offset, search ends at arr[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be a number in array between l and r. on error return -1
 */
int BruteNth(int arr[], int l = 0, int r = 4, int t = -1) {
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
double BruteMedian(int arr[], int l = 0, int r = 4);

int CountedNth(const int arr[], const int l, const int r, const int t) {
    // idea: find smallest each time until desired rank.
    if (l > r || t > r - l) return -1;
    const int targetRank = t < 0 ? (l + r) / 2 : t;
    std::cout << "TargetRank:" << targetRank << "(" << targetRank + 1 << "th ranked)" << std::endl;
    int lastMin = INT_MIN, curRanked = 0;
    // +1是因为targetRank从0开始，而curRanked是计数从1开始
    while (curRanked < targetRank + 1) {
        int newMin = INT_MAX, newRanked = 0;
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
        std::cout << "CurRanked:" << curRanked << "\tNewRanked:" << newRanked << "\tValue:" << newMin << std::endl;
    }

    return lastMin;
}

int SortedNth(int arr[], const int l, const int r, const int t) {
    if (l > r || t > r - l) return -1;
    for (int i = l; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    if (t < 0) return arr[(l + r) / 2];
    return arr[t];
}

int StdSortedNth(int arr[], const int l, const int r, const int t) {
    if (l > r || t > r - l) return -1;
    std::sort(arr+l, arr + r);
    if (t < 0) return arr[(l + r) / 2];
    return arr[t];
}

double BruteMedian(int arr[], const int l, const int r) {
    if (l > r) return -1;
    const int midL = (l + r) / 2;
    const int midR = (l + r + 1) / 2;

    if (midL == midR)
        return BruteNth(arr, l, r, midL);

    return (static_cast<double>(BruteNth(arr, l, r, midL)) + static_cast<double>(BruteNth(arr, l, r, midR)))/2;
}





int main() {
    // PCG RNG magic, see https://www.pcg-random.org/using-pcg-cpp.htm
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    pcg32 rng(seed_source);
    std::uniform_int_distribution<int> uniform_dist(1, 100);

    int numbers[100] = {0};
    for (int i = 0; i < 100; i++) {
        numbers[i] = uniform_dist(rng);
        std::cout << i << ":\t" << numbers[i] << std::endl;
    }
    std::cout << std::endl;
    const int median1 = CountedNth(numbers, 0, 99);
    const int median2 = BruteNth(numbers, 0, 99, -1);
    const int median3 = SortedNth(numbers, 0, 99);
    std::cout << "median1:" << median1 << std::endl;
    std::cout << "median2:" << median2 << std::endl;
    std::cout << "median3:" << median3 << std::endl;
    for (int i = 0; i < 100; i++) std::cout << i << ":\t" << numbers[i] << std::endl;
}

/**
* 下面时早期一些不成熟的想法，有明显的错误，删了可惜，就留在这里了
*
* (这样求不出中位数)
* 为了得到O(n)时间，没法执行排序算法，将算法分成两步骤执行
* step. 1
* 维护左右边界min/max以及各自计数cl,cr,ck
* 其中，cl是过小被丢弃的数量，cr过大，ck当前选中*
*
* 维护长k的队列s，不满时直接入队，满时和队列各元素比较并挤走一部分
*
*/
