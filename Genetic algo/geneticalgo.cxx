#include <iostream>
#include <vector>
#include <math.h>
#include <random>

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
}