#include <iostream>
#include <mutex>
#include <queue>
#include <filesystem>
#include <fstream>
#include <string>
#include <condition_variable>
using namespace std;
namespace fs = std::filesystem;

template <class T>
class Jobs {
    mutex m;
    condition_variable cv;
    queue<T> coda;
public:
    // inserisce un job in coda in attesa di essere processato, può
    // essere bloccante se la coda dei job è piena
    void put(T job){
        lock_guard<mutex> lg(m);
        coda.push(job);
        std::cout<<"PUT "<<job<<std::endl;
        cv.notify_one();
    };
    // legge un job dalla coda e lo rimuove
    // si blocca se non ci sono valori in coda
    T get() {
        unique_lock<mutex> lg(m);
        cv.wait(lg,[this](){return !coda.empty();});  // true sblocca la wait
        T data = coda.front();
        std::cout<<"GET "<<data<<std::endl;
        coda.pop();
        return data;
    };
};
void scan_directory(string dir){
    for (const auto& dirEntry : fs::recursive_directory_iterator(dir,fs::directory_options::skip_permission_denied)){
        //std::cout<< dirEntry.path()<<dirEntry.is_regular_file()<< std::endl;
        if(dirEntry.is_regular_file()){
            string filename=dirEntry.path().string();
            std::cout<<"FOUND FILE "<<filename<< dirEntry.file_size()<< std::endl;

            std::ifstream ifs(filename);

            if (!ifs.is_open()) {
                std::cout << "unable to open file "<< filename << std::endl;
                  return;
            }
            std::string line;
            int cont =0;
            while (ifs) {
                getline(ifs, line);
                cont++;
            }
            cout<<cont<<endl;
            ifs.close();


        }
    }
}

int main() {
    Jobs<string> jobs;
    string dir="../files";
    string regEx=R"(\d+\.\d+\.\d+\.\d+)"; // ip regex

    scan_directory(dir);
    return 0;
}

