#include <iostream>         //std::cout<<std::endl;

#include "list.hpp"         //List

using namespace ilrd;

static bool action_func(int* param, int arg);

int main()
{
    List<int> list;
    list.push_front(5);
    list.push_front(4);
    
    int x = 0;
    
    if (true == list.peek_front(&x))
    {
        std::cout<<"list peek = "<<x<<std::endl;
    }
    std::cout<<"list size = "<<list.size()<<std::endl;
    std::cout<<"list is_empty = "<<list.is_empty()<<std::endl;
    std::cout<<std::endl;
    
    List<int> list2 = list;
    if (true == list2.peek_front(&x))
    {
        std::cout<<"list2 peek = "<<x<<std::endl;
    }
    std::cout<<"list2 size = "<<list2.size()<<std::endl;
    std::cout<<"list2 is_empty = "<<list2.is_empty()<<std::endl;
    std::cout<<std::endl;
    
    list2.push_front(7);
    list2.push_front(4);
    list2.push_front(6);
    list2.push_front(1);
    
    std::cout<<"list2 size = "<<list2.size()<<std::endl;
    std::cout<<"list2 is_empty = "<<list2.is_empty()<<std::endl;
    std::cout<<std::endl;
    
    list2.for_each(action_func, 0);
    
    while (!list2.is_empty())
    {
        if (true == list2.peek_front(&x))
        {
            std::cout<<"list2 peek = "<<x<<std::endl;
        }
        list2.pop_front();
    }
    std::cout<<std::endl;
    
    list2.push_front(46);
    
    
    if (true == list.peek_front(&x))
    {
        std::cout<<"list peek = "<<x<<std::endl;
    }
    std::cout<<"list size = "<<list.size()<<std::endl;
    std::cout<<"list is_empty = "<<list.is_empty()<<std::endl;
    std::cout<<std::endl;
    
    List<int> list3;
    list3 = list2 = list;
    list3.pop_front();
    list2.push_front(13);
    if (true == list2.peek_front(&x))
    {
        std::cout<<"list2 peek = "<<x<<std::endl;
    }
    std::cout<<"list2 size = "<<list2.size()<<std::endl;
    std::cout<<"list2 is_empty = "<<list2.is_empty()<<std::endl;
    std::cout<<std::endl;
    
    if (true == list3.peek_front(&x))
    {
        std::cout<<"list3 peek = "<<x<<std::endl;
    }
    std::cout<<"list3 size = "<<list3.size()<<std::endl;
    std::cout<<"list3 is_empty = "<<list3.is_empty()<<std::endl;
    std::cout<<std::endl;
    
    return 0;
}

bool action_func(int* param, int arg)
{
    *param += 1;
    return true;
}