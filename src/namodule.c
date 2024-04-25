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

int main(int argc, char *argv[]){
   struct ifaddrs *ifaddr;
   int family, s;
   char host[NI_MAXHOST];

   if (getifaddrs(&ifaddr) == -1) {
       perror("getifaddrs");
       exit(EXIT_FAILURE);
   }

   for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {

       char *msg, *aux;    
       size_t sz;

       if (ifa->ifa_addr == NULL)
	   continue;

       family = ifa->ifa_addr->sa_family;
       if(family == AF_PACKET)
	   continue;

       sz = snprintf(NULL, 0, "%-6s %s (%d)\n",
              ifa->ifa_name,
              (family == AF_PACKET) ? "AF_PACKET" :
              (family == AF_INET) ? "IPV4" :
              (family == AF_INET6) ? "IPV6" : "???",
              family);

       msg = (char *)malloc(sz+1);
       snprintf(msg, sz+1, "%-6s %s (%d)\n",
              ifa->ifa_name,
              (family == AF_PACKET) ? "AF_PACKET" :
              (family == AF_INET) ? "IPV4" :
              (family == AF_INET6) ? "IPV6" : "???",
              family);

       int sep = 15;

       if (family == AF_INET || family == AF_INET6) {
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

	   puts(msg);
	   free(msg);
	   free(aux);

       }
   }

   freeifaddrs(ifaddr);
   exit(EXIT_SUCCESS);
}
