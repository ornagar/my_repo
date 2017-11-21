//
// Created by xyz on 20/11/17.
//

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <vector>
#include <iostream>

#include "Point.hpp"
#include "Apple.hpp"

class Snake {
public:
    Snake(): m_body(), m_apple(), direction(RIGHT) {
        m_body.push_back(Point(320, 240));
        grow();
    }

    void move_up() {
        if (direction == DOWN) {
            return;
        }
        Point prev(m_body[0].getM_x(), m_body[0].getM_y() + m_dist);
        for (auto& i : m_body) {
            Point temp = i;
            i = prev;
            prev = temp;
        }
        direction = UP;
    }

    void move_down() {
        if (direction == UP) {
            return;
        }
        Point prev(m_body[0].getM_x(), m_body[0].getM_y() - m_dist);
        for (auto& i : m_body) {
            Point temp = i;
            i = prev;
            prev = temp;
        }
        direction = DOWN;
    }

    void move_right() {
        if (direction == LEFT) {
            return;
        }
        Point prev(m_body[0].getM_x() + m_dist, m_body[0].getM_y());
        for (auto& i : m_body) {
            Point temp = i;
            i = prev;
            prev = temp;
        }
        direction = RIGHT;
    }

    void move_left() {
        if (direction == RIGHT) {
            return;
        }
        Point prev(m_body[0].getM_x() - m_dist, m_body[0].getM_y());
        for (auto& i : m_body) {
            Point temp = i;
            i = prev;
            prev = temp;
        }
        direction = LEFT;
    }

    void advance() {
        switch(direction) {
            case UP:
                move_up();
                break;
            case LEFT:
                move_left();
                break;
            case DOWN:
                move_down();
                break;
            case RIGHT:
                move_right();
                break;
        }
    }

    void grow() {
        if (m_body[m_body.size() - 1].getM_x() ==
                                           m_body[m_body.size() - 2].getM_x()) {
            if (m_body[m_body.size() - 1].getM_y() <
                                           m_body[m_body.size() - 2].getM_y()) {
                m_body.push_back(Point(m_body.back().getM_x(),
                                                   m_body.back().getM_y() - m_dist));

            } else {
                m_body.push_back(Point(m_body.back().getM_x(),
                                                   m_body.back().getM_y() + m_dist));
            }
        } else {
            if (m_body[m_body.size() - 1].getM_x() <
                                           m_body[m_body.size() - 2].getM_x()) {
                m_body.push_back(Point(m_body.back().getM_x() - m_dist,
                                              m_body.back().getM_y()));
            } else {
                m_body.push_back(Point(m_body.back().getM_x() + m_dist,
                                                       m_body.back().getM_y()));
            }
        }

    }

    bool check_if_apple_eaten() {
        if (m_body.front() == m_apple.get_location()) {
            grow();
            m_apple.change_location();
            return true;
        }

        return false;
    }

    bool check_boundries() {

        return (m_body[0].getM_x() < 640 && m_body[0].getM_y() < 480 &&
                m_body[0].getM_x() > 0 && m_body[0].getM_y() > 0 && check_body());
    }

    bool check_body() {
        bool head_flag = false;
        for (auto& i : m_body) {
            if (head_flag) {
                if (m_body[0] == i) {
                    return false;
                }
            }
            head_flag = true;
        }
        return true;
    }

    void display() {
        std::cout << "snake head- " << m_body[0].getM_x() << ", " << m_body[0].getM_y() << std::endl;
        std::cout << "apple- " << m_apple.get_location().getM_x() << ", " <<
                                  m_apple.get_location().getM_y() << std::endl;

        for (auto& i : m_body) {
            i.display();
        }
        m_apple.display();
    }
private:
    std::vector<Point> m_body;
    Apple m_apple;
    enum Direction {LEFT, RIGHT, UP, DOWN};
    Direction direction;
    static const int m_dist = 10;
};


#endif //SNAKE_SNAKE_HPP
