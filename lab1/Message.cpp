//
// Created by isnob on 12/05/2020.
//

#include <string>
#include <iostream>
#include "Message.h"
const bool debug = false;
long Message::cont=0;
long Message::invocations=0;
Message::Message(int size): size(size),id(cont++) {
    invocations++;
    if constexpr (debug) std::cout<<"Message:: constructor with param"<<std::endl;
    data=mkMessage(size);
}
Message::Message(): id(-1),size(0) {
    invocations++;
    if constexpr (debug)  std::cout<<"Message:: constructor default"<<std::endl;
    data= nullptr;
}

Message::Message(const Message& source):size(source.size),id(source.id){
    invocations++;
    if constexpr (debug) std::cout<<"Message:: Copy constructor "<<std::endl;
    data=new char[size+1];
    memcpy(data,source.data,size+1);
}

Message::Message( Message&& source):size(source.size),id(source.id){
    invocations++;
    if constexpr (debug) std::cout<<"Message:: Movement constructor "<<std::endl;
    data=source.data;
    source.data = nullptr;
    source.size=0;
    source.id=-1;
}
Message::~Message(){
    invocations--;
    if constexpr (debug) std::cout<<"Message:: Destructor  "<<invocations<<std::endl;
    id=-1;
    delete[] data;
}
Message& Message::operator =(const Message& source){
    if constexpr (debug) std::cout<<"Message:: operator =  "<<std::endl;
    if(this!=&source){
        delete[] data;
        data= nullptr;

        size=source.size;
        id=source.id;
        data=new char[size+1];
        memcpy(data,source.data,size+1);
    }
    return *this;
}
Message& Message::operator =( Message&& source){

    if constexpr (debug )  std::cout << "Message:: operator = MOVEMENT " << std::endl;
    if(this!=&source){
        data= source.data;
        size=source.size;
        id=source.id;
        source.data= nullptr;
        source.id=-1;
        source.size=0;

    }
    return *this;
}

char* Message::mkMessage(int n) {
    std::string vowels = "aeiou";
    std::string consonants = "bcdfghlmnpqrstvz";
    char * m = new char [n+1];
    for ( int i= 0 ; i<n; i++){
        m[i]= i% 2 ? vowels[rand()%vowels.size()] :
              consonants[rand()%consonants.size()];
    }
    m[n] = 0 ;
    return m;
}

std::ostream & operator<<(std::ostream &out, const Message &m) {
    out  << "[id:"<< m.getId() << "]"<<"[size:"<< m.getSize()<< "]"<< "[data:"<< m.getData()<< "]"<< "[Addr:"<< &m<< "]";
    return out;
}

