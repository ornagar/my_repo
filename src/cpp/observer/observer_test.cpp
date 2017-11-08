#include <iostream>

#include "observer.hpp"

class Click {
public:
    size_t count_up() { ++m_counter; return m_counter; }
    size_t get() { return m_counter; }
private:
    size_t m_counter;
};

class Respond {
public:
    void update_counter(Click click) { m_counter = click.get(); std::cout << "got callback" << std::endl; }
    void update_death() { std::cout << "dispatcher is dead" << std::endl; }
private:
    size_t m_counter;
};
using namespace ilrd;
int main() {
    
    
    Dispatcher<Click> dispatcher;
    
    Click click;
    Respond respond;
    {
    CallBack<Click, Respond> my_callback(&respond, &Respond::update_counter, &Respond::update_death);
    CallBack<Click, Respond> my_callback2(&respond, &Respond::update_counter, &Respond::update_death);
    Dispatcher<Click> dispatcher2;
    
    dispatcher.subscribe(&my_callback);
    dispatcher2.subscribe(&my_callback2);
    click.count_up();
    dispatcher.notify(click);
    dispatcher2.notify(click);
    }
}
