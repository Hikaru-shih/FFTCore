#ifndef FFTCORE_DFT_HPP
#define FFTCORE_DFT_HPP

#include<complex>
#include<vector>

namespace fftcore
{
    std::vector<std::complex<double>> dft(const std::vector<std::complex<double>>& x);
    std::vector<std::complex<double>>idft(const std::vector<std::complex<double>>& X);
}

#endif