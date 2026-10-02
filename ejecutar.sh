#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "${BASH_SOURCE[0]}")"
command -v mpicc >/dev/null || { echo 'Falta mpicc. En Ubuntu: sudo apt install openmpi-bin libopenmpi-dev'; exit 1; }
command -v mpirun >/dev/null || { echo 'Falta mpirun.'; exit 1; }
mkdir -p bin evidencias
exec > >(tee evidencias/ejecucion.txt) 2>&1
set -x
mpirun --version
mpicc -std=c11 -Wall -Wextra -Wpedantic -Werror Ejercicio1a.c -o bin/Ejercicio1a
mpicc -std=c11 -Wall -Wextra -Wpedantic -Werror Ejercicio1b.c -o bin/Ejercicio1b
mpirun --oversubscribe -np 4 ./bin/Ejercicio1a
mpirun --oversubscribe -np 4 ./bin/Ejercicio1b
