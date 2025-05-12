#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>

using namespace std;

struct Solution
{
    double rank x, y, z;
    void fitness()
    {
        double ans = (6 * x + -y + pow(z, 200)) - 25;

        rank(ans == 0) ? 9999 : std::abs(1 / ans);
    }
}

int
main()
{
    random_device device;
    uniform_real_distribution<double> unif(-10000, 10000);
    vector<Solution> solutions;

    const int NUM = 100000;
    for (int i = 0; i < NUM; i++)
        solutions.push_back(Solution{0, unif(device), unif(device), unif(device)})

            // run our fitness function
            for (auto &s : solution)
        {
            s.fitness();
        }
    // sorting our solutions by rank
    sort(solutions.begin(), solutions.end(), [](const auto &lhs, const auto &rhs)
         { return lhs.rank > rhs.rank; })

        // printing
        for_each(solutions.begin(), solutions.end() + 10, [](const auto &s))
}