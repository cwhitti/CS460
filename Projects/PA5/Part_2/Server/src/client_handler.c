// join function
void clientJoin( ChatNodeList *clientList, ChatNode* clientNode )
{
  // add client to clientList
    // function: addChatNodeToList

  // send join message to all clients
    // function: globalJoining()
}

// leave function
void clientLeave( ChatNodeList *clientList, ChatNode* clientNode )
{
  // client will stop receiving, can still send JOIN message

  // remove chat node
    // function: removeNodeFromList

  // send
    // function: globalLeaving()
}

// note function
void clientNote( ChatNodeList *clientList, ChatNode* clientNode, Note *outStr )
{
  // declare variables

  // loop through clientList

    // if the current client != clientNode
    // function: compareChatNodes()

      // send message to everyone
        // function: writeMessageToSocket( note )
}

// shutdown function
void clientShutdown( ChatNodeList *clientList, ChatNode* clientNode )
{
  // declare variables

  // loop thrpugh clientList

    // check if currentNode == clientNode

      // Send client shutdown message
        // function: writeMessageToSocket

      // remove chat node

    // otherwise

      // send message to everyone that client left

        // function: globalLeaving()

  // terminate connection with client
}

void get_ip_address(const char *string, char *ip_string)
{

}

// joining function
void globalJoining( ChatNodeList *clientList, ChatNode *clientNode )
{
  // push [USER JOIN] message to all clients
}

// leaving function
void globalLeaving( ChatNodeList *clientList, ChatNode *clientNode )
{

  // push [USER LEAVE] message to all clients

}

void globalShutdown( ChatNodeList *clientList, ChatNode *clientNode )
{

}

void* handle_client( void* args )
{
  // initialize variables
  // struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;

  // grab client socket
  // grab clientList

  // read entire message from socket, returns pointer to new msg struct
    // function: readMessageFromSocket( )

  // process depending on MessageType

    //  JOIN

      // function: clientJoin()

    //  LEAVE

      // function: clientLeave()

    //  SHUTDOWN

      // function: clientShutdown()

    //  SHUTDOWN_ALL

      // function: globalShutdown()

    //  NOTE

      // function: clientNote()

    //  JOINING

      // function: globalJoining()

    //  LEAVING

      // function: globalLeaving()

}
