//
// Created by xyz on 05/11/17.
//

#ifndef THREAD_POOL_THREAD_POOL_H
#define THREAD_POOL_THREAD_POOL_H

#include <thread>
#include <functional> //std::function
#include <vector>
#include <memory>     //shred_ptr
#include <utility>     //shred_ptr

#include "wpqueue.hpp"

namespace ilrd {

class ThreadPool {
public:
    explicit ThreadPool(size_t n_threads); // thread exceptions??
    ~ThreadPool(); // join exceptions???
    ThreadPool& operator=(const ThreadPool& other) = delete;
    ThreadPool(const ThreadPool& other) = delete;

    enum Priority{ LOW, MED, HIGH };

    template<typename Funcs,typename... Args>
    void add_task(Priority p, Funcs func, Args... params); //bad_alloc / pqueue exceptions

    // returns num of threads that fall to finish normally
    size_t stop(size_t secs); // join exceptions???,

    inline size_t get_nthreads() const noexcept;
    void set_nthread(std::size_t nthreads); //thread exceptions??

private:

    struct smaller {
        bool operator()(std::pair<Priority, std::function<void(void)>> lhs,
                        std::pair<Priority, std::function<void(void)>> rhs)
        {
            return lhs.first < rhs.first;
        }
    };

    void thread_function();
    //hint lambda
    WaitablePqueue<std::pair<Priority, std::function<void(void)>>, smaller > m_pqueue;
    std::vector<std::shared_ptr<std::thread>> m_pool;
    volatile bool keep_running;
};


template<class Funcs,class... Args>
void ThreadPool::add_task(Priority p, Funcs func, Args... params)
{
    m_pqueue.push(std::pair<Priority, std::function<void(void)>>
                      (p, [&func, params...](){ func(&params...); }));
}

inline size_t ThreadPool::get_nthreads() const noexcept
{
	return m_pool.size();
}

} /* namespace ilrd */
#endif //THREAD_POOL_THREAD_POOL_H
