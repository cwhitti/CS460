#include "main.h"

int main(int argc, char** argv)
{
    int receivingSocket, sendingSocket;
    pthread_t receivingThread, sendingThread;

    struct sockaddr_in clientAddress;
    char clientIPString[INET_ADDRSTRLEN];
    int myPort;
    char myName[NAME_LEN];

    struct sockaddr_in serverAddress;
    char serverIPString[INET_ADDRSTRLEN] ;
    int serverPort;
    char* serverName = "SERVER";

    Properties* properties;
    ChatNode*[2] chatNodes;

    // read properties
    if (argc != 2)
    {
        printf("Must include properties file name in arguments!\n");
        exit(EXIT_FAILURE);
    }

    properties = property_read_properties(argv[1]);

    // get string properties
    strncpy(clientIPString, property_get_property(properties, "MY_IP"), INET_ADDRSTRLEN);
    strncpy(serverIPString, property_get_property(properties, "SERVER_IP"), INET_ADDRSTRLEN);
    strncpy(myName, property_get_property(properties, "MY_NAME"), NAME_LEN);

    // get int properties
    sscanf(property_get_property(properties, "MY_PORT"), "%d", &myPort);
    sscanf(property_get_property(properties, "SERVER_PORT"), "%d", &serverPort);

    // set chat node array
    chatNodes[0] = createChatNodeFromData((unsigned int)inet_addr(clientIPString),
                                          (unsigned short int)myPort,
                                           myName);

    chatNodes[1] = createChatNodeFromData((unsigned int)inet_addr(serverIPString),
                                          (unsigned short int)serverPort,
                                           serverName);

    printf("test\n");
    /*
    // set server address struct
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIPString);
    serverAddress.sin_port = htons(serverPort);

    // set client address struct
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
    clientAddress.sin_port = htons(receiverPort);
    */ 

    /***************
     Start receiver
    ****************/
    
    /*
    // create receiving socket
    receivingSocket = socket(AF_INET, SOCK_STREAM, 0);

    // bind receiving socket
    if (bind(receivingSocket, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) != 0)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // start listening on receiving socket
    if (listen(receivingSocket, NUM_CONNECTIONS) != 0)
    {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }
    */

    // start listening for messages from server
    pthread_create(&receivingThread, NULL, receiverLoop, (void*)chatNodes);

    /*************
     Start sender
    **************/

    /*
    // create sending socket
    sendingSocket = socket(AF_INET, SOCK_STREAM, 0);

    // connect sending socket to server socket
    if (connect(sendingSocket, (struct sockaddr *)&serverAddress,
                                                sizeof(serverAddress)) == -1)
    {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }
    */

    // start sending messages to server
    pthread_create(&sendingThread, NULL, senderLoop, (void*)chatNodes);
}