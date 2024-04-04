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
  newData -> lastPtr = NULL;

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
  ChatNode *temp, *parentNode;

  // check for chatNodeList
  if ( chatNodeList != NULL )
  {
    // grab parent node
      // FUNCTION: removeNodeFromListHelper
    parentNode = removeNodeFromListHelper(chatNodeList, chatNode, compareNode);

    // if parentNode != NULL

      // remove child
  }

  return false; // temp stub
}

ChatNode* removeNodeFromListHelper( ChatNodeList* chatNodeList,
                                        ChatNode* parentNode,
                                          ChatNode *compareNode)
{
  // declare variables

  // iterate through list

    // 

    //


}

/*
  Function: compareChatNodes

  Purpose: Compares two chat nodes, returns success
*/
bool compareChatNodes( ChatNode* first, ChatNode* second )
{
  return false; // temp stub
}
