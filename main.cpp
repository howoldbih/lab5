#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double host_f(double x) {

    return std::cos(x) / (std::log(1 + std::sin(x)) * std::sin(1 + std::sin(x)));
}

int main() {
    double a = 1e-9;
    double b = M_PI - 1e-9;
    const int total_computational_units = 1000000; 

    double delta_x = (b - a) / total_computational_units;
    double total_sum = 0.0;
    
    std::cout << "Integrating f(x) = cot(x) / (ln(1+sin(x)) * sin(1+sin(x)))" << std::endl;
    std::cout << "Method: Sequential CPU Midpoint Rule" << std::endl;
    std::cout << "Interval: [" << a << ", " << b << "]" << std::endl;
    std::cout << "Total computational units (N): " << total_computational_units << std::endl;
    std::cout << "Delta x: " << delta_x << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < total_computational_units; ++i) {
        double x_i = a + (i + 0.5) * delta_x;
        total_sum += host_f(x_i) * delta_x;
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    double milliseconds = duration.count() / 1000.0;

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Integral result (CPU): " << total_sum << std::endl;
    std::cout << "Execution time (CPU): " << milliseconds << " ms" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    return 0;
}