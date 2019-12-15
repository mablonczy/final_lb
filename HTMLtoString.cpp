//
// Created by cis505 on 11/17/19.
//

#include <string>
#include <random>
#include <fstream>
#include "HTMLtoString.h"

std::string HTMLtoString::readHTML(const std::string& path) {
    std::string data;
    std::ifstream in(path.c_str());
    getline(in, data, std::string::traits_type::to_char_type(
            std::string::traits_type::eof()));
    return data;
}

std::string HTMLtoString::serversDown() {
    std::string htmlPage = readHTML("/home/cis505/lb_server/resources/serversdown.html");
    std::string response = "HTTP/1.1 503 Service Unavailable\r\nContent-Type: text/html\r\nContent-length: " + std::to_string(htmlPage.length()) + "\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
    response.append(htmlPage);
    return response;
}
