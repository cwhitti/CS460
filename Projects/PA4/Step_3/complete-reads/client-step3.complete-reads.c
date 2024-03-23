/*
PA 4
Peter Hilbert
*/

#include "client-step3.complete-reads.h"

pthread_mutex_t mp = PTHREAD_MUTEX_INITIALIZER;

/************************************************************************
 * MAIN
 ************************************************************************/
int main()
{
  int task;

  pthread_mutex_init(&mp, NULL);
  pthread_mutex_lock(&mp);

  for (task = 1; task <= NUM_TASKS; task++)
  {
        pthread_t thread;
        if (pthread_create(&thread, NULL, talk_to_server, (void*)&task) != 0)
        {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }

        pthread_mutex_lock(&mp);

        // detach the thread so that we don't have to wait (join) with it to reclaim memory.
        // memory will be reclaimed when the thread finishes.
        if (pthread_detach(thread) != 0)
        {
            perror("Error detaching thread");
            exit(EXIT_FAILURE);
        }

	//sleep(1);
  }

  sleep(5);

  return EXIT_SUCCESS;
}

void* talk_to_server(void* arg)
{
  int client_socket;                  // client side socket
  struct sockaddr_in client_address;  // client socket naming struct
  char ip_addr[INET_ADDRSTRLEN];
  int server_number;
  int bytes_read;

  int client_number = *(int*)arg;

  pthread_mutex_unlock(&mp);

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
  bytes_read = read( client_socket, &server_number, sizeof(server_number) );

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
