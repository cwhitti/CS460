#include "chat_node.h"

/*
  Function: createChatNodeFromData

  Purpose: Takes client data and creates a node from it
*/
ChatNode* createChatNodeFromData( unsigned int ip, unsigned short int port,
                                                    char* name)
{
  // declare variables
  ChatNode *newNode;

  // allocate memory for newNode
  newNode = ( ChatNode* )malloc( sizeof( ChatNode ) );

  // set data pieces
  newNode -> ip = ip;
  newNode -> port = port;
  newNode -> name = name;

  return newNode; // return newNode
}


void deepCopyChatNode( ChatNode* destNode, ChatNode* srcNode)
{
  destNode -> ip = srcNode -> ip;
  destNode -> port = srcNode -> port;
  destNode -> name = srcNode -> name;
}
/*
  Function: initializeChatNodeList

  Purpose: Initializes list of chat nodes
*/
ChatNodes* initializeChatNodeList( void )
{
  // allocate memory for ChatNodeList struct

  /*
  EXAMPLE FROM CS249:

  StateLLType *newData;

  newData = ( StateLLType * )malloc( sizeof( StateLLType ) );

  newData -> headPtr = NULL;

  return newData;
  */

  ChatNodeList *newData;

  newData = ( ChatNodeList *)malloc( sizeof (ChatNodeList) );

  newData -> firstPtr = NULL;

  return newData; // temp stub
}

/*
  Function: addChatNodeToList

  Purpose: Adds a chatNode to a list
*/
void addChatNodeToList( ChatNodeList* chatNodeList, ChatNode* chatNode )
{
  // grab last item

  // set last item -> lastPtr to chatNode
}

/*
  Function: removeNodeFromList

  Purpose: Removes a chatNode to a list, returns success bool
*/
bool removeNodeFromList( ChatNodeList* chatNodeList, ChatNode *chatNode)
{
  // declare variables
  // ChatNode *temp, *parentNode;

  // check for chatNodeList

    // Special case: chatNode is first

    // Special case: chatNode is last

    // grab parent node
      // FUNCTION: removeNodeFromListHelper
      // parentNode = removeNodeFromListHelper(chatNodeList, chatNode, compareNode);

    // if parentNode != NULL

      // set  temp to parentNode -> next

      // set parentNode -> next = chatNode

      // free temp

      // return true

  return false; // temp stub
}

ChatNode* removeNodeFromListHelper( ChatNodeList* chatNodeList,
                                        ChatNode* parentNode,
                                            ChatNode *compareNode)
{
  // declare variables

  // iterate through list

    // grab child node

    // Check if childNode != NULL

      // If compare child ptr to cmpNode

        // return parentNode

      // increment wkgPtr

  // return NULL
  return NULL;

}

/*
  Function: compareChatNodes

  Purpose: Compares two chat nodes, returns success
*/
bool compareChatNodes( ChatNode* first, ChatNode* second )
{
  // compare name to name

  // compare ip to ip

  // compare port to port

  return false; // temp stub
}
