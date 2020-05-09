// Author : lzy
// Email  : liuzhengyong@trio.ai
// Date   : 2020-05-08 16:53
// Description: g++ -std=c++11 -pthread ThreadPool.cc 

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <chrono>
#include <condition_variable>

class CThreadPool {
    typedef std::unique_lock<std::mutex> MutexLock;
public:
    CThreadPool(int thread_num) : 
        _thread_num(thread_num) {
        ;
    }

    void Start() {
        for (int i = 0;i < _thread_num; ++i ) {
            std::thread th(&CThreadPool::Run, this);
            _threads.push_back(std::move(th));
        }
    }

    void Stop() {
        _stop = true;
    }

    void Run() {
        while ( true ) {
            std::function<void()> func;
            do {
                MutexLock lock(_mutex);
                if ( _stop && _functions.empty() ) { return ;}
                _condition.wait(lock, [this]()->bool{return !_functions.empty();});
                func = _functions.front();
                _functions.pop();
            } while(0);
            if ( func ) {
                func();
            }
        }
    }

    void Join() {
        for (auto iter = _threads.begin(); iter != _threads.end(); ++iter) {
            iter->join();
        }
    }

    void AddJob(const std::function<void()>& func) {
        MutexLock lock(_mutex);
        _functions.push(func);
        _condition.notify_one();
    }

private:
    int _thread_num;
    volatile bool _stop{false};
    std::mutex _mutex;
    std::condition_variable _condition;
    std::vector<std::thread> _threads;
    std::queue<std::function<void()> > _functions;
};

std::mutex g_mutex;

void Func(const std::string& name)  {
    do {
        std::unique_lock<std::mutex> lock(g_mutex);
        std::cout << name << "\tSTART" << std::endl << std::flush;
    } while(0);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    do {
        std::unique_lock<std::mutex> lock(g_mutex);
        std::cout << name << "\tOVER" << std::endl << std::flush;
    } while(0);
}

int main(int argc, char* argv[])
{
    CThreadPool pool(10);
    pool.Start();

    for (int i = 0;i < 20; ++i ) {
        std::string name(i+1, 'A'+i);
        pool.AddJob(std::bind(Func, name));
    }

    pool.Stop();

    pool.Join();

    return 0;
}
