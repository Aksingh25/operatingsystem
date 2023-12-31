#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void threadFunction1() {
    std::lock_guard<std::mutex> lock1(mutex1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  
    std::lock_guard<std::mutex> lock2(mutex2);

    std::cout << "Thread 1: Executing critical section." << std::endl;
}

void threadFunction2() {
    std::lock_guard<std::mutex> lock2(mutex2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  
    std::lock_guard<std::mutex> lock1(mutex1);

    std::cout << "Thread 2: Executing critical section." << std::endl;
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
