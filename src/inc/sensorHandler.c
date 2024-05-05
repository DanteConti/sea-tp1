#include "sensorHandler.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* Funciones publicas */
float sensorGet(const char *filepath){
  FILE* fptr = fopen(filepath, "r");
  size_t maxSize = 10;
  char *line = (char *)malloc(maxSize * sizeof(char)); 
  float res;

  getline(&line, &maxSize, fptr);
  res=(atof(line)/1000.0);
  free(line);
  fclose(fptr);
  
  return(res);
}

void serialWrite(const char *filepath, float value, char *decorator){
  FILE *fptr = fopen(filepath, "w");

  if(decorator == NULL){
    fprintf(fptr, "%.3f\n", value);
  }else{
    fprintf(fptr, "%.3f %s\n", value, decorator);
  }

  fclose(fptr);
}
