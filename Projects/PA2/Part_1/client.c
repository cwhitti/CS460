#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main() {
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    char *ip_addr;
    char string[HUGE_STR_LEN];

    // get IP address of the common name server
    ip_addr = get_ip_address( SERVER_ADDR );

    // create an unnamed socket, and then name it
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // create addr structhiii sxadsafasd
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
    read( client_socket, &string, sizeof(string) );

    //    printf("%s\n", string);

    format_time( string );

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

void format_time(const char *string )
 {
  struct tm tm = {0}; // Initialize struct tm with all zeros
  const char* contents_chopped = string + 1;

  // Extract and parse date and time string
  strptime(contents_chopped+6, "%y-%m-%d %H:%M:%S", &tm);

  //printf("%s\n", string);

 // Convert to desired format
  char formatted_time[50];
  strftime(formatted_time, sizeof(formatted_time), "%A, %B %d, %Y %H:%M:%S %Z", &tm);

  // Output formatted time
  printf("Formatted time: %s\n", formatted_time);

 }

void copyString( char *destStr, const char *srcStr )
   {
    int index = 0;

    while( srcStr[ index ] != NULL_CHAR )
       {
        destStr[ index ] = srcStr[ index ];

        index++;
       }
    destStr[ index ] = NULL_CHAR;
   }
