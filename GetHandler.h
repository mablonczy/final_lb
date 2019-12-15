//
// Created by cis505 on 11/17/19.
//

#ifndef FINAL_GETHANDLER_H
#define FINAL_GETHANDLER_H


#include <string>

class GetHandler {

public:
    std::string handleRequest(std::string& request);

    static std::string sendOk(const std::string &data, std::string page);

    std::string sendFail();
};


#endif //FINAL_GETHANDLER_H
