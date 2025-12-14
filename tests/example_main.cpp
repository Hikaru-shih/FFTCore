#include <iostream>
#include <complex>
#include <vector>
#include <chrono>

#include "fftcore/dft.hpp"
#include "fftcore/fft.hpp"
#include "fftcore/utils.hpp"

// 測時間的小工具
template <typename Func>
long long measure_ms(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void run_performance_test() {
    std::cout << "\n===== Performance Test: DFT vs FFT =====\n";

    for (int N : {256, 512, 1024, 2048}) {
        std::cout << "\n--- N = " << N << " ---\n";

        // 隨機產生訊號
        std::vector<std::complex<double>> x(N);
        for (int i = 0; i < N; ++i) {
            x[i] = {std::sin(i), std::cos(i)};
        }

        // 測 DFT
        long long t_dft = measure_ms([&]() {
            auto X = fftcore::dft(x);
        });

        // 測 FFT
        long long t_fft = measure_ms([&]() {
            auto X = fftcore::fft(x);
        });

        // 印結果
        std::cout << "DFT time = " << t_dft << " ms\n";
        std::cout << "FFT time = " << t_fft << " ms\n";

        double speedup =
            (t_fft == 0 ? 0.0 : (double)t_dft / (double)t_fft);

        if (t_fft == 0) {
            std::cout << "FFT is too fast to measure at this scale.\n";
        } else {
            std::cout << "Speedup = " << speedup << "x faster\n";
        }
    }
}

void run_correctness_test() {
    std::cout << "\n===== Correctness Test =====\n";

    for (int N : {8, 16, 32, 64, 128}) {
        std::cout << "\n--- N = " << N << " ---\n";

        // 建立測試訊號
        std::vector<std::complex<double>> x(N);
        for (int i = 0; i < N; ++i) {
            x[i] = {std::sin(i), std::cos(i)};
        }

        // DFT 與 FFT 比較
        auto X_dft = fftcore::dft(x);
        auto X_fft = fftcore::fft(x);

        double max_diff = 0.0;
        for (int i = 0; i < N; ++i) {
            double diff = std::abs(X_dft[i] - X_fft[i]);
            if (diff > max_diff) max_diff = diff;
        }

        std::cout << "Max difference between DFT & FFT = "
                  << max_diff << "\n";

        // FFT → IFFT 應該回到原始 x
        auto x_rec = fftcore::ifft(X_fft);

        double max_diff2 = 0.0;
        for (int i = 0; i < N; ++i) {
            double diff = std::abs(x_rec[i] - x[i]);
            if (diff > max_diff2) max_diff2 = diff;
        }

        std::cout << "Max difference after IFFT(FFT(x)) = "
                  << max_diff2 << "\n";
    }
}


int main() {
    std::vector<std::complex<double>> x = {
        {1.0, 0.0},
        {2.0, 0.0},
        {3.0, 0.0},
        {4.0, 0.0}
    };

    auto X  = fftcore::dft(x);
    auto x2 = fftcore::idft(X);

    std::cout << "Original signal:\n";
    for (auto& v : x) {
        std::cout << v << "\n";
    }

    std::cout << "\nDFT:\n";
    for (auto& v : X) {
        std::cout << v << "\n";
    }

    std::cout << "\nIDFT:\n";
    for (auto& v : x2) {
        std::cout << v << "\n";
    }

    run_performance_test();
    run_correctness_test();

    return 0;
}
