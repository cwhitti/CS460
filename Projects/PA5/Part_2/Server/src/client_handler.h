#include "chat_node.h"
#include "message.h"

// structs
struct ThreadArgs
{
    int clientSocket;
    ChatNodeList *clientList;
};

// join function
void clientJoin( ChatNodeList *clientList, Message* messageObj );

// leave function
void clientLeave( ChatNodeList *clientList, Message* messageObj );

// note function
void clientNote( ChatNodeList *clientList, Message* messageObj );

// general forward message function
void forwardMessage( ChatNodeList *clientList, Message* messageObj )

// joining function
void globalJoining( ChatNodeList *clientList, Message* messageObj );

// leaving function
void globalLeaving( ChatNodeList *clientList, Message* messageObj );

// shutdownAll
void globalShutdown( ChatNodeList *clientList, Message* messageObj );

void* handle_client( void* args );
