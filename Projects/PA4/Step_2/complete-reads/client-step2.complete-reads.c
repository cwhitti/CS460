/*
PA 4
Peter Hilbert
*/

#include "client-step2.complete-reads.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main()
{
  int client_number = 7;
  int task;
  pthread_t thread;

  for (task = 0; task <= NUM_TASKS; task++)
  {
    if (pthread_create(&thread, NULL, talk_to_server, (void*)&client_number) != 0)
      {
       printf("Error creating thread\n");
      }
  }

  sleep(5);

  return EXIT_SUCCESS;
}

void* talk_to_server(void* arg)
{
  int client_socket;                  // client side socket
  struct sockaddr_in client_address;  // client socket naming struct
  char ip_addr[INET_ADDRSTRLEN];
  int client_number = *(int*)arg;
  int server_number;
  int bytes_read;

  // get IP address of the common name server
  get_ip_address( SERVER_ADDR, ip_addr );

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

  printf("Number sent: %d\n", client_number);

  // convert client number to network order
  client_number = htonl(client_number);

  // send our number to the server
  write( client_socket, &client_number, sizeof(client_number) );

  // get the result
  bytes_read = read_int(client_socket, &server_number);

  server_number = htonl(server_number);

  if (bytes_read != 4)
  {
    printf("Incomplete read\n");
  }
  else
  {
    printf("Steps taken: %d\n", server_number);
  }

  pthread_exit(NULL);
}

int read_int(int socket, int* int_value_ptr)
{
  char ch1 = 0;
  char ch2 = 0;
  char ch3 = 0;
  char ch4 = 0;

  read( socket, &ch1, sizeof(char));
  read( socket, &ch2, sizeof(char));
  read( socket, &ch3, sizeof(char));
  read( socket, &ch4, sizeof(char));

  if (!ch1 && !ch2 && !ch3 && !ch4)
  {
    return -1;
  }

  *int_value_ptr = ntohl((int)((ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0)));
  return 4;
}

void get_ip_address(const char *string, char *ip_string)
{
  struct addrinfo *headPtr, *wkgPtr;
  struct sockaddr_in *ipv4 = NULL;
  void *addr;
  char temp[INET_ADDRSTRLEN];

  //hints.ai_family = AF_INET; // AF_INET means IPv4 only

  if ( getaddrinfo( string, NULL, NULL, &headPtr ) == 0 )
  {
    // Loop through all the results and get the IP address
    for (wkgPtr = headPtr; wkgPtr != NULL; wkgPtr = wkgPtr->ai_next)
    {
      ipv4 = (struct sockaddr_in *)wkgPtr->ai_addr;
      addr = &( ipv4->sin_addr );

      // Convert the IP to a string
      inet_ntop( wkgPtr->ai_family, addr, temp, sizeof temp);
    }

    // Free the linked list
    freeaddrinfo( headPtr );

    // Copy the IP address string
    strncpy(ip_string, temp, INET_ADDRSTRLEN);
  }
  else
  {
    perror("Error resolving nostname.");
    exit(EXIT_FAILURE);
  }
 }
