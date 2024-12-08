#!/bin/bash
apt-get update && apt-get install -y libgtest-dev ninja-build
cmake -B build -G Ninja
cmake --build build
export PATH="/root/.local/bin:$PATH"
poetry install
