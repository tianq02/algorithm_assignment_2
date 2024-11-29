#include <iostream>
#include <pcg_random.hpp>
#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

int
main ()
{
  cout.precision (4);
  int N = 0;
  vector<int> arr;

  // cin >> N;
  // for (int i = 0; i < N; i++) {
  //     double tmp;
  //     cin >> tmp;
  //     arr.push_back(tmp);
  // }

  // generate test data
  pcg_extras::seed_seq_from<std::random_device> seed_source;
  pcg32 rng (seed_source);
  std::uniform_int_distribution dist (1, 10);
  N = 10;
  for (int i = 0; i < N; i++)
    arr.push_back (dist (rng));

  cout << "arr size:" << arr.size () << endl;
  for (const auto &i : arr)
    cout << i << ", ";
  cout << endl;

  unordered_map<int, int> map;
  for (const int &i : arr)
    {
      if (!map.contains (i))
        {
          map[i] = 1;
        }
      else
        {
          map[i] = map[i] + 1;
        }
    }
  int modeValue = 0, modeCount = 0;
  for (const auto &[fst, snd] : map)
    {
      if (snd > modeCount)
        {
          modeCount = snd;
          modeValue = fst;
        }
    }
  // ranges::sort (arr);
  // for (auto &i : arr)
  //   cout << i << ", ";
  // cout << endl;
  // cout << "modeValue:" << modeValue << ", modeCount:" << modeCount << endl;
  cout << endl
       << "answer:" << endl;
  cout << modeValue << endl;
  return 0;
}

