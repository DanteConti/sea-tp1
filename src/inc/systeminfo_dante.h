#ifndef __SYSTEMINFODANTE__
#define __SYSTEMINFODANTE__

#include <stdlib.h>

int na_get_adaptersCount(void);
void na_get_adaptersInfo(char**,int);
int cpu_get_lineCount(char*);
void cpu_get_info(char*,char**,int);

#endif
