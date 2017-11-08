/*
 * WaitablePqueue.hpp
 *
 *  Created on: Nov 1, 2017
 *      Author: super29
 */

#ifndef WPQUEUE_HPP_
#define WPQUEUE_HPP_

#include <queue>
#include <condition_variable>
#include <mutex>
#include <chrono>

namespace ilrd {

// Task should be copyable
template<class Task, class Compare = std::less<Task>>
class WaitablePqueue {
public:
	WaitablePqueue() = default;
	~WaitablePqueue()= default;
	WaitablePqueue& operator=(const WaitablePqueue& other)= delete;
	WaitablePqueue(const WaitablePqueue& other)= delete;

	void pop(Task* top);
	bool try_pop(Task* top, std::size_t sec);
	std::size_t size()const;
	bool empty()const;
	void push(const Task& task);

private:
	  std::priority_queue<Task, std::vector<Task>, Compare> m_pqueue;
	  std::condition_variable m_cv;
	  mutable std::mutex m_mutex;
};

template<class Task, class Compare>
void WaitablePqueue<Task, Compare>::push(const Task& task)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_pqueue.push(task);
    m_cv.notify_one();
} 

template<class Task, class Compare>
bool WaitablePqueue<Task, Compare>::empty() const
{
    return m_pqueue.empty();
}

template<class Task, class Compare>
size_t WaitablePqueue<Task, Compare>::size() const
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_pqueue.size();
}

template<class Task, class Compare>
void WaitablePqueue<Task, Compare>::pop(Task* top) 
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_cv.wait(lock, [this]{return !empty();});
    
    *top = m_pqueue.top();
    m_pqueue.pop();
}

template<class Task, class Compare>
bool WaitablePqueue<Task, Compare>::try_pop(Task* top, std::size_t sec)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_cv.wait_for(lock, std::chrono::seconds(sec), [this]{return !empty();});

    if (empty()) {
        return false;
    }
    
    *top = m_pqueue.top();
    m_pqueue.pop();
    return true;
}

} /* namespace ilrd */

using namespace ilrd;

#endif /* WPQUEUE_HPP_ */


