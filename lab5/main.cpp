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
#include <future>
#include <fstream>
#include <sstream>
#include <string>
#include "server_socket.h"
#include "job.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int N_THREAD = 4;

class WinSockSingletonHelper {
    WinSockSingletonHelper() {
        WSADATA info;
        unsigned int ris = WSAStartup(MAKEWORD(2, 2), &info);
        if (ris != 0) {
            cout << "Error initializing ws2 " << ris << endl;
            throw std::runtime_error("Error initializing ws2");
        }

    }

    ~WinSockSingletonHelper() {
        WSACleanup();
    }

protected:
    static WinSockSingletonHelper instance;
};

WinSockSingletonHelper
        WinSockSingletonHelper::instance;


class Message {
    std::string name;
    std::string message;
public:
    // constructor
    explicit Message(const std::string &name, const std::string &message) {
        this->name = name;
        this->message = message;
    }

    std::string getName() {
        return name;
    };

    std::string getMessage() {
        return message;
    };

};


class User {
    std::string name;
    int sock_fd;
public:
    // constructor
    User(const string &name, const int &fd) {
        this->name = name;
        this->sock_fd = fd;
    }

    string getName() {
        return name;
    };

    int getFd() {
        return sock_fd;
    };


};

int writeTo(int other_sockfd, std::string &str) {
    int res = 0;
    res = ::send(other_sockfd, str.data(), str.size(), 0);
    if (res < 0) throw std::runtime_error("Cannot write to socket");
    return res;
}

void writeToClient(std::string &str, Socket &s) {
    // take a string and a socket
    // then write to the socket
    // clear the string
    s.write(str.data(), str.size(), 0);
    str.clear();
}

class Chat {
    condition_variable cv_nicknames;
    condition_variable cv_messages;
    mutex m;
    vector<User> users;
    vector<Message> messages;

public:
    void addUser(User u) {
        unique_lock<mutex> lg(m);
        this->users.push_back(u);
        cout << "USER SAVED " << u.getName() << "(socket :" << u.getFd() << ")" << endl;
        cv_nicknames.notify_all();
    }

    void removeUser(User u) {
        unique_lock<mutex> lg(m);
        for(int i=0;i<users.size();i++){
            if(users[i].getName().compare(u.getName())==0){
                cout << "USER DISCONNETTED " << u.getName() << "(socket :" << u.getFd() << ")" << endl;
                users.erase(users.begin()+i);
                break;
            }
        }

        cv_nicknames.notify_all();
    }

    void addMessage(Message msg) {
        unique_lock<mutex> lg(m);

        this->messages.push_back(msg);
        cout << " ADD MSG " << msg.getName() << ":" << msg.getMessage() << endl;
    }

    vector<Message> getChat() {
        unique_lock<mutex> lg(m);

        return messages;
    }

    vector<User> getUsers() {
        unique_lock<mutex> lg(m);
        //  cv_nicknames.wait(lg);
        return users;
    }

};

void send_screen_client(Chat &chat, Socket &s) {
    string bufferNames;
    bufferNames += "\u001B[2J"; // clear screen
    bufferNames += "----------------------------------\n";
    bufferNames += "Users online : \n";
    vector<int> fds;
    for (auto &n : chat.getUsers()) {
        bufferNames += " ";
        bufferNames += n.getName();
        bufferNames += "\n";

        fds.push_back(n.getFd());
    }
    bufferNames += "----------------------------------\n";
    bufferNames += " CHAT: \n";
    for (auto &m : chat.getChat()) {
        bufferNames += " ";
        bufferNames += m.getName();
        bufferNames += " : ";
        bufferNames += m.getMessage();
        bufferNames += '\n';
    }

    bufferNames += "\n\r Type a Msg: ";
    writeToClient(bufferNames, s);
}

void send_screen_all(Chat &chat) {
    string bufferNames;
    bufferNames += "\u001B[2J"; // clear screen
    bufferNames += "----------------------------------\n";
    bufferNames += "Users online : \n";
    vector<int> fds;
    for (auto &n : chat.getUsers()) {
        bufferNames += " ";
        bufferNames += n.getName();
        bufferNames += "\n";

        fds.push_back(n.getFd());
    }
    bufferNames += "----------------------------------\n";
    bufferNames += " CHAT: \n";
    for (auto &m : chat.getChat()) {
        bufferNames += " ";
        bufferNames += m.getName();
        bufferNames += " : ";
        bufferNames += m.getMessage();
        bufferNames += '\n';
    }

    bufferNames += "\n\r Type a Msg: ";

    for(auto &fd:fds){
        writeTo(fd,bufferNames);
    }

}





void serverFn2(Jobs<Socket> &jobs, Chat &chat) {
    ostringstream oss;
    std::string hello_client = "Enter your name: ";

    //std::string users = " Users online : \n";
    oss << " - THREAD CREATED " << this_thread::get_id() << endl;
    cout << oss.str();
    while (true) {
        ostringstream oss;
        // get username
        optional<Socket> sock = jobs.get();
        if (!sock.has_value()) {
            break;
        }
        oss << "   (" << this_thread::get_id() << ") TAKE A SOCKET " << sock.value().getFd() << endl;
        cout << oss.str();
        writeToClient(hello_client, sock.value());
        char user_name[1024];
        int size = sock.value().read(user_name, 1023, 0);
        user_name[size - 2] = 0;
        // user_name[size-2]='A';
        oss.clear();
        std::string nick(user_name);
        cout << "   (" << this_thread::get_id() << ")" << " USERNAME  " << nick << "SIZE " << size << endl;
        cout << oss.str();
        //nicknames.push_back(str);
        User u(nick, sock->getFd());
        chat.addUser(u);
        send_screen_client(chat, sock.value());
        char buffer[200];
        int ris = 1;
        while (ris != 0) {
            ris = sock.value().read(buffer, 199, 0);
            buffer[ris-2] = 0;
            std::string str(buffer);
            if(str.compare("quit")==0){
                cout<<"PRINT "<<str<<endl;
                break;
            }
            if (ris > 0) {
                Message m(nick, str);
                chat.addMessage(m);
                send_screen_all(chat);
            }

        };

        chat.removeUser(u);
    }


}


int main() {
    Jobs<Socket> jobs;
    vector<thread> threads;
    Chat c;

    ServerSocket s(7777);
    for (int i = 0; i < N_THREAD; i++)
        threads.emplace_back([&jobs, &c]() {
            serverFn2(jobs, c);
        });


    while (true) {
        struct sockaddr_in in;
        int len = sizeof(in);

        cout << "(" << this_thread::get_id() << ")" << " Waiting for a connection" << endl;

        Socket sock = s.accept(&in, &len);
        char addr[16];
        if (inet_ntop(AF_INET, &in.sin_addr, addr, sizeof(addr)) == nullptr)
            std::cout << "error in reading address\n";
        cout << "(" << this_thread::get_id() << ")" << " connected from " << addr << ":" << ntohs(in.sin_port) << endl;
        jobs.put(move(sock));
    }

    for (auto &t:threads)
        t.join();


    return 0;
}
