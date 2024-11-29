#include "BFPRT.hpp"
#include <pcg_random.hpp> // 非常优秀的现代伪随机生成器
#include <iostream>
#include <random> // 为了在PCG算法中使用C11风格的 random device 安全初始化
#include <vector>
using namespace std;

int
main ()
{
  cout.precision (4);
  int k = 0, N = 0;
  vector<double> arr;

  // cin >> k >> N;
  // for (int i = 0; i < N; i++)
  //   {
  //     int tmp = 0;
  //     cin >> tmp;
  //     arr.push_back (tmp);
  //   }

  // generate test data
  pcg_extras::seed_seq_from<std::random_device> seed_source;
  pcg32 rng (seed_source);
  uniform_int_distribution<> dist (1, 10);
  k = 5;
  N = 10;
  for (int i = 0; i < N; i++)
    arr.push_back (dist (rng));

  // show input
  cout << "median k:" << k << ", total N:" << N << endl;
  for (auto &i : arr)
    cout << i << ", ";
  cout << endl;


  double lmid = QuickSelect (arr, (arr.size () - 1) / 2);
  double rmid = QuickSelect (arr, arr.size () / 2);
  double mid = (lmid + rmid) / 2;

  vector<double> variations;
  for (double &i : arr)
    variations.push_back (abs (i - mid));

  double maxVar = QuickSelect (variations, k-1);

  vector<double> ans, ge;
  for (double &i : arr)
    {
      if (abs (i - mid) < maxVar)
        ans.push_back (i);
      else
        ge.push_back (i);
    }
  for (double &i : ge) // deal with numbers equal to boundaries
    {
      if (abs (i - mid) <= maxVar && ans.size () < k)
        ans.push_back (i);
    }

  // cout << endl
  //      << "lmid:" << lmid << ", rmid:" << rmid << ", median:" << mid << endl;
  // cout << "variations:" << endl;
  // for (auto &i : variations)
  //   cout << i << ", ";
  // cout << endl;
  // cout << "maxVar:" << maxVar << endl;
  cout << endl
       << "answer:" << endl;
  for (auto &i : ans)
    cout << i << ", ";
  cout << endl;
}

