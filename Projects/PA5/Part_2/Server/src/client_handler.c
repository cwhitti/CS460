// join function
void clientJoin( ChatNodeList *clientList )
{

  // Add new chat node to linked list

}

// leave function
void clientLeave( ChatNodeList *clientList )
{

  // client will stop receiving, can still send JOIN message

  // remove chat node

}

// note function
void clientNote( ChatNodeList *clientList )
{

  // push notes to all clients

}

// shutdown function
void clientShutdown( ChatNodeList *clientList )
{
  // client will stop sending or receiving

  // remove chat node

  // terminate connection with client
}

void get_ip_address(const char *string, char *ip_string)
{

}

// joining function
void globalJoining( ChatNodeList *clientList )
{
  // push [USER JOIN] message to all clients
}

// leaving function
void globalLeaving( ChatNodeList *clientList )
{

  // push [USER LEAVE] message to all clients

}

void globalShutdown( ChatNodeList *clientList )
{

}

void* handle_client( void* args )
{
  // initialize variables
  struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;

  // read size of messageType

  // read size of chatNode

  // create copy of messageType

  // process depending on msgType

    //  JOIN

      // Add new chat node to linked list

    //  LEAVE

      // client will stop receiving, can still send JOIN message

      // remove chat node

    //  SHUTDOWN

      // client will stop sending or receiving

      // remove chat node

      // terminate connection with client

    //  SHUTDOWN_ALL

      // remove all chat nodes

    //  NOTE

      // push notes to all clients

    //  JOINING

      // push [USER JOIN] message to all clients

    //  LEAVING

      // push [USER LEAVE] message to all clients

}
