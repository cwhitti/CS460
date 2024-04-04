#include "chat_node.h"

typedef enum messageTypeEnum {
    JOIN = 0,
    LEAVE,
    SHUTDOWN,
    SHUTDOWN_ALL,
    NOTE,
    JOINING,
    LEAVING
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
