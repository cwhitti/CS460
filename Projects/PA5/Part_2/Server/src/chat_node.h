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



void          addChatNodeToList( ChatNodeList* chatNodeList, ChatNode* chatNode );

ChatNodeList* clearChatNodeList( ChatNodeList* list );
ChatNodeList* clearChatNodeListHelper( ChatNode *wkgPtr );
bool          compareChatNodes( ChatNode* first, ChatNode* second );
ChatNode*     createChatNodeFromData( unsigned int ip, unsigned short int port,char* name);

void          deepCopyChatNode( ChatNode* destNode, ChatNode* srcNode);

ChatNodeList* initializeChatNodeList( void );

int           privateCompareStrings( const char *leftStr, const char *rightStr );
int           privateGetStringLen( const char *str );

bool          removeNodeFromList( ChatNodeList* chatNodeList, ChatNode *chatNode);
ChatNode*     removeNodeFromListHelper( ChatNode* parentNode, ChatNode *compareNode );


#endif
