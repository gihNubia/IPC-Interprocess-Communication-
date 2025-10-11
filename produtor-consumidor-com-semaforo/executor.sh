#!/bin/bash

# Arquivo de saída
output_file="output.txt"
> "$output_file"

# Loop para X, Y, Z de 0 a 10
for X in {1..5}; do
    for Y in {1..5}; do
        for Z in {1..5}; do
            last_line=$(./index "$X" "$Y" "$Z" | tail -n 1)
            echo "$X $Y $Z"
            echo "index $X $Y $Z $last_line" >> "$output_file"
        done
    done
done

echo "Execução completa. Resultados em $output_file"