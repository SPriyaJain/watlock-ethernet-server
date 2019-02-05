#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

/*
 * ErrorMessge: Displays the desired error message
 * msg: The message to be displayed
 */
void ErrorMessage(const char *msg){
        perror(msg);
}

int main(int argc, char *argv[])
{
        printf("hellow world");
        /*
         * sock_fd && new_sock_fd: The socket descriptors
         * port: Port number
         * clilen: used to store the length of the address of the client
         * n: contains the number of characters in a string
         */
        int sock_fd, new_sock_fd, port, clilen, n;
        char buffer[256]; // Reads the characters sent on the connection with the server

        /*
         * sockaddr_in: allows the storage of IPs
         * serv_addr: Stores the ip of the server
         * cliaddr: Stores the ip of the client
         */
        struct sockaddr_in serv_addr, cli_addr;

        printf("lots of statements");

        /*
         * AF_INET: Creates a socket using the address family that is used to designate IPv4 type addresses
         * SOCK_STREAM: Enforces socket to use TCP
         * 0: OS chooses the protocol to use
         */
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);

        if(sock_fd < 0) // Checks if socket was opened successfully (sock_fd returns -1 if it failed)
                fprintf(stderr, "Error opening socket");

        bzero((char *) & serv_addr, sizeof(serv_addr));// sets serv_addr to zeros

        printf("hellow therewwwwww");

        port = atoi(argv[1]);

        /*
         * Ensures port is passed on argv when program is executed
         */
        printf("hello there");

        if(argc < 2){
                printf("value of argc is %d\n", argc);
                fprintf(stderr, "Error, missing port\n");
                return 0;
        }

        /*
         * sin_family: Family of addresses to be used
         * sin_port: Converts from Little Endian to Big Endian (Using htons() because we are passing short integer)
         * sin_addr.s_addr: unsigned long to pass the IP of server
         */
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        /*
         * Binds the socket to the IP
         * Bind: The socket descriptor, Address to be binded, size of the address that will be binded
         */
        if (bind(sock_fd, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0)
                ErrorMessage("Error in connection");

        listen(sock_fd, 10); // Makes the server listen to connections, the second argument states how many can wait while server is recieving a connection elsewhere

        /*
         * Provides clilen the size of the address of the client
         * Accepting the connection creates another socket given to new_sock_fd which is given the descriptor, client address, and size of client address
         * accept() will block the error until a client connects
         */
        clilen = sizeof(cli_addr);
        new_sock_fd = accept(sock_fd, (struct sockaddr *) & cli_addr, &clilen);
        if(new_sock_fd < 0)
                ErrorMessage("Error on accepting incoming connections");

        bzero(buffer, 256); // sets the buffer positions to zero
        n = read(new_sock_fd, buffer, 255); // Stores the number of characters that will be read

        if(n < 0) // Checks if socket is read successfully
                ErrorMessage("Error reading socket");
        printf("Here is the message: %s", buffer); // Displays the message of the client

        n = write(new_sock_fd, "Got your message", 16); // Stores the number of characters that will be sent
        if(n < 0) // Checks if writing on socket was successfull
                ErrorMessage("Error writing on socket");
        return 0;
}
