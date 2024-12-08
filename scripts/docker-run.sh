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
 run)
   case $2 in
     cpp)
       docker run -v $(pwd):/app quant-fin ./build/quant_fin_main
       ;;
     python)
       docker run -v $(pwd):/app quant-fin poetry run python python_bindings/main.py
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
