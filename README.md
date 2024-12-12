# Quantitative Finance Library
A C++ library for quantitative finance calculations with Python bindings and RESTful API, including options pricing, risk metrics, and Greeks calculations.

## Features

### Core Library Features
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

### RESTful API Features
- HTTP/2 support via Drogon framework
- JSON request/response format
- CORS support for cross-origin requests
- Comprehensive error handling
- Request validation
- Detailed logging
- Endpoints for:
  - Black-Scholes pricing
  - Monte Carlo simulation
  - Binomial Tree calculation

## Prerequisites

### Core Library
- CMake (>= 3.15)
- C++ compiler supporting C++17
- Python (>= 3.8)
- Poetry

### API Dependencies
- Drogon framework
- spdlog for logging
- nlohmann-json for JSON handling
- OpenSSL for HTTPS support

## Installation

### Installing Dependencies

```bash
# Install core build tools
sudo apt-get install -y cmake g++ ninja-build

# Install API dependencies
sudo apt-get install -y git gcc g++ cmake libjsoncpp-dev uuid-dev \
    openssl libssl-dev zlib1g-dev postgresql-server-dev-all \
    libc-ares-dev libcurl4-openssl-dev libspdlog-dev

# Install Drogon framework
git clone https://github.com/drogonframework/drogon
cd drogon
git checkout v1.8.7  # Using stable version
git submodule update --init
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ..
make && sudo make install
```

## Building

### Building C++ Library and API
```bash
# Create build directory and build project
cmake -B build -G Ninja
cmake --build build

# Run the API server
./build/bin/api_server
```

### Running C++ Tests
```bash
# From build directory
./build/bin/test_quant_fin_lib
```

### Python Installation
```bash
# Install dependencies
poetry install

# Run main.py example
poetry run python python_bindings/main.py

# Run python tests
export PYTHONPATH=$PYTHONPATH:$(pwd)
poetry run pytest python_bindings/tests/
```

## Usage

### C++ Library
```cpp
#include "quant_fin_lib.h"

// Calculate Black-Scholes price
double price = black_scholes_price(100, 100, 0.05, 1, 0.2, 1);
```

### Python
```python
from python_bindings.quant_fin import black_scholes_price

# Calculate Black-Scholes price
price = black_scholes_price(100, 100, 0.05, 1, 0.2, 1)
```

### RESTful API

The API server runs on port 8080 by default and provides the following endpoints:

#### Black-Scholes Pricing
```bash
POST /api/v1/pricing/black-scholes
Content-Type: application/json

{
    "spot_price": 100.0,
    "strike_price": 100.0,
    "risk_free_rate": 0.05,
    "time_to_maturity": 1.0,
    "volatility": 0.2,
    "is_call": true
}
```

#### Monte Carlo Simulation
```bash
POST /api/v1/pricing/monte-carlo
Content-Type: application/json

{
    "spot_price": 100.0,
    "strike_price": 100.0,
    "risk_free_rate": 0.05,
    "time_to_maturity": 1.0,
    "volatility": 0.2,
    "is_call": true,
    "num_simulations": 10000,
    "num_steps": 252
}
```

#### Binomial Tree Pricing
```bash
POST /api/v1/pricing/binomial-tree
Content-Type: application/json

{
    "spot_price": 100.0,
    "strike_price": 100.0,
    "risk_free_rate": 0.05,
    "time_to_maturity": 1.0,
    "volatility": 0.2,
    "is_call": true,
    "num_steps": 100
}
```

All API endpoints return JSON responses in the following format:
```json
{
    "success": true,
    "message": "Option price calculated successfully",
    "data": {
        "price": 10.45,
        "input_params": {
            // Echo of input parameters
        }
    }
}
```

Error responses follow this format:
```json
{
    "success": false,
    "message": "Error description",
    "data": null
}
```

## Configuration

### CMake Options
- BUILD_API: Enables building the REST API server (ON by default)
- Build shared library: Default
- Build tests: Enabled by default

### API Configuration
- config.json for server settings
  - Port configuration
  - Thread pool size
  - Logging settings
  - CORS settings

### Python Configuration
- Poetry dependencies in pyproject.toml
- CFFI for C++ bindings
