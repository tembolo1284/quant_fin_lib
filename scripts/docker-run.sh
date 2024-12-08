# docker-run.sh
#!/bin/bash

case $1 in
  build)
    docker build -t quant-fin .
    docker run -v $(pwd):/app quant-fin ./scripts/build.sh
    ;;
  test)
    docker run -v $(pwd):/app quant-fin ./scripts/run-tests.sh
    ;;
  clean)
    docker run -v $(pwd):/app quant-fin ./scripts/clean.sh
    ;;
  *)
    echo "Usage: ./docker-run.sh [build|test|clean]"
    exit 1
    ;;
esac
