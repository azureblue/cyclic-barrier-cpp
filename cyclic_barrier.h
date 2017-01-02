#ifndef CYCLIC_BARRIER_H
#define CYCLIC_BARRIER_H

#include <cstdint>
#include <mutex>
#include <condition_variable>

class cyclic_barrier {

public:
    enum exit_status {
        normal = 0
    };
    
    cyclic_barrier(const int threads) :
    threads(threads) {
    }
    
    exit_status await();
    
private:
    const int threads;
    uint64_t cycle = 1;
    int waiting = 0;
    std::mutex mut;
    std::condition_variable cnd;
    
    void next_cycle();
};

#endif /* CYCLIC_BARRIER_H */

