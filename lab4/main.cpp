#include <iostream>
#include <mutex>
#include <queue>
#include <filesystem>
#include <fstream>
#include <string>
#include <condition_variable>
#include <future>
#include <optional>
#include <utility>
#include <regex>
#include <sstream>
#include "DurationLogger.h"

int N_CONSUMER = 8;
int N_PRODUCER = 2;
int MAX_QUEUE_LEN = 20;
using namespace std;
namespace fs = std::filesystem;

class Line {
    string file_name;
    string data;
    int row;
public:
    Line(string file_name, string data, int row) : file_name(std::move(file_name)), data(std::move(data)), row(row) {}
    string getData() { return data; }
    int getRow() { return row; }
    string getFileName() { return file_name; }
};

template<class T>
class Jobs {
    mutex m;
    condition_variable cv;
    condition_variable cv2;
    queue<T> coda;
    std::atomic<bool> completed = false;
public:
    // inserisce un job in coda in attesa di essere processato, può
    // essere bloccante se la coda dei job è piena
    void put(T job) {
        unique_lock<mutex> lg(m);
        cv2.wait(lg, [this]() {
            return coda.size() < MAX_QUEUE_LEN;
        });
        coda.push(job);
        cv.notify_one(); // notifica i consumers
    };

    // legge un job dalla coda e lo rimuove
    // si blocca se non ci sono valori in coda
    optional<T> get() {

        unique_lock<mutex> lg(m);
        cv.wait(lg, [this]() { return !coda.empty() || completed.load(); });  // true sblocca la wait
        if (completed.load() && coda.empty()) {
            return nullopt;
        }
        T data = coda.front();
        // std::cout << this_thread::get_id() << " GET " << data << std::endl;
        coda.pop();
        cv2.notify_one(); // notifica il producer
        return data;

    };

    bool is_completed() {
        return completed.load();
    }

    bool is_empty() {
        return coda.empty();
    }

    // per notificare la chiusura
    void complete() {
        completed.store(true);
        cv.notify_all();
        // std::cout << this_thread::get_id() << "COMPLETED " << std::endl;
    }
};


template<class T>
void producer_v1(string const &dir, T &jobs) {
    for (const auto &dirEntry : fs::recursive_directory_iterator(dir, fs::directory_options::skip_permission_denied)) {
        //std::cout<< dirEntry.path()<<dirEntry.is_regular_file()<< std::endl;
        if (dirEntry.is_regular_file()) {
            string path = dirEntry.path().string();
            string filename = dirEntry.path().filename().string();
            //cout<<this_thread::get_id()<<" FOUND FILE "<<filename<< dirEntry.file_size()<< std::endl;

            ifstream ifs(path);

            if (!ifs.is_open()) {
                cout << "unable to open file " << filename << std::endl;
                return;
            }
            std::string line;
            int cont = 0;
            while (getline(ifs, line)) {
                jobs.put(Line(filename, line, cont));
                cont++;
            }
            //         cout<<cont<<"lines"<<endl;
            ifs.close();

        }
    }

    jobs.complete();
}

template<class T1, class T2>
void producer_v2(T1 &fileJobs, T2 &jobs) {
    ostringstream oss; //thread safe print
    oss << "  PRODUCER  - (" << this_thread::get_id() << ")" << "  " << endl;
    cout << oss.str();
    while (true) {
        optional<string> path = fileJobs.get();
        if (!path.has_value()) {
            break;
        }
        ostringstream oss; //thread safe print
        oss << "     (" << this_thread::get_id() << ")" << " READ FILE: " << path.value() << endl;
        cout << oss.str();
        //string path = dirEntry.path().string();
        //string filename = dirEntry.path().filename().string();
        //cout<<this_thread::get_id()<<" FOUND FILE "<<filename<< dirEntry.file_size()<< std::endl;
        ifstream ifs(path.value());

        if (!ifs.is_open()) {
            cout << "unable to open file " << path.value() << std::endl;
            return;
        }
        std::string line;
        int cont = 0;
        while (getline(ifs, line)) {
            jobs.put(Line(path.value(), line, cont));
            cont++;
        }
        ifs.close();
    }

    oss << "  (" << this_thread::get_id() << ")" << "PRODUCER FINISH" << endl;
    cout << oss.str();


}


template<class T>
void consumer(const regex &regEx, T &jobs) {
    ostringstream oss; //thread safe print

    oss << "  CONSUMER  - (" << this_thread::get_id() << ")" << "  " << endl;
    cout << oss.str();
    while (true) {
        optional<Line> job = jobs.get();
        if (!job.has_value()) {
            break;
        }
        string line = job.value().getData();
        std::smatch match;
        while (regex_search(line, match, regEx)) { // loop su tutti i risultati della riga
            //std::cout << rit->str() << std::endl;
            ostringstream oss; //thread safe print
            oss << job.value().getFileName() << " - " << job.value().getRow() << " - " << match[0] << " ("
                << this_thread::get_id() << ")" << endl;
            cout << oss.str();
            line = match.suffix().str();
        }
    }
}

template<class T>
void scan_directory(string const &dir, T &jobs) {
    for (const auto &dirEntry : fs::recursive_directory_iterator(dir, fs::directory_options::skip_permission_denied)) {
        //std::cout<< dirEntry.path()<<dirEntry.is_regular_file()<< std::endl;
        if (dirEntry.is_regular_file()) {
            cout << "FOUND FILE " << dirEntry.path().string() << endl;
            jobs.put(dirEntry.path().string());
        }
    }
    jobs.complete();
}

int main() {
    DurationLogger dl("multi thread");
    cout << "MAIN THREAD " << this_thread::get_id() << endl;
    Jobs<Line> jobs;
    string dir = "../files";
    string regEx = R"(\d+\.\d+\.\d+\.\d+)"; // ip regex
    regex my_regex(regEx); // matches words beginning by "sub"
    /*thread producer([dir, &jobs]() {
        producer_v1<Jobs<Line>>(dir, jobs);
    });
    vector<thread> consumers;
    for (int i = 0; i < N_THREAD; i++)
        consumers.emplace_back([&my_regex, &jobs]() {
            consumer<Jobs<Line>>(my_regex,jobs);
        });



    for (auto &t:consumers) {
        auto id = t.get_id();

        t.join();

        cout << "consumer " << id << " joined" << endl;
    };
    auto prod_id = producer.get_id();
    cout << "producer " << prod_id << " joined" << endl;
    producer.join();*/

    Jobs<string> fileJobs;
    vector<thread> consumers;
    vector<thread> producers;

    for (int i = 0; i < N_PRODUCER; i++)
        producers.emplace_back([&fileJobs, &jobs]() {
            producer_v2<Jobs<string>, Jobs<Line> >(fileJobs, jobs);
        });
    for (int i = 0; i < N_CONSUMER; i++)
        consumers.emplace_back([&my_regex, &jobs]() {
            consumer<Jobs<Line>>(my_regex, jobs);
        });


    scan_directory(dir, fileJobs);
    int cont = N_PRODUCER;

    for (auto &t:producers) {
        auto id = t.get_id();
        t.join();
        cont--;
        cout << "producer  " << id << " joined > remaining"<<cont << endl;
        if (cont == 0) {
            cout << "TUTTI I PRODUCER SONO TEMINATI completo il job" << endl;
            jobs.complete();
        }


    };
    for (auto &t:consumers) {
        auto id = t.get_id();
        t.join();
        cout << "consumer " << id << " joined" << endl;
    };

    return 0;
}

