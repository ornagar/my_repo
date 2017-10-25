#include "singleton.hpp"

#include <iostream>



int main()
{
	//template <class T>
	int* ptr1 =  MySingleton<int>::GetInstance();
	//template <class T>
	int* ptr2 =  MySingleton<int>::GetInstance();
	double* ptr3 = MySingleton<double>::GetInstance();
	
	std::cout<<ptr1<<std::endl;
	std::cout<<ptr2<<std::endl;
	
	MySingleton<double>::atexit_handler();
	
	ptr3 = MySingleton<double>::GetInstance();
	std::cout <<"atexit:"<< ptr3 << std::endl;
}
