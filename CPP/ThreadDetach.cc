#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
 
void pause_thread(int n) 
{
    std::this_thread::sleep_for (std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}
 
int main() 
{
    std::cout << "Spawning and detaching 3 threads...\n";

    // detach 不需要 调用 join ，其资源回收由 init 负责
    std::thread (pause_thread,1).detach();
    std::thread (pause_thread,2).detach();
    std::thread (pause_thread,3).detach();
    
    /*
    std::thread th1(pause_thread,1);
    std::thread th2(pause_thread,2);
    std::thread th3(pause_thread,3);
    // join 阻塞等待线程执行完成，回收线程资源, 不调用 join 线程可以正常执行，但资源无法回收会导致资源泄露，在 linux 上程序结束时会产生一个 core
    // th1.join();
    // th2.join();
    // th3.join();
    */
    std::cout << "Done spawning threads.\n";
  
    std::cout << "(the main thread will now pause for 5 seconds)\n";
    // give the detached threads time to finish (but not guaranteed!):
    pause_thread(5);
    return 0;
}
