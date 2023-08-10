#include "client.h"
#include <bits/stdc++.h>

using namespace std;

int MAX_DATA = 1024;

Client::Client(string ip, int PORT) {
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sock = sockfd;
}

void Client::set_conn() {
    // establish connection to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        exit(1);
    }
}

void Client::set_timeout(int TIMEOUT) {
    // set the socket timeout
    sock = sockfd;
    struct timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = TIMEOUT;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        std::cerr << "Failed to set socket timeout" << std::endl;
        exit(1);
    }
}

vector<char> Client::recieve() {
    socklen_t len;
    size_t data_len;
    vector<char> buffer(MAX_DATA);
    data_len = read(sockfd, buffer.data(), MAX_DATA);
    if (data_len < 0) {
        std::cerr << "Failed to read from socket" << std::endl;
        exit(1);
    }
    buffer.resize(data_len);
    return buffer;
}

void Client::send_data(vector<char> msg) {
    socklen_t len = sizeof(servaddr);
    send(sockfd, msg.data(), msg.size(), 0);
}

void Client::close_conn() {
    close(sockfd);
}