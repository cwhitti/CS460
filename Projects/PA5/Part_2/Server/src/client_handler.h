#include "chat_node.h"
#include "message.h"

// structs
struct ThreadArgs
{
    void *clientSocket;
    ChatNodeList *clientList;
};

// join function
void clientJoin( ChatNodeList *clientList);

// leave function
void clientLeave( ChatNodeList *clientList );

// note function
void clientNote( ChatNodeList *clientList );

// shutdown function
void clientShutdown( ChatNodeList *clientList );

void get_ip_address(const char *string, char *ip_string);

// joining function
void globalJoining( ChatNodeList *clientList );

// leaving function
void globalLeaving( ChatNodeList *clientList );

// shutdownAll
void globalShutdown( ChatNodeList *clientList );

void* handle_client( void* args );
