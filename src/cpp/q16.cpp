#include <iostream>

#include "q16.h"

int main(void)
{
	int arr[12];
	
	std::cout<<max(3, 5)<<" "<<max(3.7, 12.9) << " ";
	std::cout<<max(arr, arr+8)<<std::endl;
	std::cout<<max('a', 'b')<<std::endl;
	
	return 0;
}
