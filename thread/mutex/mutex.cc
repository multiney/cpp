#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>

volatile int counter{0};
std::mutex mtx;
std::timed_mutex tmtx;

void increase() {
    for (int i = 0; i < 10000; ++i)
        if (mtx.try_lock()) {
            ++counter;
            mtx.unlock();
        }
}

void increase_independent() {
    for (int i = 0; i < 10000; ++i) {
        mtx.lock();
        ++counter;
        mtx.unlock();
    }
}

template <class F, class... Args>
void test_increase(F&& f, Args... args) {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(f, i);

    for (auto &th : threads) th.join();
    std::cout << counter << std::endl;
}

template<class F, class... Args>
void test(F&& f, Args&&... args) {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(f, args...);

    for (auto &th : threads) th.join();
    std::cout << counter << std::endl;

}

void fireworks() {
    while (!tmtx.try_lock_for(std::chrono::milliseconds(200))) {
        std::cout << "-";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << std::this_thread::get_id() << std::endl;
    tmtx.unlock();
}

/**
  std::lock_guard()
  */
void print_even(int x) {
    if (x & 0x1) throw (std::logic_error("not even"));
    else std::cout << x << "is even\n";
}

void print_thread_id(int id) {
    try {
        std::lock_guard<std::mutex> lck(mtx);
        print_even(id);
    }
    catch (std::logic_error&) {
        std::cout << "[exception caught]\n";
    }
}

int main (int argc, char *argv[])
{
    //test(increase_independent);
    //test(fireworks);
    test_increase(print_thread_id);
    return 0;
}
