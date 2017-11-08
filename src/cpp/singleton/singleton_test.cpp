#include "singleton.hpp"
#include <thread>
#include <iostream>
#include <fstream>
#include <mutex>

#define NUM_THREADS (15)


void single_thread();

void multi_thread();
void get_ptr(void);

int main()
{
    std::ofstream f;
    f.open("test.txt", std::ios::out);
    f.close();
	//single_thread();
	multi_thread();
}
void single_thread()
{
	//template <class T>
	int* ptr1 =  MySingleton<int>::GetInstance();
	//template <class T>
	int* ptr2 =  MySingleton<int>::GetInstance();
	double* ptr3 = MySingleton<double>::GetInstance();
	
	std::cout<<ptr1<<std::endl;
	std::cout<<ptr2<<std::endl;
	std::cout<<ptr3<<std::endl;
	
	/*
	// suppose to crach 
	MySingleton<double>::atexit_handler();
	ptr3 = MySingleton<double>::GetInstance();
	*/
}

void multi_thread()
{
	std::thread* threads[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++ ) {
   			threads[i] = new std::thread(&get_ptr);   
	}
	
	for(int i = 0; i < NUM_THREADS; i++ ) {
			threads[i]->join();
	}
}

void get_ptr() {
	int* ptr1;
	ptr1 = MySingleton<int>::GetInstance();
    static std::mutex m;
    std::lock_guard<std::mutex> lock(m);
    std::ofstream file;
    file.open("test.txt", std::ios::app);
	file<<ptr1<<std::endl;
    file.close();
  // pthread_exit(NULL);
  return ; 
}
