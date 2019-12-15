//
// Created by cis505 on 11/17/19.
//


#include <string>
#include "GetHandler.h"
#include "Server.h"
#include "HTMLtoString.h"

std::string GetHandler::handleRequest(std::string& request) {
    request = request.substr(request.find_first_of('/'));
    std::string page = request.substr(1, request.find_first_of(' '));
    if (page == " ") {
        page = "web";
    }
    std::vector<std::string> liveServers = Server::pingFrontendServers();
    if (liveServers.size() > 0) {
        return sendOk(liveServers.at(rand() % liveServers.size()), page);
    } else {
        return sendFail();
    }
}


std::string GetHandler::sendOk(const std::string& data, std::string page) {
    return "HTTP/1.1 303 See Other\r\nLocation: http://localhost:" + data + "/" + page + "\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
}

std::string GetHandler::sendFail() {
    return HTMLtoString::serversDown();
}
