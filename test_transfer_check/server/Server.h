#ifndef Server_f
#define Server_f

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

class Server {

    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;

    //functions for creating server, sending and recieving data packets
public:

    //constructor function to start the server
    Server(int);
    //get sockid
    void get_sockfd() {
        cout << sockfd << endl;
    }
    //helper function to accept connections
    int accept_conn();
    //helper function to recieve data from clients
    vector<char> recieve(int);
    //helper function to send the data to clients
    void send_data(vector<char> msg, int PORT, string IP, int connfd);
    //helper function to close the socket connection
    void close_conn(int);
};

#endif