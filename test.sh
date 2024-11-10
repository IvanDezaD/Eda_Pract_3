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
