#include "sender_handler.c"

/*
Implements loop of listening for messages from server. Expects a pointer
to a socket as the argument.
Dependencies: parseMessage, writeMessageToSocket, scanf
*/
void* senderLoop(void* arg)
{   
    // get arguments from struct

    // initialize message

    // set message chat node to my chat node
        // function: deepCopyChatNode

    // loop until message is a SHUTDOWN or SHUTDOWN_ALL

        // read string from command line
            // function: scanf

        // write data from string to message struct, check for success
            // function: parseMessage

            // if successful, then write the message to the server
                // function: writeMessageToServer

    // exit thread
        // function: pthread_exit
}

/*
Reads the string and attempts to interpret as a message, and writes data
to the given message structure, specifically the message type and note contents.
Returns true if successful, false if not
Dependencies: sscanf
*/
bool parseMessage(char* inString, Message* outMsg)
{
    
    // get the first and second "word" from the string
        // function: sscanf

    // check for JOIN keyword in first word

        // update messageType of outMsg

    // check for LEAVE keyword in first word

        // update messageType of outMsg

    // check for SHUTDOWN keyword in first word

        // check for second word is ALL keyword

            // update messageType of outMsg

        // otherwise, assume just SHUTDOWN

            // update messageType of outMsg

    // otherwise, assume message is a NOTE

        // update messageType of outMsg

        // update Note field of outMsg
            // function: strcpy

    return true;
}