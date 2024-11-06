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

int numbers[1000] = {0};

/**
 * get the index of median number in an array of numbers with length 5
 * change lr in real world cases, e.g. last group of 5 in BFPRT
 * beware we're not checking array boundaries here
 * @param num5 the array you want to determine its median
 * @param l left offset, search would start at num5[l]
 * @param r right offset, search ends at num5[r]
 * @return index of median number, should be int between l and r. on error return -1
 */
int MedianIn5(int num5[], int l=0, int r=5);

int MedianIn5(int num5[], int l, int r) {
    if (l <= r) return -1;  // param check
    return 0;
}


int main() {
    std::cout << "Solution 2_3" << std::endl;
    return 0;
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