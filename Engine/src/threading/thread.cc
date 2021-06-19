#include "thread.h"
#include <thread>

int Thread::Create(auto (*fn)(), int id)
{
    /* Determine whether a specific thread id was assigned, or none. If none then the threading class keeps track of the thread id */
    (id = this->thread_id++) ? (id == -1) : id;
    std::thread _new_thread();
    return id;
}
