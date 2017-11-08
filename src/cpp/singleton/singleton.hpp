#ifndef _TS_SINGELTON_
#define _TS_SINGELTON_

#include <iostream>
#include <atomic>
#include <mutex>

template <class T>
class  MySingleton 
{
public:
	static T* GetInstance();
	static void atexit_handler(); //warning, after use of this function the get instance function will cause undefined behavior

private:
	static T* m_instance;
	
	MySingleton(); // private constructor	
	MySingleton(const MySingleton<T>& other)  = delete; // private constructor	
	MySingleton operator =(const MySingleton<T>& other)  = delete; // private constructor	
	
   ~MySingleton();
};
template <class T>
T* MySingleton<T>::m_instance = nullptr;

template <class T>
inline T* MySingleton<T>::GetInstance(){
	//static method that returns only instance of MySingletone
	static std::mutex mutex;
	
	std::atomic_thread_fence(std::memory_order_acquire);//barrier1
	static volatile bool created_flag = false;
	if (!created_flag) // if not yet instantiated
	{
		std::lock_guard<std::mutex> lock(mutex);	

		if(!created_flag) {
			m_instance = new T;
			created_flag = true;
			std::atexit(MySingleton::atexit_handler);
			std::atomic_thread_fence(std::memory_order_release);//barrier2
		}
	}
	if (nullptr == m_instance) {
		abort();
	}
	return m_instance;
}
template <class T>
void MySingleton<T>::atexit_handler()
{ 
	delete m_instance; 
	m_instance = nullptr;
}

#endif  // _TS_SINGELTON_
