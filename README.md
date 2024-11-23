# Integral Calculator Using Gaussian Quadrature

This repository contains a C++ program that computes the definite integral of a given function over a specified interval using the **Composite Gaussian Quadrature** method with a 6-point Gauss-Legendre rule.

## Problem Statement

Numerical integration is essential for approximating definite integrals, especially when an analytical solution is challenging or impossible to obtain. The **Composite Gaussian Quadrature** method divides the integration interval into smaller subintervals and applies Gaussian quadrature to each, enhancing accuracy for functions that are not well-approximated over the entire interval.

### Input:

- **Integration Interval**: Lower bound $( a \)$ and upper bound $( b \)$.
- **Desired Accuracy**: User-defined tolerance $( \epsilon \)$ for the relative error of the integral approximation.

### Output:

- **Integral Value**: Approximated value of the definite integral.
- **Achieved Accuracy**: Relative error of the approximation.

## Features

1. **Composite Gaussian Quadrature**:
   - Divides the integration interval into $( n \)$ subintervals.
   - Applies a 6-point Gauss-Legendre quadrature rule to each subinterval.

2. **Adaptive Refinement**:
   - Doubles the number of subintervals iteratively.
   - Continues refinement until the relative error is within the user-specified tolerance $( \epsilon \)$.

3. **User Interaction**:
   - Prompts the user to input the desired accuracy.
   - Displays the computed integral value and the achieved accuracy.

## Implementation Details

### Algorithm Description: Composite Gaussian Quadrature

The program utilizes a 6-point Gauss-Legendre quadrature rule, which is effective for integrating polynomials up to degree 11 exactly. By dividing the interval $[a, b]$ into $( n \)$ subintervals and applying the quadrature rule to each, the method enhances accuracy for functions that are not well-approximated over the entire interval.

**Steps:**

1. **Initialization**:
   - Set the initial number of subintervals $( n = 1 \)$.
   - Define the integration interval $[a, b]$.
   - Prompt the user to input the desired accuracy $( \epsilon \)$.

2. **Quadrature Application**:
   - For each subinterval, apply the 6-point Gauss-Legendre quadrature rule using predefined weights and nodes.

3. **Adaptive Refinement**:
   - Compute the integral approximation.
   - Calculate the relative error between successive approximations.
   - Double the number of subintervals $( n \)$ and repeat until the relative error is within $( \epsilon \)$.

4. **Output Results**:
   - Display the computed integral value.
   - Show the achieved accuracy in scientific notation.

## Example

Given the function $f(x) = \frac{1}{\sqrt{1 + x^4}}$  over the interval $[0, 2]$, the program approximates the integral with a user-defined accuracy.

**Sample Output**:

```
Enter the required integration accuracy:1e-6
Integral value: 1.525512
Integration accuracy: 9.876543e-7
```

## Code Structure

### Main Function

Handles user input, initializes parameters, and manages the iterative refinement process:

```cpp
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
```

### Gaussian Quadrature Function

Performs the numerical integration over the specified interval:

```cpp
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
```

### Integrand Function

Defines the function to be integrated:

```cpp
double f(double x) {
    return 1.0 / sqrt(1 + pow(x, 4));
}
```

## Requirements

- **Language**: C++
- **Compiler**: Any standard-compliant C++ compiler
- **Libraries**: Standard C++ libraries (`<iostream>`, `<cmath>`, `<locale>`)

## Usage

1. **Clone the Repository**:

   ```bash 
