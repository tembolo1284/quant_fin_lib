# Quantitative Finance Library

A C++ library for quantitative finance calculations with Python bindings, including options pricing, risk metrics, and Greeks calculations.

## Features

- Option Pricing Models
  - Black-Scholes
  - Binomial Tree
  - Monte Carlo
- Risk Metrics
  - Historical VaR
  - Parametric VaR
- Options Greeks
  - Delta
  - Gamma
  - Vega
  - Theta
  - Rho
- Yield Curve Interpolation
  - Linear
  - Cubic Spline

## Prerequisites

- CMake (>= 3.15)
- C++ compiler supporting C++17
- Python (>= 3.8)
- Poetry

## Building C++ Library

```bash
# Create build directory
cmake -B build -G Ninja

# Build project

cmake --build build

## Running C++ Tests
```
# From build directory
./test_quant_fin_lib
```

## Python Installation

```
# Install dependencies
poetry install

# Run main.py example
poetry run python python_bindings/main.py

# Run python tests
export PYTHONPATH=$PYTHONPATH:$(pwd)
poetry run pytest python_bindings/tests/

```

## Usage

### C++

```
#include "quant_fin_lib.h"

// Calculate Black-Scholes price
double price = black_scholes_price(100, 100, 0.05, 1, 0.2, 1);
```

### Python

```
from python_bindings.quant_fin import black_scholes_price

# Calculate Black-Scholes price
price = black_scholes_price(100, 100, 0.05, 1, 0.2, 1)

````

## Configuration

### CMake Options

- Build shared library: Default
- Build tests: Enabled by default

### Python Configuration
- Poetry dependencies in pyproject.toml
- CFFI for C++ bindings

