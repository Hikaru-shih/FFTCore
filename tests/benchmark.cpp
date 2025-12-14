#include <iostream>
#include <vector>
#include <complex>
#include <chrono>
#include <cmath>

#include "fftcore/dft.hpp"
#include "fftcore/fft.hpp"

using namespace std;
using namespace std::chrono;

constexpr double PI = 3.14159265358979323846;

vector<complex<double>> generate_signal(int N) {
    vector<complex<double>> x(N);
    for (int i = 0; i < N; i++) {
        double t = i * 2 * PI / N;
        x[i] = sin(5 * t);   // simple sine wave
    }
    return x;
}

template <typename Func>
long long measure_ms(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    vector<int> sizes = {256, 512, 1024, 2048, 4096};

    cout << "=== FFT vs DFT Performance Test ===\n\n";

    for (int N : sizes) {
        auto x = generate_signal(N);

        cout << "N = " << N << "\n";

        long long t_dft = measure_ms([&]() {
            auto X = fftcore::dft(x);
        });

        long long t_fft = measure_ms([&]() {
            auto X = fftcore::fft(x);
        });

        cout << "  DFT time: " << t_dft << " us\n";
        cout << "  FFT time: " << t_fft << " us\n";
        cout << "----------------------------------\n";
    }

    return 0;
}
