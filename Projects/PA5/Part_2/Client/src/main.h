#include <pthread.h>

#include "receiver_handler.h"
#include "sender_handler.h"
#include "properties.h"

#define NUM_CONNECTIONS 20

typedef struct senderArgsStruct
{
    int sendingSocket;
    ChatNode* myChatNode;
} SenderArgs;