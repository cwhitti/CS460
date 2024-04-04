#include "sender_handler.c"

/*
Implements loop of listening for messages from server. Expects a pointer
to a socket as the argument.
Dependencies: parseMessage, writeMessageToSocket, scanf
*/
void* senderLoop(void* arg)
{
    
}

/*
Reads the string and attempts to interpret as a message, and writes data
to the given message structure. Returns true if successful, false if not
Dependencies: sscanf
*/
bool parseMessage(char* inString, Message* outMsg)
{
    return true;
}