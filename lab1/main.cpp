#include <iostream>
#include "Message.h"
#include "DurationLogger.h"
#include "MessageStore.h"

void firstHalf();

void secondHalf();

int main() {
    DurationLogger dl("Main");

    //firstHalf();

    secondHalf();


    return 0;
}

void secondHalf() {
    Message buff[100]; //uso un buffer per testare dingolarmente le prestazioni del solo message store e non invludere quelle di creazione messaggi

    for (int i = 0; i < 100; i++) {
        buff[i] = Message(1000000); // usa l'operatore = per movimento!!
    }


    {
        DurationLogger dl("MessageStore");
        MessageStore ms(10);
        for (int i = 0; i < 100; i++) {

            ms.add(buff[i]);
        }
        std::optional<Message> m=ms.get(99);
        //std::cout<<m.value()<<std::endl;


        std::tuple t=ms.stats();
        std::cout<<"DISPONIBILITA [usati][disponibili]"<<get<0>(t)<<":"<<get<1>(t)<<std::endl;

        for (int i = 0; i < 100; i++) {
            if(i%2 == 0){
              ms.remove(i);
            }


        }
        ms.compact();

        Message m2 =Message(100);
        ms.add(m2);
        std::tuple t1=ms.stats();
        std::cout<<"DISPONIBILITA [usati][disponibili]"<<get<0>(t1)<<":"<<get<1>(t1)<<std::endl;


    }
}


void firstHalf() {

    Message m1(10);
    Message m2(20);
    Message m3(m1);
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;

    Message m4 = std::move(m2);
    std::cout << "MOV m2->m4" << std::endl;
    std::cout << m4 << std::endl;
    std::cout << m2 << std::endl;

    m1 = m4;
    std::cout << "COPY m4->m1" << std::endl;
    // std::cout << m4 <<std::endl;
    std::cout << m1 << std::endl;

    Message buff1[10]; //usa il costruttore di degaulr

    Message *buff2 = new Message[10]; //e' necessario fare la delete del buffer SI!
    buff1[1] = Message(10);

    for (int i = 0; i < 10; i++) {
        buff1[i] = Message(1000000); // usa l'operatore = per movimento!!
    }


    {
        DurationLogger dl("Operator =");
        for (int i = 0; i < 10; i++) {
            buff2[i] = buff1[i];  // usa l'operatore = per copia!!
        }
    }

    {
        DurationLogger dl("Operator = MOVMENT");
        for (int i = 0; i < 10; i++) {
            buff2[i] = std::move(buff1[i]);  // usa l'operatore = per movimento!!
        }
    }
}
