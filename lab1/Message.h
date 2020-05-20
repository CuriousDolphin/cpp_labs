//
// Created by isnob on 12/05/2020.
//

#ifndef LAB1_MESSAGE_H
#define LAB1_MESSAGE_H


class Message {

private:
    long id;

    char *mkMessage(int n);
    int size;
protected:
    char *data;
public:
    static long cont;
    static long invocations; //per controllare se alla fine tutti sono distrutti
    // constructor with params
    Message(int size);
    // default constructor
    Message();
    // copy constructor
    Message(const Message& source);

    // movement constructor
    Message(Message&& source);


    ~Message();

    int getSize() const { return size; }
    long getId() const { return id; }

    char* getData() const { if(data!= nullptr)return data;}

    Message& operator =(const Message& source);
    Message& operator =(Message&& source);


};

std::ostream & operator<<(std::ostream& out, const Message& m) ;

#endif //LAB1_MESSAGE_H
