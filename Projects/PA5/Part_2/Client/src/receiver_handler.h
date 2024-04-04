// "Server" dependencies
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <netdb.h>

#include "message.h"

/*
Implements loop of listening for messages from server. Expects a pointer
to a socket as the argument.
Dependencies: readMessageFromSocket, printf
*/
void* receiverLoop(void* arg);

/*
Reads data from the socket, expecting message data, and returns
pointer to new message
Dependencies: read, createMessageFromData, createChatNodeFromData
*/
Message* readMessageFromSocket(int socket);