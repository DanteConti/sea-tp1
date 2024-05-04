#include "sensorHandler.h"
#include <string.h>
#include <stdio.h>

/* Funciones publicas */
float getHumidity(char *filepath){
  FILE* fptr = fopen(filepath, "r");
  char *line;
  
  getline(&line, 10, fptr);
  fclose(fptr);
  
  return(atof(line)/100.0);
}
