//
// Created by xyz on 05/11/17.
//

#include "threadpool.hpp"
#include <unistd.h>

namespace ilrd {


static void kill_me()
{
    return;
}

void ThreadPool::thread_function()
{
    while (keep_running) {
        std::pair<Priority, std::function<void(void)>> p;
        m_pqueue.pop(&p);
        
        if (p.first == static_cast<Priority>(666)) {
            //TODO: push thread to destroy_queue.
            return;
        }
        p.second();
    }
}

ThreadPool::ThreadPool(size_t n_threads) : keep_running(true)
{
    for (size_t i = 0; i < n_threads; ++i) {
        m_pool.push_back(std::shared_ptr<std::thread>(new std::thread(&ThreadPool::thread_function, this)));
    }
}

ThreadPool::~ThreadPool()
{
    keep_running = false;
}

size_t ThreadPool::stop(size_t secs)
{
    for (size_t i = 0; i < m_pool.size(); ++i) {
        add_task(static_cast<Priority>(666), kill_me);
    }
    
    for (auto& t: m_pool) {
		t->join(); //TODO: add timer.
	}
	
    return 0; //TODO: should return num of successfull stops
}

void ThreadPool::set_nthread(std::size_t n_threads)
{
    if (n_threads < m_pool.size()) {//TODO: add a queue of threads to remove.
		for (size_t i = n_threads; i < m_pool.size(); ++i) {
            add_task(Priority(666), kill_me);
        }
    } else if (n_threads > m_pool.size()) {
        for (size_t i = m_pool.size(); i < n_threads; ++i) {
            m_pool.push_back(std::shared_ptr<std::thread>(new std::thread(&ThreadPool::thread_function, this)));
        }
    }
}

} // namespace ilrd
