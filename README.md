# CC3069 — Ejercicio de Open MPI

Ejercicio de recolección de temperaturas y consumo eléctrico con cuatro procesos.

## Archivos

- `Ejercicio1a.c`: reúne dos temperaturas por proceso mediante una llamada a `MPI_Gather`.
- `Ejercicio1b.c`: calcula consumo total, máximo y mínimo mediante `MPI_Reduce`.
- `Analisis_MPI.pdf`: análisis de parámetros, respuestas y capturas de compilación y ejecución.
- `evidencias/`: capturas reales y registro de ejecución.
- `ejecutar.sh`: compila y ejecuta ambos programas en Ubuntu o WSL2.

## Ejecución

Con Open MPI y GCC instalados, ejecutar desde la carpeta del repositorio:

```bash
bash ejecutar.sh
```

Se utilizan cuatro procesos. El orden de los mensajes locales puede variar.

## Resultados

Gather reúne las mediciones 24.5, 25.0, 26.1, 26.4, 23.8, 24.1, 27.0 y 27.3 °C, agrupadas por rank.

Reduce obtiene:

- Consumo total: 550 kWh.
- Consumo máximo: 180 kWh.
- Consumo mínimo: 100 kWh.

## Video de explicación

**Pendiente de publicación.** El enlace al video de explicación de `MPI_Gather` y `MPI_Reduce` se añadirá en esta sección al finalizar la grabación.
