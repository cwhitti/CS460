typedef enum {
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
    message_type messageType;
    chat_node* messageSender;
    note noteContent;
} Message;

/*
Returns a pointer to a new message, initialized with given data
Dependencies: createChatNodeFromChatNode
*/
Message* createMessageFromData(MessageType; inMsgType, 
                               ChatNode inMsgSender,
                               Note inNoteContent);

/*
Returns a pointer to a new message, initialized with data
from another message
Dependencies: createMessageFromData
*/
Message* createMessageFromMessage(Message* inMsg);