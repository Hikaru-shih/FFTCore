#ifndef FFTCORE_FFT_HPP
#define FFTCORE_FFT_HPP

#include <complex>
#include <vector>

namespace fftcore {

    // Fast Fourier Transform (Radix-2, iterative)
    std::vector<std::complex<double>>
    fft(const std::vector<std::complex<double>>& x);

    // Inverse FFT
    std::vector<std::complex<double>>
    ifft(const std::vector<std::complex<double>>& X);

}

#endif // FFTCORE_FFT_HPP
