//
// Created by xyz on 20/11/17.
//

#ifndef SNAKE_APPLE_HPP
#define SNAKE_APPLE_HPP

#include <iostream>
#include <ctime>

#include "Point.hpp"

class Apple {
public:
    Apple() : m_location(std::rand() % MAX_WIDTH + 1, std::rand() % MAX_HEIGHT + 1) {}
    void change_location() {
        Point next(std::rand() % MAX_WIDTH, std::rand() % MAX_HEIGHT);
        m_location = next;
    }

    void display() {
        m_location.display();
    }

    Point get_location() {
        return m_location;
    }

private:
    Point m_location;
    static const int MAX_WIDTH = 639;
    static const int MAX_HEIGHT = 479;
};


#endif //SNAKE_APPLE_HPP
