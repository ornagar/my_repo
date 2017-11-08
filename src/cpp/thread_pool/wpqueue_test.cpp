#include <iostream>

#include "wpqueue.hpp"

int main()
{
    int a[20] = {0};
    WaitablePqueue<int> queue;
    queue.push(a[0]);
    int b = 1;
    queue.pop(&b);
    int c = 1;
    std::cout << b << std::endl;
    queue.try_pop(&c, 2);
    std::cout << c << std::endl;
}
