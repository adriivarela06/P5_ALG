#!/bin/bash

OUTPUT_FILE="gnuplot/Datos/resultados_grafica.txt"
MAPA_TEMP="gnuplot/Datos/mapa_temp.txt"

echo -e "N\tTiempo(ms)" > "$OUTPUT_FILE"

for n in 50 100 200 300 400 500 600 800; do
    ./bin/generador "$n" "$MAPA_TEMP" 0.4
    ./bin/tiempos "$MAPA_TEMP" >> "$OUTPUT_FILE"
done

if [ -f "$MAPA_TEMP" ]; then
    rm "$MAPA_TEMP"
fi