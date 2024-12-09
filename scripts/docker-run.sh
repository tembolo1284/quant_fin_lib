#!/bin/bash
case $1 in
  build)
    docker build -t quant-fin .
    # Clean the build directory first
    rm -rf build/
    # Now run with the correct paths
    docker run -v $(pwd):/app quant-fin bash -c "cd /app && ./scripts/build.sh"
    ;;
  test)
    docker run -v $(pwd):/app quant-fin bash -c "cd /app && ./scripts/run-tests.sh"
    ;;
  clean)
    docker run -v $(pwd):/app quant-fin bash -c "cd /app && rm -rf build/ && find . -type d -name **pycache** -exec rm -r {} +"
    docker system prune -f
    ;;
  run)
    case $2 in
      cpp)
        docker run -v $(pwd):/app quant-fin bash -c "cd /app && cmake -B build -G Ninja && cmake --build build && ./build/quant_fin_main"
        ;;
      python)
        docker run -v $(pwd):/app quant-fin bash -c "cd /app && poetry run python python_bindings/main.py"
        ;;
      *)
        echo "Usage: ./docker-run.sh run [cpp|python]"
        exit 1
        ;;
    esac
    ;;
  *)
    echo "Usage: ./docker-run.sh [build|test|clean|run cpp|run python]"
    exit 1
    ;;
esac
