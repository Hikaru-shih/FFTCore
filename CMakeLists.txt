cmake_minimum_required(VERSION 3.12)
project(fftcore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================================
# Core FFT Library (static or shared is ok)
# ==========================================================
add_library(fftcore_lib
    cpp/src/dft.cpp
    cpp/src/utils.cpp
    cpp/src/fft.cpp
)

# Required for Python module linking
set_target_properties(fftcore_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(fftcore_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/include
)

# ==========================================================
# Example executable
# ==========================================================
add_executable(fftcore_example tests/example_main.cpp)
target_link_libraries(fftcore_example PRIVATE fftcore_lib)

add_executable(fftcore_benchmark tests/benchmark.cpp)
target_link_libraries(fftcore_benchmark PRIVATE fftcore_lib)

# ==========================================================
# Python Binding (pybind11)
# ==========================================================
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Python module name is fftcore (import fftcore)
pybind11_add_module(fftcore python/bindings.cpp)

# Link our FFT library into the Python module
target_link_libraries(fftcore PRIVATE fftcore_lib)
