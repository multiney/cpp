#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready)
        cv.wait(lock);
    std::cout << "thread" << id << "\n";
}

void go() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

void test_print_id() {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(print_id, i);
    std::cout << "10 threads ready to race...\n";
    go();
    for (auto &th : threads)
        th.join();
}

int main (int argc, char *argv[])
{
    test_print_id();
    return 0;
}
