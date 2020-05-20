//
// Created by isnob on 16/05/2020.
//

#include "Directory.h"

std::shared_ptr<Directory> Directory::root = nullptr;

Directory::Directory(std::string name, std::weak_ptr<Directory> parent) : name(name), parent(parent) {
    std::cout << " Creata " << name << " @ " << this << std::endl;
}

std::shared_ptr<Directory> Directory::makeDir(std::string name, std::weak_ptr<Directory> parent) {
    Directory *dir =new Directory(name,parent);
    std::shared_ptr<Directory> ptr=std::shared_ptr<Directory>(dir);

    dir->self = ptr;

    return ptr;
}

std::shared_ptr<Directory> Directory::addDirectory(const std::string &name) {
    if (this->children.contains(name))
        return std::shared_ptr<Directory>(nullptr);
    auto child = makeDir(name, this->self);
    this->children.insert({name,child});
    //this->children.insert(std::make_pair(name, child));
    return child;
}
std::shared_ptr<File> Directory::addFile (const std::string& name, uintmax_t size){
    if (this->children.contains(name))
        return std::shared_ptr<File>(nullptr);
    auto file=File::newFile(name,size);
    this->children.insert({name,file});
    return file;

}

std::shared_ptr<Base> Directory::get(const std::string &name) {
    if (name == "..")
        return this->parent.lock();
    if (name == ".")
        return this->self.lock();
    if (children.contains(name))
        return children.at(name);
    else
        return std::shared_ptr<Base>(nullptr);


}
bool  Directory::remove(const std::string& name){
    if (name == ".." || name == ".")
        return false;
    if (!this->children.contains(name))
        return false;

    this->children.erase(name);
    return true;

}

std::shared_ptr<Directory> Directory::getDir(const std::string &name) {
    return dynamic_pointer_cast<Directory>(get(name));
}

std::shared_ptr<Directory> Directory::getRoot() {
    if (root == nullptr) {
        root = makeDir("/", std::weak_ptr<Directory>());

    }
    return root;
}


void Directory::ls(int indent) const {
    for (int i = 0; i < indent; i++) {
        std::cout << " ";
    }

    std::cout <<"[+]"<< this->name << std::endl;

    for (auto it = children.begin(); it != children.end(); ++it) {
        it->second->ls(indent + 4);
    }
    return;
}

int Directory::mType() const {
    return 0; // 0 = directory, 1 = file
}