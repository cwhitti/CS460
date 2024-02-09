#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main()
{
  int client_socket;                  // client side socket
  struct sockaddr_in client_address;  // client socket naming struct
  char *ip_addr;
  char inString[HUGE_STR_LEN], outStr[HUGE_STR_LEN];

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
  read( client_socket, &inString, sizeof(inString) );

  // format string
  format_time( inString, outStr );

  // print to console
  printf( "%s\n", outStr );

  return EXIT_SUCCESS;
}

void copy_string( char *destStr, const char *srcStr )
  {
    // declare variables
    int index = 0;

    // loop thru string
    while( srcStr[ index ] != '\0' )
     {
      // copy char
      destStr[ index ] = srcStr[ index ];

      // increment index
      index++;
     }

    // add null char
    destStr[ index ] = '\0';
  }


void format_time(const char *string, char *outStr )
  {
   // declare variables
   struct tm tm; // Initialize struct tm with all zeros
   const char* contents_chopped = string + 1;
   char temp[HUGE_STR_LEN];

   // convert NIST to time variable
   strptime( contents_chopped + 6, "%y-%m-%d %H:%M:%S", &tm );

   // convert time variable to temp
   strftime( temp, sizeof( temp ), "%A, %B %d, %Y %H:%M:%S %Z", &tm );

   // copy string back to main
   copy_string( outStr, temp );
  }

char* get_ip_address(const char *string)
{
  // declare variables
   struct hostent *hp;
   struct in_addr ip_addr;

  /* call gethostbyname() with a host name. gethostbyname() returns a */
  /* pointer to a hostent struct or NULL.                             */
   hp = gethostbyname(string);

   if (!hp)
   {
      printf("%s was not resolved\n", string );
      exit( EXIT_FAILURE );
   }

  /* move h_addr to ip_addr. This enables conversion to a form        */
  /* suitable for printing with the inet_ntoa() function.             */
   ip_addr = *(struct in_addr *)(hp->h_addr);

   return inet_ntoa(ip_addr);
 }
