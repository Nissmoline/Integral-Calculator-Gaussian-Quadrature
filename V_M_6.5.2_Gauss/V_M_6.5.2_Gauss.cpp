#include <iostream>
#include <cmath>
#include <locale>

// Подынтегральная функция
double f(double x) {
    return 1.0 / sqrt(1 + pow(x, 4));
}

// Функция для численного интегрирования с использованием составной формулы Гаусса
double gauss_integration(double a, double b, double (*func)(double), int n, const double* weights, const double* nodes) {
    double result = 0.0;
    double interval_length = (b - a) / n;
    double middle;

    for (int i = 0; i < n; i++) {
        middle = a + i * interval_length + interval_length / 2;
        for (int j = 0; j < 6; j++) {
            result += weights[j] * func(middle + interval_length / 2 * nodes[j]);
        }
    }

    return (interval_length / 2) * result;
}

int main() {
    setlocale(LC_ALL, "");
    int n = 1;
    double a = 0.0;
    double b = 2.0;

    double input_eps;
    std::cout << "Enter the required integration accuracy: ";
    std::cin >> input_eps;
    double eps = input_eps;

    const double weights[] = { 0.171324492379170, 0.360761573048139, 0.467913934572691, 0.467913934572691, 0.360761573048139, 0.171324492379170 };
    const double nodes[] = { -0.932469514203152, -0.661209386466265, -0.238619186083197, 0.238619186083197, 0.661209386466265, 0.932469514203152 };
    double integral_prev = gauss_integration(a, b, f, n, weights, nodes);
    double integral_curr = 0.0;
    double relative_error = 0.0;

    do {
        n *= 2;
        integral_curr = gauss_integration(a, b, f, n, weights, nodes);
        relative_error = fabs(integral_curr - integral_prev) / integral_prev;
        integral_prev = integral_curr;
    } while (relative_error > eps);

    std::cout << "Integral value: " << integral_curr << std::endl;
    std::cout << "Integration accuracy: " << std::scientific << relative_error << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
