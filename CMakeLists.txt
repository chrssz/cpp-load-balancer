cmake_minimum_required(VERSION 3.16)
project(cpp-load-balancer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_load_balancer
    src/main.cpp
    src/server/server.cpp
    src/socket/socket.cpp
    src/socket/connectedsocket.cpp
    src/socket/listeningsocket.cpp
    src/threadpool/threadpool.cpp
    src/httpparse/parse.cpp
)

target_include_directories(cpp_load_balancer
    PRIVATE
        server
        socket
        threadpool
        utils
        httpparse
)

if(WIN32)
    target_link_libraries(cpp_load_balancer PRIVATE ws2_32)
endif()