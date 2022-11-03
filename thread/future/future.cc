#include <chrono>
#include <iostream>
#include <functional>
#include <thread>
#include <future>

void print_int(std::future<int> &fut) {
    int x = fut.get();
    std::cout << "value: " << x << "\n";
}

void test_print_int() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread t(print_int, std::ref(fut));
    prom.set_value(10);
    t.join();
}

// std::packaged_task
int countdown(int from, int to) {
    for (int i = from; i != to; --i) {
        std::cout << i << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Finished!\n";
    return from - to;
}

void test_countdown() {
    std::packaged_task<int(int, int)> task(countdown);
    std::future<int> ret = task.get_future();
    std::thread th(std::move(task), 10, 0);
    int val = ret.get();
    std::cout << "The countdown lasted for " << val << " seconds.\n";
    th.join();
}

int main (int argc, char *argv[])
{
    //test_print_int();
    test_countdown();
    return 0;
}
