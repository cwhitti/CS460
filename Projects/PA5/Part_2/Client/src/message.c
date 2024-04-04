#include "message.h"

/*
Returns a pointer to a new message, initialized with given data
Dependencies: createChatNodeFromChatNode
*/
Message* createMessageFromData(MessageType* inMsgType, 
                               ChatNode inMsgSender,
                               Note inNoteContent)
{

}

/*
Returns a pointer to a new message, initialized with data
from another message
Dependencies: createMessageFromData
*/
Message* createMessageFromMessage(Message* inMsg)
{

}

/*
Reads data from the socket, expecting message data, and returns
pointer to new message
Dependencies: read, createMessageFromData, createChatNodeFromData
*/
Message* readMessageFromSocket(int socket)
{
    return NULL;
}

/*
Reads data from the socket, expecting message data, and returns
pointer to new message
Dependencies: write, createMessageFromData, createChatNodeFromData
*/
void writeMessageToSocket(int socket, Message* outMsg)
{

}
