#ifndef CHAT_NODE_H
#define CHAT_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 16

// ChatNode w/ IP, Port, logical name
typedef struct chat_node_struct
{
  unsigned int ip;
  unsigned short int port;
  char name[NAME_LEN];
} ChatNode;

// ChatNodeListElement for building a list
typedef struct chat_node_list_element_struct
{
  ChatNode chat_node;
  struct chat_node_list_element_struct* next;
} ChatNodeListElement;

// ChatNodeList
typedef struct chat_node_list_struct
{
  ChatNodeListElement* firstPtr;
  // ChatNodeListElement* lastPtr;
} ChatNodeList;

// create chat node from given data
ChatNode* createChatNodeFromData( unsigned int ip, unsigned short int port,
                                                    char* name);

// create a chat node list
ChatNodeList* initializeChatNodeList( void );

void addChatNodeToList( ChatNodeList* chatNodeList, ChatNode* chatNode );
bool removeNodeFromList( ChatNodeList* chatNodeList, ChatNode *chatNode);

bool compareChatNodes( ChatNode* first, ChatNode* second );

#endif
