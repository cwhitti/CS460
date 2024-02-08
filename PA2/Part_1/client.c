#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main() {
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    char *ip_addr;
    char string[256];
    int index = 0;

    // get IP address of the common name server
    ip_addr = get_ip_address( SERVER_ADDR );

    // create an unnamed socket, and then name it
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // create addr struct
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(ip_addr);
    client_address.sin_port = htons(PORT);

    // connect to server socket
    if (connect(client_socket, (struct sockaddr *)&client_address,
                                              sizeof(client_address)) == -1)
    {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }

    // get the result
    read(client_socket, &string, sizeof(string));

    while ( string[index] != ASTERISK )
    {
      printf("%c", string[index] );
      index = index + 1;
    }

    printf("\n");

    return EXIT_SUCCESS;
}

char* get_ip_address(const char *string)
{
   struct hostent *hp;
   struct in_addr ip_addr;

  /* call gethostbyname() with a host name. gethostbyname() returns a */
  /* pointer to a hostent struct or NULL.                             */
   hp = gethostbyname(string);

   if (!hp) {
      printf("%s was not resolved\n", string );
      exit(EXIT_FAILURE);
   }

  /* move h_addr to ip_addr. This enables conversion to a form        */
  /* suitable for printing with the inet_ntoa() function.             */

   ip_addr = *(struct in_addr *)(hp->h_addr);
   //printf("Hostname: %s, was resolved to: %s\n", string, inet_ntoa(ip_addr));

   return inet_ntoa(ip_addr);
 }
