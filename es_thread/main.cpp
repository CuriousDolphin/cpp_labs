#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

using namespace std;


/* v1 con mutex e results globali, cosi si garantisce che vengono eliminati per ultimi;
mutex m;
vector<string> results;
 */


bool contains(string filename, string pattern) {
    ifstream ifs(filename);
    string s;
    while (ifs) {
        getline(ifs, s);
        if (s.find(pattern) != string::npos) {
            ifs.close();
            return true;
        }
    }
    return false;
}
// class thread safe

class safe_vector{
    mutex m;
    vector<string> v;

public:
    void add(string value){
        lock_guard lg(m);
        v.push_back(value);
    }
    vector<string> values(){
        lock_guard lg(m);
        return  v;
    }
};
int main() {
    safe_vector results;
    vector<std::string> filenames{"../a.txt", "../b.txt", "../c.txt"};
    string pattern = "alfa";
    vector<thread> threads;
    for (auto f:filenames) {
        /* creo un thread e gli passo una funzione lambda che cattura f e pattern applica una lock guard */
        /* v1  nb il mutex e il vett dei ris sono globali, altrimenti avrei dovuto catturare anche loro ma per reference   */
        /* v2 con class thread safe */
        /* crea un thread nel vettore alternativamente thread t([](){})*/
        threads.emplace_back([f, pattern,&results]() {
            if (contains(f, pattern)) {
                //lock_guard<mutex> lg(m); // IL LOCK GUARD acquisisce il mutex e lo rilascia nel distruttore
                results.add(f);
            }

        });
    }
    cout << threads.size() << " threads created" << endl;
    /* ricevuti per reference, quindi l'originale e non la copia perche' i thread non si copiano */
    for (auto &t:threads) {
        auto id = t.get_id();
        t.join();
        cout << "Thread " << id << " joined" << endl;

    }

    for (auto f:results.values()) {
        cout << " FILE " << f << endl;
    }

    return 0;
}
