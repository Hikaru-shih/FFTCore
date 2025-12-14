#include "fftcore/utils.hpp"
#include <iostream>
#include <cmath>

namespace fftcore {

bool is_power_of_two(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int next_power_of_two(int n) {
    if (n <= 1) return 1;
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

int reverse_bits(int x, int bits) {
    int y = 0;
    for (int i = 0; i < bits; ++i) {
        y = (y << 1) | (x & 1);
        x >>= 1;
    }
    return y;
}

void print_complex_vector(const std::vector<std::complex<double>>& v,
                          const std::string& label) {
    if (!label.empty())
        std::cout << label << ":\n";

    for (auto& c : v) {
        std::cout << c << "\n";
    }
}

}
