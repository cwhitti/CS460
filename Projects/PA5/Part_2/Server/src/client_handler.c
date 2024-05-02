#include "client_handler.h"

bool clientInList( ChatNodeList *clientList, Message* messageObj )
{
  ChatNode *wkgPtr = clientList -> firstPtr;
  ChatNode msgSender = messageObj -> messageSender;

  while ( wkgPtr != NULL && !compareChatNodes( wkgPtr, &msgSender ) )
  {
    wkgPtr = wkgPtr -> next;
  }

  return wkgPtr != NULL;

}
// join function
void clientJoin( ChatNodeList *clientList, Message* messageObj )
{
  // grab client from messageObj
  ChatNode clientNode = messageObj->messageSender;

  printf("Trying to add %s\n", clientNode.name);

  // add client to clientList
    // function: addChatNodeToList
  addChatNodeToList(clientList, &clientNode);

  // change msgtype from JOIN > JOINED
  messageObj->messageType = JOINING;
  strncpy( messageObj->noteContent, "User has joined!!!\n",
                                    sizeof(messageObj->noteContent));

  // send join message to all clients
    // function: forwardMessage()
  forwardMessage(clientList, messageObj);
}

// leave function
void clientLeave( ChatNodeList *clientList, Message* messageObj )
{
  // grab client from messageObj
  ChatNode clientNode = messageObj->messageSender;

  // remove chat node
    // function: removeNodeFromList
  if (removeNodeFromList(clientList, &clientNode))
  {
    printf("%s was removed!\n", clientNode.name);

    // change msgtype from LEAVE > LEAVING
    messageObj->messageType = LEAVING;
    strncpy( messageObj->noteContent, "User has Left!!!\n",
                                      sizeof(messageObj->noteContent));

    // send
      // function: forwardMessage()
    forwardMessage(clientList, messageObj);
  }
}

void forwardMessage( ChatNodeList *clientList, Message* messageObj )
{
  printf("Got into forward message\n");
  printf("Message to forward:");
  printMessageStruct(messageObj);
   // declare variables
  ChatNode* wkgPtr;

  // grab client from messageObj
  ChatNode clientNode = messageObj->messageSender;

  for (wkgPtr = clientList->firstPtr; wkgPtr != NULL; wkgPtr = wkgPtr->next)
  {
    if ( !compareChatNodes(wkgPtr, &clientNode) )
    {

      printf("Trying to forward to: ");
      printElement( wkgPtr );
      printf("\n");

      int sendSocket = socket(AF_INET, SOCK_STREAM, 0);;

      struct sockaddr_in clientAddress;
      clientAddress.sin_family = AF_INET;
      clientAddress.sin_addr.s_addr = htonl(wkgPtr->ip);
      clientAddress.sin_port = htons(wkgPtr->port);

      if (connect(sendSocket, (struct sockaddr *)&clientAddress,
                                                  sizeof(clientAddress)) == -1)
      {
        perror("Error forwarding to client");
        exit(EXIT_FAILURE);
      }

      printf("Connected to person\n");
      writeMessageToSocket(sendSocket, messageObj);
      printf("Successfully wrote to person\n");

      // disconnect
      if (close(sendSocket) == -1)
      {
          perror("Error closing socket");
          exit(EXIT_FAILURE);
      }

      printf("Closed socket to client\n");
      printf("Sent to %s\n", wkgPtr->name);
    }
  }
}

void* handle_client( void* args )
{
  // initialize variables
  ThreadArgs *threadArgs = (ThreadArgs *)args;

  // grab client socket
  int clientSocket = threadArgs->clientSocket;
  // grab clientList
  ChatNodeList* clientList = threadArgs->clientList;
  pthread_mutex_t* mainLock = threadArgs->mainLock;
  pthread_mutex_t* llLock = threadArgs->llLock;

  pthread_mutex_unlock(mainLock);
  pthread_mutex_unlock(llLock);

  printf("Client accepted!\n");

  // read entire message from socket, returns pointer to new msg struct
    // function: readMessageFromSocket( )
  Message* messageObj = readMessageFromSocket( clientSocket );

  // process depending on MessageType
  switch (messageObj->messageType)
  {
    //  JOIN
    case JOIN:

      if ( !clientInList( clientList, messageObj ) )
      {
        // function: clientJoin()
        printf("%s joined\n", messageObj->messageSender.name);
        clientJoin(clientList, messageObj);
        printf("Finsihed joining\n");
      }
      break;

    //  LEAVE
    case LEAVE:

      if ( clientInList( clientList, messageObj ) )
      {
        // function: clientLeave()
        printf("%s left\n", messageObj->messageSender.name);
        clientLeave(clientList, messageObj);
        printf("Finished leaving\n");
      }

      break;

    //  SHUTDOWN
    case SHUTDOWN:

      if ( clientInList( clientList, messageObj ) )
      {
        printf("%s shutdown\n", messageObj->messageSender.name);
        // function: clientLeave()
        clientLeave(clientList, messageObj);
        printf("Finished shutting down\n");
      }

      break;

    //  SHUTDOWN_ALL
    case SHUTDOWN_ALL:

      if ( clientInList( clientList, messageObj ) )
      {
        printf("%s shutdown all\n", messageObj->messageSender.name);
        // function: forwardMessage()
        forwardMessage(clientList, messageObj);

        // function: clearChatNodeList()
        clearChatNodeList(clientList);

        printf("Finished shutdown all\n");
      }
      break;

    //  NOTE
    case NOTE:
      printf("Note from %s\n", messageObj->messageSender.name);
      // function: forwardMessage()

      if ( clientInList( clientList, messageObj ) )
      {
        forwardMessage(clientList, messageObj);
        printf("Finished forwarding the note\n");
      }
      else
      {
        printf("%s not in list\n", messageObj->messageSender.name);
      }

      exit(EXIT_SUCCESS);
      break;

    /*
    //  JOINING
    case JOINING:
      // function: forwardMessage()
      forwardMessage(clientList, messageObj);
      break;

    //  LEAVING
    case LEAVING:
      // function: forwardMessage()
      forwardMessage(clientList, messageObj);
      break;
    */
    default:
      break;
  }

  displayLinkedList( clientList );

  pthread_exit(NULL);
}
