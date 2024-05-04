#include <stdio.h>
#include <stdlib.h>
#include "inc/systeminfo_dante.h"

int main(int argc, char *argv[]){
  int adapterqty = na_get_adaptersCount();
  char **adaptersInfo = malloc(sizeof(char *) * adapterqty);
  
  na_get_adaptersInfo(adaptersInfo, adapterqty);
  
  return(0);
}
