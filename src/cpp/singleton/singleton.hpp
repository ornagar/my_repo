#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>

template <typename T>
class Singleton
{
public:
    static T& get_instance();

private:
    Singleton();   
   ~Singleton();
};

template <typename T>
T& Singleton<T>::get_instance()
{
    static T t;
    
    return t;
}

#endif //SINGLETON_HPP
