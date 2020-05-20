//
// Created by isnob on 16/05/2020.
//
#include <iostream>
#include <memory>
#include <map>
#include "Base.h"
#include "File.h"

#ifndef LAB2_DIRECTORY_H
#define LAB2_DIRECTORY_H

class Directory : public Base {
    static std::shared_ptr<Directory> root;

    std::map<std::string, std::shared_ptr<Base>> children;
    std::weak_ptr<Directory> self;
    std::weak_ptr<Directory> parent;
    //std::string name;

    Directory(std::string name,std::weak_ptr<Directory> parent);

    static std::shared_ptr<Directory> makeDir(std::string name, std::weak_ptr<Directory> parent);


public:
    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<Directory> addDirectory(const std::string& name);
    std::shared_ptr<File> addFile (const std::string& nome, uintmax_t size);
    std::shared_ptr<Base> get(const std::string& name);
    std::shared_ptr<Directory> Directory::getDir(const std::string &name);
    bool remove (const std::string& nome);

    void ls(int indent) const override;

    int mType() const override;

    ~Directory() {
        std::cout << "~ Distrutta " << name << " @ " << this << std::endl;

    }
};


#endif //LAB2_DIRECTORY_H
