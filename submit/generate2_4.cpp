//
// Created by tianq on 24-11-29.
//
#include <iostream>
#include <pcg_random.hpp>
#include <random>
using namespace std;
int main() {
    constexpr int N = 10;

    // generate test data
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    pcg32 rng (seed_source);
    std::uniform_int_distribution dist (1, 10);

    cout << N << endl;
    for (int i = 0; i < N; i++)
        cout << dist(rng) << " ";
}