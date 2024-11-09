## Tests Automaticos
Como en cualquier proyecto, es necesario tener ciertas funciones de tests para comprobar que las funciones individuales funcionan y no volverse loco buscando el fallo. Para esto usamos la libreria gtest de google, con la cual podemos definir tests de manera sencilla. Además de eso, permite
integración en el makefile, de manera que si una modificacón en las funciones auxiliares, hace que un test falle, no se completará el compilado. Como esto solo funciona en las versiones de c++ por encima de la 14, esta opcion en el compilado es opcional. Para probarla es necesario ejecutar 
`make tests`

## En busca de memory leaks
Para asegurarnos de que no había ningún memory leak hemos usado valgrind, una herramienta que es capaz de buscar fallos de memoria en porgramas. La salida del siguiente comando: `valgrind --leak-check=full -s --show-leak-kinds=all target/main P3_entrada_salida_hendrix/entrada.txt`
Es la siguiente:
```
==408998== Memcheck, a memory error detector
==408998== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==408998== Using Valgrind-3.23.0 and LibVEX; rerun with -h for copyright info
==408998== Command: target/main P3_entrada_salida_hendrix/entrada.txt
==408998==
==408998==
==408998== HEAP SUMMARY:
==408998==     in use at exit: 0 bytes in 0 blocks
==408998==   total heap usage: 65 allocs, 65 frees, 93,253 bytes allocated
==408998==
==408998== All heap blocks were freed -- no leaks are possible
==408998==
==408998== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```
Con esto, somos capaces de saber que no estamos cometiendo ningún fallo de memoria en el programa.

## Comprobación del funcionamiento del programa
Para comprobar que el programa funciona, hemos creado un pequeño script que lo que hace es ejecutar el programa, hacer un diff de la salida esperada y la salida obtenida, y si el diff esta vacío 
confirma que el programa es correcto. En cualquier otro caso, se indica que el programa no es correcto, y muestra las diferencias obtenidas.
El script es el siguiente:
```bash
#!/bin/bash 

 function executeProgram(){
   make > /dev/null 2>&1
  target/main P3_entrada_salida_hendrix/entrada.txt
}

function findDiferencias(){
  local diferencias=$(diff P3_entrada_salida_hendrix/salida.txt salida.txt)
  if [[ $? -eq 0 ]]; then
    echo "El programa se ha ejecutado con exito!"
  else
    echo "Se han encontrado diferencias entre el fichero de entrada y de salida"
    echo "$diferencias"
  fi
}

function deleteShit(){
  rm salida.txt 
}

main(){
  executeProgram
  findDiferencias
  deleteShit
}

main
```

