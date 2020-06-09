#include <iostream>
#include <mutex>
#include <queue>
using namespace std;
template <class T>
class Buffer {
    mutex m;
    condition_variable cv;
    queue<T> coda;

public:
    void push(T element){
        lock_guard<mutex> lg(m);
        coda.push(element);
        std::cout<<"PUSH "<<element<<std::endl;
        cv.notify_one();
    }
    T pop(){
        unique_lock< mutex> lg(m);
        cv.wait(lg,[this](){
            return !coda.empty();
        });
        T data = coda.front();
        std::cout<<"POP "<<data<<std::endl;
        coda.pop();
        return data;
    }
};
int main() {
    Buffer<int> b;
    vector<thread> threads;
    int i;
    for(i=0;i<5;i++){
        if(i%2==0){
            threads.emplace_back([&b](){
                for (int i = 0; i < 10; i++){
                    b.push(i);
                }});
        }else{
            threads.emplace_back([&b](){
                for (int i = 0; i < 10; i++){
                    b.pop();
                }});
        }
    }
    cout << threads.size() << " threads created" << endl;
    for (auto &t:threads) {
        auto id = t.get_id();
        t.join();
        cout << "Thread " << id << " joined" << endl;
    }
    return 0;
}
