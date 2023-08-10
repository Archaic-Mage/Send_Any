#include "Server.h"
#include <bits/stdc++.h>

using namespace std;

int MAX_DATA = 1024;

Server::Server(int PORT)
{
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    int opt = 1;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port PORT
    if (setsockopt(sockfd, SOL_SOCKET, 
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // listen for connections
    if (listen(sockfd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

int Server::accept_conn() {
    socklen_t len;
    int connfd;
    len = sizeof(cliaddr);  //len is value/result

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr,
                    &len);
    if (connfd < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return connfd;
}

vector<char> Server::recieve(int connfd)
{
    socklen_t len;
    int data_len;
    vector<char> buffer(MAX_DATA);

    len = sizeof(cliaddr);
    data_len = read(connfd, buffer.data(), MAX_DATA);
    if (data_len < 0)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer.resize(data_len);
    return buffer;
}

void Server::send_data(vector<char> msg, int PORT, string IP, int connfd) {
    socklen_t len = sizeof(cliaddr);
    //sets the client info 
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(PORT);
    cliaddr.sin_addr.s_addr = inet_addr(IP.c_str());

    send(connfd, msg.data(), msg.size(), 0);
}

void Server::close_conn(int connfd) {
    close(connfd);
}