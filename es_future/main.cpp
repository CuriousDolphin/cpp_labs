#include <iostream>
#include <future>
#include <thread>
#include <thread>
#include <sstream>
#include <mutex>
using namespace std;

string compute_result(){
    this_thread::sleep_for(chrono::milliseconds( 1000));
    return "Hello future";
}
int main() {
    shared_future<string> sf = async(launch::async,compute_result).share();
    for(int i=0;  i<10;i++){
        thread([&sf](){
            ostringstream oss;
            oss<<"thread "<<this_thread::get_id()<<" -> "<<sf.get()<<endl;
            cout<<oss.str();
        }).detach();
    }
    this_thread::sleep_for(chrono::seconds(5));
    return 0;
}
