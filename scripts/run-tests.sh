# scripts/run-tests.sh
#!/bin/bash
cd build
./test_quant_fin_lib
cd ..
export PYTHONPATH=$PYTHONPATH:$(pwd)
poetry run pytest python_bindings/tests/
