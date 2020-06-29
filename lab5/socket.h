//
// Created by isnob on 13/06/2020.
//

#include <WinSock2.h>
#include <iostream>

#ifndef LAB5_SOCKET_H
#define LAB5_SOCKET_H

#endif //LAB5_SOCKET_H
using namespace std;
class Socket {
    int sockfd;

    Socket(const Socket &) = delete;

    Socket &operator=(const Socket &) = delete;

    Socket(int sockfd) : sockfd(sockfd) {
        cout << "Socket " << sockfd << " created with private" << endl;
    }

    friend class ServerSocket;

public:

    Socket(Socket&& other){ // movment constructor
        if (sockfd != 0) closesocket(sockfd);
        sockfd = other.sockfd;
        other.sockfd = 0;
    }

    Socket() {
        sockfd = ::socket(AF_INET, SOCK_STREAM, 0); // tcp socket
        if (sockfd < 0)
            throw runtime_error(" CANNOT CREATE SOCKET");
        cout << "Socket" << sockfd << " created" << endl;

    }

    ~Socket() {
        if (sockfd != 0) {
            cout << "Socket" << sockfd << " closed" << endl;

            closesocket(sockfd);
        }
    }

    Socket& operator=(Socket &&other) { // movimento
        if (sockfd != 0) closesocket(sockfd);
        sockfd = other.sockfd;
        other.sockfd = 0;
        return *this;
    }
    int getFd(){
        return sockfd;
    }
    int read(char *buffer,int len, int options){
        int  res = ::recv(sockfd, buffer,len,options);
        if( res<0)
            throw runtime_error("cannot read from socket");
        return res;
    }
    int write(char *buffer,size_t len, int options){
        int res = ::send(sockfd, buffer,len,options);
        if( res<0)
            throw runtime_error("cannot write to socket");
        return res;
    }

    int write_string(std::string &str){
        int res = write(str.data(), str.size(), 0);
        str.clear();
        return res;
    }
    void connect (struct sockaddr_in *addr, unsigned int len){
        if(::connect(sockfd, reinterpret_cast<struct sockaddr *>(addr),len)!=0)
            throw runtime_error("cannor connect to remote socket");
    }

};