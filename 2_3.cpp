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
#include "pcg_random.hpp"

int numbers[10000] = {0};

/**
 * get the median number in an array of numbers with length 5.
 * change lr in real world cases, e.g. last group of 5 in BFPRT.
 * beware we're not checking array boundaries here.
 * this function has no side effects, have fun multithreading.
 * average time: O(n^2), space: O(1)
 * when t<<n, average time O(n)
 * @param num5 the array you want to determine its median
 * @param l left offset, search would start at num5[l]
 * @param r right offset, search ends at num5[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be int between l and r. on error return -1
 */
int Median5(const int num5[], int l = 0, int r = 4, int t = -1);

/**
 * Another implementation of median_in_five
 * It performs bubble sort on given range of array to get median number, leaving some side effect
 * average time: O(n^2), space: O(1)
 * @param num5 the array you want to determine its median
 * @param l left offset, search would start at num5[l]
 * @param r right offset, search ends at num5[r]
 * @param t target rank, [0,r-l], get n-th smallest in given range, -1:median
 * @return value of median or rank t, should be int between l and r. on error return -1
 */
int Sorted5(int num5[], int l = 0, int r = 4, int t = -1);

int Partition(int array[], int l, int r, int pivot);

auto ComputeMedian = Median5;

int Median5(const int num5[], const int l, const int r, const int t) {
    // idea: find smallest each time until desired rank.
    if (l > r || t > r - l) return -1;
    const int targetRank = t < 0 ? (l + r) / 2 : t;
    std::cout << "TargetRank:" << targetRank << "(" << targetRank + 1 << "th ranked)" << std::endl;
    int lastMin = INT_MIN, curRanked = 0;
    // +1是因为targetRank从0开始，而curRanked是计数从1开始
    while (curRanked < targetRank + 1) {
        int newMin = INT_MAX, newRanked = 0;
        for (int i = l; i <= r; i++) {
            if (num5[i] > lastMin & num5[i] < newMin) {
                newMin = num5[i];
                newRanked = 1;
            } else if (num5[i] == newMin) {
                newRanked++;
            }
        }
        curRanked += newRanked;
        lastMin = newMin;
        std::cout << "CurRanked:" << curRanked << "\tNewRanked:" << newRanked << "\tValue:" << newMin << std::endl;
    }

    return lastMin;
}

int Sorted5(int num5[], const int l, const int r, const int t) {
    if (l > r || t > r - l) return -1;
    for (int i = l; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            if (num5[i] > num5[j]) {
                int temp = num5[i];
                num5[i] = num5[j];
                num5[j] = temp;
            }
        }
    }
    if (t < 0) return num5[(l + r) / 2];
    return num5[t];
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
    const int median1 = Median5(numbers, 0, 99);
    const int median2 = ComputeMedian(numbers, 0, 99, -1);
    const int median3 = Sorted5(numbers, 0, 99);
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
