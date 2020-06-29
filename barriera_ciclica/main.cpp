#include <iostream>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <string>
using namespace std;
mutex m2;
void my_print(string s){
    lock_guard<mutex> lg(m2);
    cout<<"("<<this_thread::get_id()<<") "<<s<<endl;

};
class BarrieraCiclica {
private:
    int maxn;
    int i;
    std::mutex m;
    std::condition_variable cv;
public:
    BarrieraCiclica(int n): maxn(n) {
        i = 0;
    };
    ~BarrieraCiclica(){
        cout<<"Barriera ciclica destroyed"<<endl;
    }
    void attendi() {

        unique_lock<std::mutex> ul(m);
        i++;

        if(i < maxn ){
            my_print(" WAITING  "+to_string(i));
            cv.wait(ul, [this](){ return i==0; });


            my_print(" WAKE UP "+to_string(i));

        }else{
            my_print("OPEN DOOR ");
            i=0;
            cv.notify_all();
        }

    }
};


template <class T>
        class Exchanger {
            T value;
            bool cond;
            mutex m;
            condition_variable  cv;
        public:
            Exchanger(){cond=false;};


            T exchange(T t){
                unique_lock<mutex> ul(m);
                if(!cond){
                    value=t;
                    cond=true;
                    cv.wait(ul);
                    return value;
                }else{
                    T tmp = value;
                    value=t;
                    cond=false;
                    cv.notify_one();
                    return tmp;
                }

            }


};


int main() {
    vector<thread> threads;
    /*BarrieraCiclica bc(5);

    int i;
    for(i=0;i<15;i++){
        this_thread::sleep_for(chrono::milliseconds(1000));
        threads.emplace_back([&bc](){
         //   my_print("CREATED");
            bc.attendi();
        });
    }*/

    Exchanger<int> ex;
    int i;
    for(i=0;i<15;i++)
        threads.emplace_back([&ex,i](){
            //   my_print("CREATED");
            int ris=ex.exchange(i);
            my_print("EXCHANGED "+to_string(i)+" with"+to_string(ris));
        });


    for (auto &t:threads) {
        auto id = t.get_id();
        t.join();
        cout << "(" << id << ") joined" << endl;
    }
    return 0;
}
