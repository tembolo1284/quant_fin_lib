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

#### Testing API Endpoints with curl

Test Black-Scholes pricing:
```bash
curl -X POST http://localhost:8080/api/v1/pricing/black-scholes \
  -H "Content-Type: application/json" \
  -d '{
    "spot_price": 100.0,
    "strike_price": 100.0,
    "risk_free_rate": 0.05,
    "time_to_maturity": 1.0,
    "volatility": 0.2,
    "is_call": true
  }'
```

Test Monte Carlo simulation:
```bash
curl -X POST http://localhost:8080/api/v1/pricing/monte-carlo \
  -H "Content-Type: application/json" \
  -d '{
    "spot_price": 100.0,
    "strike_price": 100.0,
    "risk_free_rate": 0.05,
    "time_to_maturity": 1.0,
    "volatility": 0.2,
    "is_call": true,
    "num_simulations": 10000,
    "num_steps": 252
  }'
```

Test Binomial Tree calculation:
```bash
curl -X POST http://localhost:8080/api/v1/pricing/binomial-tree \
  -H "Content-Type: application/json" \
  -d '{
    "spot_price": 100.0,
    "strike_price": 100.0,
    "risk_free_rate": 0.05,
    "time_to_maturity": 1.0,
    "volatility": 0.2,
    "is_call": true,
    "num_steps": 100
  }'
```

Sample successful response:
```json
{
    "success": true,
    "message": "Option price calculated successfully",
    "data": {
        "price": 10.45,
        "input_params": {
            "spot_price": 100.0,
            "strike_price": 100.0,
            "risk_free_rate": 0.05,
            "time_to_maturity": 1.0,
            "volatility": 0.2,
            "is_call": true
        }
    }
}
```

Sample error response:
```json
{
    "success": false,
    "message": "Error description",
    "data": null
}
```

### Docker Support

The project includes comprehensive Docker support through the `docker-run.sh` script, which provides several commands for building, testing, and running the project.

#### Docker Script Usage

```bash
./docker-run.sh [command] [options]
```

Available commands:

1. **Build Commands:**
```bash
# Build the entire project
./docker-run.sh build

# Build with API support explicitly
./docker-run.sh build-api
```

2. **Run Commands:**
```bash
# Run C++ executable
./docker-run.sh run cpp

# Run Python example
./docker-run.sh run python

# Run API server
./docker-run.sh run api

# Run all components
./docker-run.sh run all
```

3. **Test Commands:**
```bash
# Run all tests
./docker-run.sh test
```

4. **Clean Commands:**
```bash
# Clean build artifacts and Docker cache
./docker-run.sh clean
```

#### Docker Development Workflow

1. Initial setup:
```bash
# Build the project
./docker-run.sh build

# Give execution permissions to scripts (if needed)
chmod +x scripts/*
```

2. Development cycle:
```bash
# Make changes to code

# Rebuild and run tests
./docker-run.sh build
./docker-run.sh test

# Run specific component
./docker-run.sh run [cpp|python|api]
```

3. API Development:
```bash
# Build and run API server
./docker-run.sh run api

# Test endpoints using curl commands (in another terminal)
# Use curl commands provided in the API Testing section above
```

4. Cleanup:
```bash
# Clean all build artifacts and Docker cache
./docker-run.sh clean
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
