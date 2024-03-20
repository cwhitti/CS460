/*
PA 4
Peter Hilbert
*/

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <netdb.h>
// added libraries //
#include <time.h>
#include <string.h>

/* Function prototypes */
void* handle_client(void* arg);
void get_current_time( char *outStr );
void get_ip_address(const char *string, char *ip_string);
int threea_plus_one(int num);

/* Preprocessor directives */
#define THIS_ADDR "hwsrv-1126936.hostwindsdns.com"
#define PORT 1103

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 5       // number of pending connections in the connection queue

#define ASTERISK '*'
#define NULL_CHAR '\0'
#define BUFFER_SIZE 1024
#define HUGE_STR_LEN 256
