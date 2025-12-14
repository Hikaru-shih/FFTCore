#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

#include "fftcore/dft.hpp"
#include "fftcore/fft.hpp"

namespace py = pybind11;

PYBIND11_MODULE(fftcore, m) {
    m.doc() = "FFT/DFT library implemented in C++ (pybind11 bindings)";

    m.def("dft",  &fftcore::dft,  "Compute DFT");
    m.def("idft", &fftcore::idft, "Compute inverse DFT");

    m.def("fft",  &fftcore::fft,  "Compute FFT (radix-2)");
    m.def("ifft", &fftcore::ifft, "Compute inverse FFT");
}
