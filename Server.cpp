//
// Created by cis505 on 11/19/19.
//

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <zconf.h>
#include <arpa/inet.h>
#include <strings.h>
#include <cstring>
#include "Server.h"
#include "ThreadHandler.h"
#include "Writer.h"

std::vector<int> Server::frontendServers;

void Server::startServer() {
    int port_num = 5555;
    //open socket
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Cannot open socket" << std::endl;
        exit(1);
    }
    //bind port
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port_num);
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    //listen
    listen(sockfd, 100);
    pthread_t thread;
    while (true) {
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        //accept connection
        int comm_fd = accept(sockfd, (struct sockaddr *) &clientaddr, &clientaddrlen);
        std::cerr << "[" << comm_fd << "] " << "New connection" << std::endl;
        pthread_create(&thread, NULL, ThreadHandler::worker, &comm_fd);
    }
}

std::vector<std::string> Server::pingFrontendServers() {
    std::vector<std::string> liveServers;
    for (auto server: Server::frontendServers) {
        int sockfd = socket(PF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            fprintf(stderr, "Cannot open socket (%s)\n", strerror(errno));
            exit(1);
        }
        struct sockaddr_in servaddr;
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(server);
        inet_pton(AF_INET, "localhost", &(servaddr.sin_addr));
        connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
        std::string ping = "ALIVE?";
        Writer::do_write(sockfd, ping.c_str(), ping.length());
        char* buf = new char[500];
        int rcvd = ThreadHandler::do_read(sockfd, buf, 500);
        if (rcvd > 0) liveServers.push_back(std::to_string(server));
        close(sockfd);
    }
    return liveServers;
}

bool Server::toggleServer(int server) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Cannot open socket (%s)\n", strerror(errno));
        exit(1);
    }
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server);
    inet_pton(AF_INET, "localhost", &(servaddr.sin_addr));
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    std::string ping = "SWITCH";
    Writer::do_write(sockfd, ping.c_str(), ping.length());
    char* buf = new char[500];
    int rcvd = ThreadHandler::do_read(sockfd, buf, 500);
    close(sockfd);
    return rcvd > 0;
}
