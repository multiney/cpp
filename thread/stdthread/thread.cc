#include <chrono>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <thread>

void thread_task(int &n, const char* msg) {
    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "ID:" << std::this_thread::get_id() << " ";
    ++n;
    std::cout << msg << " " << n << std::endl;
}

int main (int argc, char *argv[])
{
    int n = 0;
    /*
    std::thread t(thread_task, std::ref(n), "t");
    std::cout << std::boolalpha << t.joinable() << std::endl;
    t.join();
    std::cout << std::boolalpha << t.joinable() << std::endl;
    */
    std::cout << std::thread::hardware_concurrency() << std::endl;
    std::thread (thread_task, std::ref(n), "detach1").detach();
    std::thread (thread_task, std::ref(n), "detach2").detach();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << n << std::endl;
    return EXIT_SUCCESS;
}
