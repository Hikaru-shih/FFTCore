#ifndef FFTCORE_UTILS_HPP
#define FFTCORE_UTILS_HPP

#include <complex>
#include <vector>
#include <string>

namespace fftcore {

    bool is_power_of_two(int n);

    int next_power_of_two(int n);

    int reverse_bits(int x, int bits);

    void print_complex_vector(const std::vector<std::complex<double>>& v,
                              const std::string& label = "");

}

#endif