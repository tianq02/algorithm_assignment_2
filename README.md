# Assignment 2
> CHD 24 fall Advanced Algorithm Design and Analysis

## [2-3](2_3.cpp)

> 给定一个由 $n$ 个互不相同的数组成的集合 $S$，及一个正整数 $k \le n$ ，试设计一个 $O(n)$ 时间算法找出 $S$ 中最接近 $S$ 的中位数的 $k$ 个数。  
> Given a set $S$ consisting of $n$ distinct numbers and a positive integer $k \le n$, try to design an $O(n)$ time algorithm to find the knumbers closest to the median of $S$ in $S$.

Solution:

查找中位数，接下来计算每个数和中位数的差，按照差的绝对值做topK**排序**$O(kn)$，输出结果

> BFPRT线性查找算法 [Blum et al. (1973)](http://people.csail.mit.edu/rivest/pubs/BFPRT73.pdf)  
> 
> 概括：类似快速排序，每次选择轴值左右分组查找，对于轴值的选择，在给定的区间中每5个分组分别取中位数（插入排序），对于各组中位数的结果继续取中位数（递归调用中位数算法），直到取出这些中位数们55一组的中位数，这个数跟真正的中位数八九不离十
> 
> 算法的时间最坏情况下也是 $O(n)$  


## [2-4](2_4.cpp)

在一个由元素组成的表中，出现的次数最多的元素称为众数。试写一个寻找众数的算法，并分析其计算复杂性。

In a table composed of elements, the element that appears the most often is called the mode. Write an algorithm to find the mode and analyze its computational complexity