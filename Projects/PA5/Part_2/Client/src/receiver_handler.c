#include "receiver_handler.h"

/*
Implements loop of listening for messages from server. Expects a pointer
to a socket as the argument.
Dependencies: readMessageFromSocket, printf
*/
void* receiverLoop(void* arg)
{
    // cast argument to ChatNode**

    // extract my chat node

    // set up a socket with my chat node info and start listening

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

