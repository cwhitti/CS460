#ifndef MESSAGE_H
#define MESSAGE_H

#include "chat_node.h"

typedef enum {
    JOIN = 0,
    LEAVE = 1,
    SHUTDOWN = 2,
    SHUTDOWN_ALL = 3,
    NOTE = 4,
    JOINING = 5,
    LEAVING = 6
} MessageType;

typedef char Note[64];

typedef struct messageStruct {
    MessageType messageType;
    ChatNode* messageSender;
    Note noteContent;
} Message;

/*
Returns a pointer to a new message, initialized with given data
Dependencies: createChatNodeFromChatNode
*/
Message* createMessageFromData(MessageType inMsgType,
                               ChatNode* inMsgSender,
                               Note inNoteContent);

/*
Returns a pointer to a new message, initialized with data
from another message
Dependencies: createMessageFromData
*/
Message* createMessageFromMessage(Message* inMsg);

/*
Reads data from the socket, expecting message data, and returns
pointer to new message
Dependencies: read, createMessageFromData, createChatNodeFromData
*/
Message* readMessageFromSocket(int socket);

/*
Reads data from the socket, expecting message data, and returns
pointer to new message
Dependencies: write, createMessageFromData, createChatNodeFromData
*/
void writeMessageToSocket(int socket, Message* outMsg);

#endif
