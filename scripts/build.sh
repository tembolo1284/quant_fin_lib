# scripts/build.sh
#!/bin/bash
cmake -B build -G Ninja
poetry install
