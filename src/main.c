#include <stdio.h>
#include <stdlib.h>
#include "inc/systeminfo_dante.h"

const char* filePath = "/var/www/htmlUpdate";
const char* updaterPath = "/updateHtml.sh";

void printInfo(char **info, int len){
  for(size_t i=0; i<len; i++){
        puts(info[i]);
  }
}

void saveToFile(FILE *fptr, char **data, int len){
  for(int i=0; i<len; i++){
    fprintf(fptr, "%s\n", data[i]);
  }
}

void liberarPunteros(char **ptr, int len){
  for(int i=0; i<len; i++){
    free(ptr[i]);
  }
  free(ptr);
}

int main(int argc, char *argv[]){
  int adapterqty = na_get_adaptersCount();
  int cpuinfolc = cpu_get_lineCount("/proc/cpuinfo");
  char **adaptersInfo = malloc(sizeof(char *) * adapterqty);
  char **cpuinfo = malloc(sizeof(char *) * cpuinfolc);
  FILE *updateHtml_ptr;
  
  // obtener informacion placa de red y guardarla en filePath
  na_get_adaptersInfo(adaptersInfo, adapterqty);
  printInfo(adaptersInfo, adapterqty);
  updateHtml_ptr = fopen(filePath, "w+");
  if(!updateHtml_ptr){
    printf("Error en lectura/creación archivo updateHtml\n");
    exit(EXIT_FAILURE);
  }
  saveToFile(updateHtml_ptr, adaptersInfo, adapterqty);
  fclose(updateHtml_ptr);
  
  // obtener informacion de cpuinfo y guardarla en filepath
  cpu_get_info("/proc/cpuinfo", cpuinfo, cpuinfolc);
  printInfo(cpuinfo, cpuinfolc);
  updateHtml_ptr = fopen(filePath, "a");
  if(!updateHtml_ptr){
    printf("Error en lectura/creación archivo updateHtml\n");
    exit(EXIT_FAILURE);
  }
  saveToFile(updateHtml_ptr, cpuinfo, cpuinfolc);
  fclose(updateHtml_ptr);
  
  // liberar memoria alojada dinamicamente
  liberarPunteros(adaptersInfo, adapterqty);
  liberarPunteros(cpuinfo, cpuinfolc);
  
  // correr script para actualizar index.html
  system(updaterPath);

  // leer periodicamente sensor y enviar lectura por puerto serie
  
  
  return(0);
}
