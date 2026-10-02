/*----------------------------------------------------------------------
 * Universidad del Valle de Guatemala
 * Curso:     CC3069 - Computacion Paralela y Distribuida
 * Ejercicio: Ejercicio30Septiembre - Introduccion a Open MPI
 * Descripcion: simulacion de la recoleccion de temperaturas
 *              registradas en diferentes sucursales.
 *
 *              Cada proceso MPI representa una ubicacion diferente:
 *                  rank 0 -> Oficina central
 *                  rank 1 -> Sucursal 1
 *                  rank 2 -> Sucursal 2
 *                  rank 3 -> Sucursal 3
 *
 *              Cada proceso registra dos temperaturas locales y la
 *              Oficina Central recopila todos los valores utilizando
 *              MPI_Gather().
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    int size;
    float temperatura[2];
    float temperaturas[8];

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

    // Dos mediciones por ubicacion; cada proceso conserva su par local.
    if (rank == 0) {
        temperatura[0] = 24.5f;
        temperatura[1] = 25.0f;
    } else if (rank == 1) {
        temperatura[0] = 26.1f;
        temperatura[1] = 26.4f;
    } else if (rank == 2) {
        temperatura[0] = 23.8f;
        temperatura[1] = 24.1f;
    } else {
        temperatura[0] = 27.0f;
        temperatura[1] = 27.3f;
    }

    printf("Proceso %d: temperaturas registradas = %.1f C, %.1f C\n",
           rank, temperatura[0], temperatura[1]);

    // Reunir las temperaturas de todos los procesos en rank 0
    MPI_Gather(
        temperatura,
        2,
        MPI_FLOAT,
        temperaturas,
        2,
        MPI_FLOAT,
        0,
        MPI_COMM_WORLD
    );

    // La Oficina Central muestra todas las temperaturas recibidas
    if (rank == 0) {

        printf("\nOficina Central: temperaturas recibidas\n");

        for (int i = 0; i < size; i++) {
            // Gather guarda los pares en orden de rank.
            printf("Proceso %d: %.1f C, %.1f C\n",
                   i, temperaturas[2 * i], temperaturas[2 * i + 1]);
        }
    }

    // Finaliza correctamente el entorno MPI
    MPI_Finalize();

    return 0;
}
