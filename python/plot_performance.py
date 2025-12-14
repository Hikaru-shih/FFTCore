import numpy as np
import matplotlib.pyplot as plt
import fftcore
import time
import os

# --- Output directory ---
output_dir = "figures"
os.makedirs(output_dir, exist_ok=True)

# sizes to test
sizes = [128, 256, 512, 1024, 2048, 4096]

def benchmark_fft(N, repeat=500):
    """Average FFT time for a given size."""
    x = np.random.rand(N).tolist()

    start = time.perf_counter()
    for _ in range(repeat):
        fftcore.fft(x)
    end = time.perf_counter()

    return (end - start) * 1e6 / repeat  # microseconds

def benchmark_dft(N):
    """DFT is slow → run only once."""
    x = np.random.rand(N).tolist()

    start = time.perf_counter()
    fftcore.dft(x)
    end = time.perf_counter()

    return (end - start) * 1e6  # microseconds

dft_times = []
fft_times = []

print("Running Python-side benchmark using your C++ FFT/DFT...")

for N in sizes:
    print(f"N = {N}")
    t_dft = benchmark_dft(N)
    t_fft = benchmark_fft(N)

    dft_times.append(t_dft)
    fft_times.append(t_fft)

print("Benchmark complete.")

# ----- Plotting -----

plt.figure(figsize=(10, 6))
plt.plot(sizes, dft_times, marker="o", label="DFT (O(N²))")
plt.plot(sizes, fft_times, marker="s", label="FFT (O(N log N))")

plt.xlabel("N (input size)")
plt.ylabel("Execution Time (microseconds)")
plt.title("DFT vs FFT Performance (Using Your C++ Implementation)")
plt.grid(True)
plt.legend()

# Save figure
output_path = os.path.join(output_dir, "performance.png")
plt.savefig(output_path, dpi=300)

print(f"Saved performance chart to: {output_path}")
