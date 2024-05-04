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

    char *msg, *aux, *destAux;    
    size_t sz;

    family = ifa->ifa_addr->sa_family;
    if (ifa->ifa_addr == NULL || family == AF_PACKET)
      continue;

    destAux = *(dest+adapterCount);

    // obtener nombre y tipo del adaptador
    sz = snprintf(NULL, 0, "%-6s %s (%d)\n",
    ifa->ifa_name,
    (family == AF_INET) ? "IPV4" :
    (family == AF_INET6) ? "IPV6" : "???",
    family);
    msg = (char *)malloc(sz+1);
    snprintf(msg, sz+1, "%-6s %s (%d)\n",
    ifa->ifa_name,
    (family == AF_INET) ? "IPV4" :
    (family == AF_INET6) ? "IPV6" : "???",
    family);

    int sep = 15;

    if (family == AF_INET || family == AF_INET6) {
      // obtener direccion ip
      s = getnameinfo(ifa->ifa_addr,
      (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
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
      (family == AF_INET) ? sizeof(struct sockaddr_in) :
      sizeof(struct sockaddr_in6),
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
    if (ifa->ifa_addr == NULL || family == AF_PACKET){
      continue;
    }else{
       adaptersCount++;
    }
  }

  return(adaptersCount);
}

void na_get_adaptersInfo(char **info, int len){
  const size_t maxSz = 120;
  
  if(info){
    for(size_t i=0; i<len; i++){
      info[i] = (char*)malloc(maxSz);
    }
    getAdaptersInfo(info);
    for(size_t i=0; i<len; i++){
      puts(info[i]);
    }
  }else{
    printf("Error reservando memoria para info adaptadores de red\n");
  }
}

