#include "fftcore/fft.hpp"
#include "fftcore/utils.hpp"
#include <cmath>

namespace fftcore {

static const double PI = 3.14159265358979323846;

std::vector<std::complex<double>>
fft(const std::vector<std::complex<double>>& x)
{
    int N = x.size();

    if (!is_power_of_two(N)) {
        throw std::runtime_error("FFT input size must be a power of 2");
    }

    int levels = std::log2(N);

    std::vector<std::complex<double>> a(x);

    for (int i = 0; i < N; ++i) {
        int j = reverse_bits(i, levels);
        if (j > i) std::swap(a[i], a[j]);
    }

    for (int len = 2; len <= N; len <<= 1) {
        int half = len / 2;
        double angle = -2.0 * PI / len;

        std::complex<double> wlen(std::cos(angle), std::sin(angle));

        for (int i = 0; i < N; i += len) {
            std::complex<double> w = 1.0;

            for (int j = 0; j < half; ++j) {
                std::complex<double> u = a[i + j];
                std::complex<double> t = w * a[i + j + half];

                a[i + j]         = u + t;
                a[i + j + half]  = u - t;

                w *= wlen;
            }
        }
    }

    return a;
}

std::vector<std::complex<double>>
ifft(const std::vector<std::complex<double>>& X)
{
    int N = X.size();

    std::vector<std::complex<double>> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = std::conj(X[i]);
    }

    a = fft(a);

    for (int i = 0; i < N; ++i) {
        a[i] = std::conj(a[i]) / (double)N;
    }

    return a;
}

} // namespace fftcore
