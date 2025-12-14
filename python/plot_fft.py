import numpy as np
import matplotlib.pyplot as plt
import fftcore
import os

# --- Output directory ---
output_dir = "figures"
os.makedirs(output_dir, exist_ok=True)

# generate signal
N = 512
t = np.linspace(0, 1, N, endpoint=False)

# mixed frequency signal
signal = (
    0.7 * np.sin(2 * np.pi * 5 * t) +    # 5 Hz
    0.4 * np.sin(2 * np.pi * 20 * t) +   # 20 Hz
    0.2 * np.sin(2 * np.pi * 50 * t)     # 50 Hz
)

# use your C++ FFT!
fft_result = fftcore.fft(signal.tolist())
fft_result = np.array(fft_result)

# magnitude spectrum
magnitude = np.abs(fft_result) / N
freqs = np.fft.fftfreq(N, 1/N)

# only positive frequencies
pos_mask = freqs >= 0
freqs = freqs[pos_mask]
magnitude = magnitude[pos_mask]

# ---- PLOTTING ----
plt.figure(figsize=(12, 6))

# Time domain
plt.subplot(2, 1, 1)
plt.plot(t, signal)
plt.title("Time Domain Signal")
plt.xlabel("Time")
plt.ylabel("Amplitude")

# Frequency domain
plt.subplot(2, 1, 2)
plt.stem(freqs, magnitude, basefmt=" ", linefmt='b-', markerfmt='bo')
plt.title("Frequency Spectrum (Using C++ FFT)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")

plt.tight_layout()

# Save figure instead of showing it
output_path = os.path.join(output_dir, "fft_spectrum.png")
plt.savefig(output_path, dpi=300)

print(f"Saved FFT spectrum figure to: {output_path}")
