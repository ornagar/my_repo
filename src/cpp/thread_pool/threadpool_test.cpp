#include <iostream>
#include "threadpool.hpp"
#include <unistd.h>
using namespace ilrd;

static void function() {
	std::cout << "hello first thread" << std::endl;
}

int main(int argc, char **argv)
{
    size_t n_threads = 10;
    if (argc > 1) {
		n_threads = atoi(argv[1]);
	}
    ThreadPool pool(n_threads);
    
    pool.add_task(ThreadPool::Priority::LOW, function);
    pool.set_nthread(1);
    pool.add_task(ThreadPool::Priority::LOW, function);
    pool.add_task(ThreadPool::Priority::LOW, function);
    pool.add_task(ThreadPool::Priority::LOW, function);
    pool.add_task(ThreadPool::Priority::LOW, function);
    pool.add_task(ThreadPool::Priority::LOW, function);
    sleep(2);
    pool.stop(1);
}
