//
// Created by isnob on 14/05/2020.
//

#include <iostream>
#include "MessageStore.h"
#include "DurationLogger.h"

MessageStore::MessageStore(int n) : n(n), dim(n),countMsg(0) {
    std::cout << "MESSAGESTORE constructor " << std::endl;
    this->messages = new Message[n];
}

MessageStore::~MessageStore() {
    std::cout << "MESSAGESTORE destructor " << std::endl;
    delete[] this->messages;
}

void MessageStore::add(Message &m) {

    if (countMsg < dim) { // se non e' multiplo di 10
        int i = 0;
        while (this->messages[i].getId() != -1 && i < dim) {
            i++;
        };
        //std::cout << "FOUND FREE INDEX " << i << std::endl;

        this->messages[i] = m;
        this->countMsg++;
        //std::cout << "MESSAGESTORE ADD " <<i<< std::endl;
    }else{
       // std::cout << "REALLOC " <<dim<<n<< std::endl;

        Message *newBuf= new Message[dim+n];

        for (int i = 0; i < dim; i++) {
            newBuf[i] = std::move(messages[i]);  // usa l'operatore = per movimento molto piu veloce!!
           // newBuf[i] = messages[i]; solo per benchmark
        }
        delete[] messages;
        this->messages=newBuf;
        this->messages[dim]=m;
        //std::cout << "FOUND FREE INDEX " << dim << std::endl;
        this->dim+=n;
        this->countMsg++;

    }

}
void MessageStore::compact(){
    DurationLogger dl("COMPACT");
    int minDim=countMsg+(countMsg%n);
    //std::cout<<"MIN DIM COMPACT "<<countMsg<<std::endl;
    Message *newBuf= new Message[minDim];
    int j=0;
    for (int i=0;i<dim;i++){
        if(messages[i].getId()!=-1){
            newBuf[j]=std::move(messages[i]);
            // newBuf[i] = messages[i]; solo per benchmark
                    j++;
        }
    }
    delete[] messages;
    messages=newBuf;
    dim=minDim;


}
bool MessageStore::remove(long id) {
    for(int i=0;i<dim;i++){
        if(messages[i].getId()==id){
            messages[i]=Message();
            countMsg--;
            return true;
        }

    }
    return false;
}

std::optional<Message> MessageStore::get(long id){
    for(int i=0;i<dim;i++){
        if(messages[i].getId()==id)
            return messages[i];
    }
}

std::tuple<int, int> MessageStore::stats(){

    return std::tuple(countMsg,dim-countMsg);
}

