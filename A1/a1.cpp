#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

struct circle {
    double x;
    double y;
    double r;
};

bool inCircle(circle c, double x, double y) {
    return pow(c.x - x, 2) + pow(c.y - y, 2) <= pow(c.r, 2);
}

void solve() {
    std::ofstream out("diffWide.txt");
    std::ofstream out2("squareWide.txt");
    const double s_real = (0.25 * M_PI + 1.25 * std::asin(0.8) - 1);

    std::cout << s_real;
    circle c1{1, 1, 1}, c2{1.5, 2, std::sqrt(5)/2}, c3{2, 1.5, std::sqrt(5)/2};

    double min_y = std::min(c1.y - c1.r, std::min(c2.y - c2.r, c3.y - c3.r));
    double max_y = std::max(c1.y + c1.r, std::min(c2.y + c2.r, c3.y + c3.r));
    double min_x = std::min(c1.x - c2.r, std::min(c2.x - c2.r, c3.x - c3.r));
    double max_x = std::max(c1.x + c2.r, std::min(c2.x + c2.r, c3.x + c3.r));
    double area = (max_x - min_x) * (max_y - min_y);

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<> distr_x(min_x, max_x);
    std::uniform_real_distribution<> distr_y(min_y, max_y);

    for (int n = 100; n <= 100000; n += 500) {
        int m = 0;
        for (int i = 0; i < n; ++i) {
            double x = distr_x(generator);
            double y = distr_y(generator);

            if (inCircle(c1, x, y) && inCircle(c2, x, y) && inCircle(c3, x, y)) {
                m += 1;
            }
        }
        std::cout.precision(15);
        double s = m * area / n;
        out << n << ", " << 100 * (s - s_real) / s_real << '\n';
        out2 << n << ", " << s << '\n';
    }

    out = std::ofstream("diffNarrow.txt");
    out2 = std::ofstream("squareNarrow.txt");

    min_y = 0.87;
    max_y = 2.1;
    min_x = 0.87;
    max_x = 2;
    area = (max_x - min_x) * (max_y - min_y);

    distr_x = std::uniform_real_distribution<>(min_x, max_x);
    distr_y = std::uniform_real_distribution<>(min_y, max_y);

    for (int n = 100; n <= 100000; n += 500) {
        int m = 0;
        for (int i = 0; i < n; ++i) {
            double x = distr_x(generator);
            double y = distr_y(generator);

            if (inCircle(c1, x, y) && inCircle(c2, x, y) && inCircle(c3, x, y)) {
                m += 1;
            }
        }
        std::cout.precision(15);
        double s = m * area / n;
        out << n << ", " << 100 * (s - s_real) / s_real << '\n';
        out2 << n << ", " << s << '\n';
    }
}

int main() {
    solve();
}