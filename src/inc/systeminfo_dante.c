#include "systeminfo_dante.h"
#define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>

size_t maxSz = 120;

/* Funciones privadas */
void getAdaptersInfo(char **dest){
  struct ifaddrs *ifaddr;
  int family, s;
  char host[NI_MAXHOST];

  if (getifaddrs(&ifaddr) == -1) {
    perror("getifaddrs");
    exit(EXIT_FAILURE);
  }

  static size_t adapterCount = 0;
  for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {

    char *msg, *aux;    
    size_t sz;

    family = ifa->ifa_addr->sa_family;
    if (ifa->ifa_addr == NULL || family == AF_PACKET || family == AF_INET6)
      continue;

    // obtener nombre y tipo del adaptador
    sz = snprintf(NULL, 0, "%-6s %s\n",
    ifa->ifa_name,
    (family == AF_INET) ? "ipv4 if:" : "???");
    msg = (char *)malloc(sz+1);
    snprintf(msg, sz+1, "%-6s %s\n",
    ifa->ifa_name,
    (family == AF_INET) ? "ipv4 if:" : "???");

    int sep = 15;

    if (family == AF_INET) {
      // obtener direccion ip
      s = getnameinfo(ifa->ifa_addr,
      sizeof(struct sockaddr_in),
      host, NI_MAXHOST,
      NULL, 0, NI_NUMERICHOST);
      
      if (s != 0) {
        printf("getnameinfo() failed: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
      }

      sz = snprintf(NULL, 0, "%*s %s\n", sep, "address:", host);
      aux = (char*)malloc(sz+1);
      snprintf(aux, sz+1, "%*s %s\n", sep, "address:", host);
      strcat(msg, aux);

      // obtener mascara subred
      s = getnameinfo(ifa->ifa_netmask,
      sizeof(struct sockaddr_in),
      host, NI_MAXHOST,
      NULL, 0, NI_NUMERICHOST);
      
      if (s != 0) {
        printf("getnameinfo() failed: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
      }

      sz = snprintf(NULL, 0, "%*s %s\n", sep, "netmask:", host);
      aux = (char*)malloc(sz+1);
      snprintf(aux, sz+1, "%*s %s\n", sep, "netmask:", host);
      strcat(msg, aux);
      
      // copiar informacion en destino
      memcpy(dest[adapterCount], msg, strlen(msg));
      adapterCount++;
      
      // liberar punteros creados dinamicamente
      free(msg);
      free(aux);
    }
  }
  
  // liberar puntero ifaddr
  freeifaddrs(ifaddr);
}


/* Funciones publicas */
int na_get_adaptersCount(){
  struct ifaddrs *ifaddr;
  int family;
  static int adaptersCount = 0;

  if (getifaddrs(&ifaddr) == -1) {
     perror("getifaddrs");
     exit(EXIT_FAILURE);
  }

  for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {

    family = ifa->ifa_addr->sa_family;
    if (ifa->ifa_addr == NULL || family == AF_PACKET || family == AF_INET6){
      continue;
    }else{
       adaptersCount++;
    }
  }
  freeifaddrs(ifaddr);

  return(adaptersCount);
}

void na_get_adaptersInfo(char **info, int len){
  if(info){
    for(size_t i=0; i<len; i++){
      info[i] = (char*)malloc(maxSz);
    }
    getAdaptersInfo(info);
  }else{
    printf("Error reservando memoria para info adaptadores de red\n");
    exit(EXIT_FAILURE);
  }
}

int cpu_get_lineCount(char *filePath){ 
  int size = 0;
  char *line = NULL;
  FILE *fptr = fopen(filePath, "r");
  
  if(fptr == NULL){
      printf("can't open file!\n");
      exit(EXIT_FAILURE);
  }
  while(getline(&line, &maxSz, fptr) != -1){
    size++;
  }
  fclose(fptr);
  
  return(size);
}

void cpu_get_info(char *filePath, char **info, int len){
  char *line = NULL;
  FILE *fptr = fopen(filePath, "r");
  
  if(info){
    if(fptr != NULL){
      for(size_t i=0; i<len; i++){
        info[i] = (char*)malloc(maxSz);
      }
      int i=0;
      while(getline(&line, &maxSz, fptr) != -1){
        strcpy(info[i], line);
        i++;
      }
    }else{
        printf("can't open file!\n");
        exit(EXIT_FAILURE);
    }  
  }else{
    printf("Error reservando memoria para info de cpu\n");
    exit(EXIT_FAILURE);
  }
}
