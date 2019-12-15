cmake_minimum_required(VERSION 3.15)
project(lb_server)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

set(CMAKE_CXX_STANDARD 17)

add_executable(lb_server json.hpp main.cpp Server.cpp Server.h ThreadHandler.cpp ThreadHandler.h GetHandler.cpp GetHandler.h PostHandler.h PostHandler.cpp Writer.cpp Writer.h HTMLtoString.cpp HTMLtoString.h)