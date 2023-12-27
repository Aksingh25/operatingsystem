#include <iostream>
#include <thread>
#include <atomic>

const int THREADS = 2;

std::atomic<int> turn(0);
std::atomic<int> flag[THREADS] = {0};

void process(int id) {
    for (int i = 0; i < 5; ++i) {
        flag[id] = 1;
        turn = 1 - id;

        while (flag[1 - id] == 1 && turn == 1 - id) {
            
        }

        
        std::cout << "Process " << id << " is in the critical section" << std::endl;

        flag[id] = 0;

        
        std::cout << "Process " << id << " is in the remainder section" << std::endl;
    }
}

int main() {
    std::thread threads[THREADS];

    for (int i = 0; i < THREADS; ++i) {
        threads[i] = std::thread(process, i);
    }

    for (int i = 0; i < THREADS; ++i) {
        threads[i].join();
    }

    return 0;
}

