#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include "Directory.h"
#include <filesystem>
namespace fs = std::filesystem;

int main() {


    std::shared_ptr<Directory> root = Directory::getRoot();
    auto alfa = root->addDirectory("alfa");
    alfa->addDirectory("beta")->addFile("file1", 150);
    alfa->getDir("beta")->addFile("file2", 200);
    alfa->getDir("..")->ls(0);
    alfa->getDir("beta")->remove( "file2" );
    root->ls(0);


    for (const auto& dirEntry : fs::recursive_directory_iterator("../test",fs::directory_options::skip_permission_denied)){
        std::cout<< dirEntry.path(). << std::endl;
    }

}