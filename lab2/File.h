//
// Created by isnob on 16/05/2020.
//

#ifndef LAB2_FILE_H
#define LAB2_FILE_H

#include <iostream>
#include <memory>
#include <map>
#include "Base.h"

class File : public Base {
    std::string name;
    File(std::string name,uintmax_t size);
    uintmax_t size;

    public:
    static std::shared_ptr<File> newFile(std::string name,uintmax_t size);
    uintmax_t getSize () const;
    void ls (int indent) const override;
    int mType() const override;
    ~File(){
        std::cout << "~ Distrutto FILE " << name << " @ " << this << std::endl;
    }
};


#endif //LAB2_FILE_H
