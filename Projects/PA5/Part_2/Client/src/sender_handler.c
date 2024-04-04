/*
Reads data from the socket, expecting message data, and returns
pointer to new message
Dependencies: write, createMessageFromData, createChatNodeFromData
*/
void writeMessageToSocket(int socket, Message* outMsg)
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