//
// Created by xyz on 20/11/17.
//

#ifndef SNAKE_POINT_HPP
#define SNAKE_POINT_HPP

#include <GL/glut.h> //GLFloat
#include <cmath>

class Point {
public:
    Point(int x = 0, int y = 0) {
        m_x = x;
        m_y = y;
    }

    int getM_x() const {
        return m_x;
    }

    void setM_x(int x) {
        m_x = x;
    }

    int getM_y() const {
        return m_y;
    }

    void setM_y(int y) {
        m_y = y;
    }

    void display() {
        double m_radius = 5;
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        GLfloat step = 1/m_radius;
        GLfloat x, y;

        for(GLfloat theta = 0; theta <= 360; theta += step) {
            x = m_x + (m_radius * cos(theta));
            y = m_y + (m_radius * sin(theta));
            glVertex2i(x, y);
        }
        glEnd();
    }

private:
    int m_x;
    int m_y;
};

#endif //SNAKE_POINT_HPP
