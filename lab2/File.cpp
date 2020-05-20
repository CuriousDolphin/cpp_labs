//
// Created by isnob on 16/05/2020.
//

#include "File.h"

File::File(std::string name,uintmax_t size): name(name),size(size){
    std::cout << " Create FILE " << name << " @ " << this << std::endl;
}

std::shared_ptr<File> File::newFile(std::string name,uintmax_t size){
    File *f=new File(name,size);
    return std::shared_ptr<File>(f);

}

void File::ls(int indent) const {
    for (int i = 0; i < indent; i++) {
        std::cout<<" ";
    }

    std::cout <<"[file]"<< this->name <<" "<<this->size<< std::endl;
    return;

}
int File::mType() const {
    return 1; // 0 = directory, 1 = file
}