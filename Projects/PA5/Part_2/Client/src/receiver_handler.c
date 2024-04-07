#include "receiver_handler.h"

/*
Implements loop of listening for messages from server. Expects a pointer
to a socket as the argument.
Dependencies: readMessageFromSocket, printf
*/
void* receiverLoop(void* arg)
{
    // receiver loop

        // accept a new connection from server

        // read message from server
            // function: readMessageFromSocket

        // close socket

        // process depending on message type:

            // JOINED: print join message
                // function: printJoinMessage

            // LEAVING: print leaving message
                // function: printLeaveMessage

            // NOTE: print note
                // function: printNote

            // SHUTDOWN: exit the receiver
                // function: pthread_exit
}

