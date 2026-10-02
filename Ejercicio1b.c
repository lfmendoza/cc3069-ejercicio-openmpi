/*----------------------------------------------------------------------
 * Universidad del Valle de Guatemala
 * Curso:     CC3069 - Computacion Paralela y Distribuida
 * Ejercicio: Ejercicio30Septiembre - Introduccion a Open MPI
 * Descripcion: simulacion del calculo del consumo electrico
 *              de las diferentes sucursales.
 *
 *              Cada proceso MPI representa una ubicacion diferente.
 *              Cada proceso registra su consumo electrico local y
 *              la Oficina Central obtiene total, maximo y minimo con
 *              MPI_Reduce().
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    int size;
    int consumo;
    int consumo_total;
    int consumo_maximo;
    int consumo_minimo;

    // Inicializa el entorno MPI
    MPI_Init(&argc, &argv);

    // Obtener el identificador del proceso actual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtener el numero total de procesos que participan
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Este ejercicio requiere exactamente 4 procesos
    if (size != 4) {

        if (rank == 0) {
            printf("Este programa requiere exactamente 4 procesos.\n");
        }

        MPI_Finalize();
        return 1;
    }

    // Cada proceso registra su consumo electrico
    if (rank == 0) {
        consumo = 150;
    } else if (rank == 1) {
        consumo = 120;
    } else if (rank == 2) {
        consumo = 180;
    } else {
        consumo = 100;
    }

    printf("Proceso %d: consumo = %d kWh\n", rank, consumo);

    // Sumar los consumos de todos los procesos
    MPI_Reduce(
        &consumo,
        &consumo_total,
        1,
        MPI_INT,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    // Todos los procesos participan en las tres reducciones, en el mismo orden.
    MPI_Reduce(&consumo, &consumo_maximo, 1, MPI_INT,
               MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&consumo, &consumo_minimo, 1, MPI_INT,
               MPI_MIN, 0, MPI_COMM_WORLD);

    // Solo rank 0 utiliza los resultados recibidos.
    if (rank == 0) {
        printf("\nConsumo total: %d kWh\n", consumo_total);
        printf("Consumo maximo: %d kWh\n", consumo_maximo);
        printf("Consumo minimo: %d kWh\n", consumo_minimo);
    }

    // Finaliza correctamente el entorno MPI
    MPI_Finalize();

    return 0;
}
