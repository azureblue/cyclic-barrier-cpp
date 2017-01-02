#include <vector>
#include <thread>
#include <cassert>
#include <algorithm>
#include <iostream>

#include "cyclic_barrier.h"

void test_mem_sync() {
    cyclic_barrier start_bar(4);
    cyclic_barrier end_bar(4);
    const int iterations = 2000;
    
    std::vector<int> data{0, 0, 0};
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 3; i++)
        threads.push_back(std::thread([&, i] {
            int iters = iterations;
            while (iters--) {
                start_bar.await();
                data[i]++;
                end_bar.await();
            }
        }));

    start_bar.await();
    
    for (int i = 1; i < iterations; i++) {        
        end_bar.await();
        assert(data[0] == i);
        assert(data[1] == i);
        assert(data[2] == i);
        start_bar.await();
    }
    
    end_bar.await();

    threads[0].join();
    threads[1].join();
    threads[2].join();

}

int main(int argc, char** argv) {
    test_mem_sync();
    return 0;
}

