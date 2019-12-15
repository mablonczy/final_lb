//
// Created by cis505 on 11/19/19.
//

#ifndef FINAL_SERVER_H
#define FINAL_SERVER_H

#include <vector>
#include <string>

class Server {

public:
    static std::vector<int> frontendServers;
    static void startServer();
    static std::vector<std::string> pingFrontendServers();
    Server() {
        frontendServers = {5051, 5052, 5053};
    }
    static bool toggleServer(int port);
};


#endif //FINAL_SERVER_H
