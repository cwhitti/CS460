#include "message.h"

/*
Returns a pointer to a new message, initialized with given data
Dependencies: createChatNodeFromChatNode
*/
Message* createMessageFromData(MessageType inMsgType, 
                               ChatNode* inMsgSender,
                               Note inNoteContent)
{
    Message* newMessage = (Message*)malloc(sizeof(Message));
    newMessage->messageType = inMsgType;
    deepCopyChatNode(&(newMessage->messageSender), inMsgSender);
    strncpy((char*)&(newMessage->noteContent), (char*)inNoteContent, NOTE_LEN);
    newMessage->noteContent[NOTE_LEN] = NULL_CHAR;

    return newMessage;
}

/*
Returns a pointer to a new message, initialized with data
from another message
Dependencies: createMessageFromData
*/
Message* createMessageFromMessage(Message* inMsg)
{
    return createMessageFromData(inMsg->messageType,
                                 &(inMsg->messageSender),
                                 inMsg->noteContent);
}

/*
Reads data from the socket, expecting message data, and returns
pointer to new message, returns NULL if there was a network error
Dependencies: completeRead, createMessageFromData, createChatNodeFromData
*/
Message* readMessageFromSocket(int socket)
{
    int inMsgType;
    unsigned int inIp;
    unsigned short int inPort;
    char inName[NAME_LEN];
    Note inNote;

    ChatNode* newChatNode;
    Message* newMessage;

    // read all raw data
    completeRead(socket, (void*)&inMsgType, sizeof(inMsgType));
    completeRead(socket, (void*)&inIp, sizeof(inIp));
    completeRead(socket, (void*)&inPort, sizeof(inPort));
    completeRead(socket, (void*)inName, NAME_LEN);
    completeRead(socket, (void*)inNote, NOTE_LEN);

    // convert raw data into data structures
    newChatNode = createChatNodeFromData(inIp, inPort, inName);
    newMessage = createMessageFromData(inMsgType, newChatNode, inNote);

    // return new message
    return newMessage;
}

/*
Helper function to ensure complete reads
Dependencies: read
*/
int completeRead(int socket, void* buffer, unsigned int size)
{
    ssize_t bytesRead = 0;
    ssize_t bytesReadAll = 0;
    char* bufferPtr = buffer;

    do
    {
        bytesRead = read(socket, bufferPtr, size);

        if (bytesRead == -1)
        {
            // network error
            return -1;
        }
        else
        {
            size -= (int)bytesRead;
            bufferPtr += bytesRead;
            bytesReadAll += bytesRead;
        }
    } while (size != 0);
    
    return (int)bytesReadAll;
}

/*
Reads data from the socket, expecting message data, and returns
pointer to new message
Dependencies: write
*/
void writeMessageToSocket(int socket, Message* outMsg)
{
    // write message type
    write(socket, &(outMsg->messageType), sizeof(outMsg->messageType));

    // write chat node info
    write(socket, &(outMsg->messageSender.ip), sizeof(outMsg->messageSender.ip));
    write(socket, &(outMsg->messageSender.port), sizeof(outMsg->messageSender.port));
    write(socket, &(outMsg->messageSender.name), NAME_LEN);

    // write note content
    write(socket, &(outMsg->noteContent), NOTE_LEN);
}
