//
// Created by cis505 on 11/19/19.
//

#ifndef FINAL_POSTHANDLER_H
#define FINAL_POSTHANDLER_H

#include <string>
#include <vector>

class PostHandler {

public:
    std::string handleRequest(std::string& request);

    static std::string sendOk(const std::string& basicString);

    std::string sendFail();

    std::string findData(std::string &request);
};


#endif //FINAL_POSTHANDLER_H
