#include "cyclic_barrier.h"

void cyclic_barrier::next_cycle() {
    waiting = 0;
    cycle++;
    cnd.notify_all();
}

cyclic_barrier::exit_status cyclic_barrier::await() {
    std::unique_lock<std::mutex> lk(mut);
    const uint64_t current_cycle = cycle;
    waiting++;
    
    if (waiting == threads) {
        next_cycle();
        return normal;
    }
    
    while (cycle == current_cycle) {
        cnd.wait(lk);
    }
    
    return normal;
}
