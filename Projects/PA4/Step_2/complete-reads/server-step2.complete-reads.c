/*
PA 4
Peter Hilbert
*/

#include "server-step2.complete-reads.h"


/* ************************************************************************* */
/* MAIN                                                                      */
/* ************************************************************************* */

int main(int argc, char** argv)
{
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    int yes = 1;


    // ----------------------------------------------------------
    // ignore SIGPIPE, sent when client disconnected
    // ----------------------------------------------------------
    signal(SIGPIPE, SIG_IGN);

    // ----------------------------------------------------------
    // create unnamed network socket for server to listen on
    // ----------------------------------------------------------
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // lose the pesky "Address already in use" error message
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // ----------------------------------------------------------
    // bind the socket
    // ----------------------------------------------------------
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on

    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // ----------------------------------------------------------
    // listen on the socket
    // ----------------------------------------------------------
    if (listen(server_socket, NUM_CONNECTIONS) != 0)
    {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    // ----------------------------------------------------------
    // server loop
    // ----------------------------------------------------------
    while (TRUE)
    {

        // accept connection to client
        int client_socket = accept(server_socket, NULL, NULL);
        //printf("\nServer with PID %d: accepted client\n", getpid());

        // create thread to handle the client's request
        // note that this is a naive approach, i.e. there are race conditions
        // for now this is okay, assuming low load
        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, (void*)&client_socket) != 0)
        {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }

        // detach the thread so that we don't have to wait (join) with it to reclaim memory.
        // memory will be reclaimed when the thread finishes.
        if (pthread_detach(thread) != 0)
        {
            perror("Error detaching thread");
            exit(EXIT_FAILURE);
        }
    }
}


/* ************************************************************************* */
/* handle client                                                             */
/* ************************************************************************* */

void* handle_client(void* arg)
{
    int client_socket = *((int*)arg);   // the socket connected to the client
    int client_number, steps_taken;
    
    // get number from client
    //read(client_socket, &client_number, sizeof(client_number));

    read_int(client_socket, &client_number);

    printf("Number received: %d\n", client_number);

    steps_taken = threea_plus_one(client_number);

    printf("Steps taken: %d\n", steps_taken);

    // put the out number into network order
    steps_taken = htonl(steps_taken);

    // for now, send the same number back to the client
    if (write(client_socket, &steps_taken, sizeof(steps_taken)) == 0)
        {
         printf("Error writing\n");
        }

    // cleanup
    if (close(client_socket) == -1)
    {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Closed socket to client, exit\n");
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

  *int_value_ptr = (int)((ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0));
  return 4;
}

int threea_plus_one(int num)
{
    int steps = 0;

    while (num != 1)
    {
        if (num % 2 == 0)
        {
            num = num / 2;
        }
        else
        {
            num = 3 * num + 1;
        }

        steps++;
    }

    return steps;
}
