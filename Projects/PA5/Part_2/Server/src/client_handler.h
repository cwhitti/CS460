#include "chat_node.h"
#include "message.h"

// structs
struct ThreadArgs
{
    int clientSocket;
    ChatNodeList *clientList;
};

// join function
void clientJoin( ChatNodeList *clientList, ChatNode *clientNode );

// leave function
void clientLeave( ChatNodeList *clientList, ChatNode *clientNode );

// note function
void clientNote( ChatNodeList *clientList, ChatNode *clientNode, Note *outStr );

// shutdown function
void clientShutdown( ChatNodeList *clientList, ChatNode *clientNode );

void get_ip_address(const char *string, char *ip_string);

// joining function
void globalJoining( ChatNodeList *clientList, ChatNode *clientNode );

// leaving function
void globalLeaving( ChatNodeList *clientList, ChatNode *clientNode );

// shutdownAll
void globalShutdown( ChatNodeList *clientList, ChatNode *clientNode );

void* handle_client( void* args );
