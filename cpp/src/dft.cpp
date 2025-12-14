#include "fftcore/dft.hpp"
#include <cmath>

namespace fftcore {

static const double PI = 3.14159265358979323846;

std::vector<std::complex<double>>
dft(const std::vector<std::complex<double>>& x)
{
    int N = x.size();
    std::vector<std::complex<double>> X(N);

    for (int i = 0; i < N; i++) {
        std::complex<double> sum = 0;
        for (int j = 0; j < N; j++) {
            double angle = -2.0 * PI * i * j / N;
            std::complex<double> w(std::cos(angle), std::sin(angle));
            sum += x[j] * w;
        }
        X[i] = sum;
    }

    return X;
}

std::vector<std::complex<double>>
idft(const std::vector<std::complex<double>>& X)
{
    int N = X.size();
    std::vector<std::complex<double>> x(N);

    for (int i = 0; i < N; i++) {
        std::complex<double> sum = 0;
        for (int j = 0; j < N; j++) {
            double angle = 2.0 * PI * j * i / N;
            std::complex<double> w(std::cos(angle), std::sin(angle));
            sum += X[j] * w;
        }
        x[i] = sum / (double)N;
    }

    return x;
}

}
