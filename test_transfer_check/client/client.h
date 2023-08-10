#ifndef CLIENT_H
#define CLIENT_H

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

class Client {
    int sockfd;
    int sock;
    struct sockaddr_in servaddr;
public:
    Client(string, int);
    void set_conn();
    void set_timeout(int T);
    vector<char> recieve();
    void send_data(vector<char> msg);
    void close_conn();
};

#endif