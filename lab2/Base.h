//
// Created by isnob on 16/05/2020.
//

#ifndef LAB2_BASE_H
#define LAB2_BASE_H

#include <xhash>

//template  <typename T>
class Base {
protected:
    // Parameters
    std::string name;
public:
    std::string getName () const {
        return this->name;
    };
    virtual int mType () const = 0;
    virtual void ls (int indent) const = 0;


};


#endif //LAB2_BASE_H
