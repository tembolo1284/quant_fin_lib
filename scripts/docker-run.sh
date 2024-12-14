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
        docker run -v $(pwd):/app quant-fin bash -c "cd /app && cmake -B build -G Ninja && cmake --build build && ./build/bin/quant_fin_main"
        ;;
      python)
        docker run -v $(pwd):/app quant-fin bash -c "cd /app && poetry run python python_bindings/main.py"
        ;;
      api)
        docker run -v $(pwd):/app -p 8080:8080 quant-fin bash -c "cd /app && cmake -B build -G Ninja && cmake --build build && ./build/bin/api_server"
        ;;
      all)
        echo "Building and running all components..."
        docker run -v $(pwd):/app -p 8080:8080 quant-fin bash -c "cd /app && \
          cmake -B build -G Ninja && \
          cmake --build build && \
          ./build/bin/api_server"
        ;;
      *)
        echo "Usage: ./docker-run.sh run [cpp|python|api|all]"
        exit 1
        ;;
    esac
    ;;
  build-api)
    docker run -v $(pwd):/app quant-fin bash -c "\
      cd /app && \
      cmake -B build -G Ninja -DBUILD_API=ON && \
      cmake --build build"
    ;;
  *)
    echo "Usage: ./docker-run.sh [build|build-api|test|clean|run cpp|run python|run api|run all]"
    exit 1
    ;;
esac
