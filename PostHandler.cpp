//
// Created by cis505 on 11/19/19.
//

#include "PostHandler.h"
#include "Server.h"
#include "HTMLtoString.h"
#include "json.hpp"

using json = nlohmann::json;

std::string PostHandler::handleRequest(std::string& request) {
    std::vector<std::string> liveServers = Server::pingFrontendServers();
    request = request.substr(request.find_first_of('/'));
    std::string path = request.substr(0,request.find_first_of(' '));
    if (path == "/web/admin/toggle") {
        std::string data = findData(request);
        data = data.substr(0, data.find_last_of('}') + 1);
        json j = json::parse(data);
        std::string server = j["address"];
        server = server.substr(server.find_first_of(':') + 1);
        if (Server::toggleServer(stoi(server))) {
            sendOk("PASS");
        } else {
            sendFail();
        }
    }
    if (liveServers.size() > 0) {
        return sendOk(liveServers.at(rand() % liveServers.size()));
    } else {
        return sendFail();
    }
}


std::string PostHandler::sendOk(const std::string& data) {
    std::string json = "{\"location\":" + data + "}";
    return "HTTP/1.1 200 Okay\r\nContent-Type: application/json\r\nContent-length: " + std::to_string(json.length()) + "\r\nAccess-Control-Allow-Origin: *\r\n\r\n" + json + "\r\n";
}

std::string PostHandler::sendFail() {
    return HTMLtoString::serversDown();
}

std::string PostHandler::findData(std::string& request) {
    std::string lineEnd = "\r\n";
    int pos = 0;
    std::string headerLine;
    while ((pos = request.find(lineEnd)) != std::string::npos) {
        headerLine = request.substr(0, pos);
        request.erase(0, pos + lineEnd.length());
        if (headerLine.empty()) {
            break;
        }
    }
    return request;
}

