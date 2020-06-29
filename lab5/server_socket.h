//
// Created by isnob on 14/06/2020.
//
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/types.h>
#include <stdexcept>
#include <windows.h>
#include <io.h>
#include <inaddr.h>
#include <map>
#include <vector>
#include "socket.h";
#ifndef LAB5_SERVER_SOCKET_H
#define LAB5_SERVER_SOCKET_H

#endif //LAB5_SERVER_SOCKET_H
class ServerSocket: private Socket {
public:
    ServerSocket(int portNumber) {

        struct sockaddr_in addr;
        cout<<"SERVER SOCKET CONSTRUCTOR"<<endl;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(portNumber);
        addr.sin_addr.s_addr= htonl(INADDR_ANY);
        int resBind= ::bind(sockfd, (SOCKADDR *) &addr, sizeof(addr));
        if(resBind != 0){
            cout << "cannot Bind port "<<sockfd << endl;
            throw runtime_error("cannot Bind port");
        }
        if(listen(sockfd, 8)!=0) // passivo
        {
            cout << "cannot listen port" << endl;
            throw runtime_error("cannot listen port");}
    }

    ~ServerSocket() {
        closesocket(sockfd);
    }
    Socket accept(struct sockaddr_in *addr,   int* len) {
        int fd = ::accept(sockfd, reinterpret_cast<struct sockaddr *>(addr),len);
        if( fd<0){
            cout << "cannot accept socket "<<fd<<WSAGetLastError() << endl;
            throw runtime_error("cannor accept socket");
        }

        return Socket(fd);
    }
};
