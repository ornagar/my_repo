#include <cmath>
#include "shape.hpp"

namespace ilrd {

namespace shape {

const double PI = 3.14;

Point& Point::rotate(const Point& axis,double angle)
{
  double s = sin((PI/180)*angle);
  double c = cos((PI/180)*angle);

  // translate point back to origin:
  m_x -= axis.m_x;
  m_y -= axis.m_y;

  // rotate point
  double xnew = m_x * c - m_y * s;
  double ynew = m_x * s + m_y * c;

  // translate point back:
  m_x = xnew + axis.m_x;
  m_y = ynew + axis.m_y;

  return *this;
}

void Triangle::draw() const
{
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(m_a.getx(), m_a.gety());
    glVertex2f(m_b.getx(), m_b.gety());
    glVertex2f(m_c.getx(), m_c.gety());
    glEnd();
}

void Triangle::move(const Point& other)
{
    double x = other.getx();
    double y = other.gety();

    m_a.addx(x);
    m_a.addy(y);

    m_b.addx(x);
    m_b.addy(y);

    m_c.addx(x);
    m_c.addy(y);

    set_center();
}

void Triangle::rotate(double angle)
{
    m_a.rotate(m_center ,angle);
    m_b.rotate(m_center ,angle);
    m_c.rotate(m_center ,angle);
}

void Triangle::revolve(const Point& point, double angle)
{
    m_a.rotate(point ,angle);
    m_b.rotate(point ,angle);
    m_c.rotate(point ,angle);

    set_center();
}

Point Triangle::get_center()
{
    return m_center;
}

void Triangle::set_center()
{
    m_center.setx((m_a.getx() + m_b.getx() + m_c.getx()) / 3);
    m_center.sety((m_a.gety() + m_b.gety() + m_c.gety()) / 3);
}

void Circle::draw() const
{
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    GLfloat step = 1/m_radius;
    GLfloat x, y;

    for(GLfloat theta = 0; theta <= 360; theta += step) {
        x = m_center.getx() + (m_radius * cos(theta));
        y = m_center.gety() + (m_radius * sin(theta));
        glVertex2i(x, y);
    }
    glEnd();
}

void Circle::move(const Point& other)
{
    double x = other.getx();
    double y = other.gety();

    m_center.addx(x);
    m_center.addy(y);
}

void Circle::rotate(double angle)
{
    return;
}

void Circle::revolve(const Point& point, double angle)
{
    m_center.rotate(point ,angle);
}

void Rectangle::draw() const
{
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(m_a.getx(), m_a.gety());
    glVertex2f(m_b.getx(), m_b.gety());
    glVertex2f(m_c.getx(), m_c.gety());
    glVertex2f(m_d.getx(), m_d.gety());
    glEnd();
}

void Rectangle::move(const Point& other)
{
    double x = other.getx();
    double y = other.gety();

    m_a.addx(x);
    m_a.addy(y);

    m_b.addx(x);
    m_b.addy(y);

    m_c.addx(x);
    m_c.addy(y);

    m_d.addx(x);
    m_d.addy(y);

    set_center();
}

void Rectangle::rotate(double angle)
{
    m_a.rotate(m_center ,angle);
    m_b.rotate(m_center ,angle);
    m_c.rotate(m_center ,angle);
    m_d.rotate(m_center ,angle);
}

void Rectangle::revolve(const Point& point, double angle)
{
    m_a.rotate(point ,angle);
    m_b.rotate(point ,angle);
    m_c.rotate(point ,angle);
    m_d.rotate(point ,angle);

    set_center();
}

Point Rectangle::get_center()
{
    return m_center;
}

void Rectangle::set_center()
{
    m_center.setx((m_a.getx() + m_c.getx()) / 2);
    m_center.sety((m_b.gety() + m_d.gety()) / 2);
}

void Group::add(Shape* shape)
{
    if (15 > num_of_shapes) {
        shapes[num_of_shapes] = shape;
        ++num_of_shapes;
    }
}
void Group::draw() const
{
    for (size_t i = 0; i < num_of_shapes; ++i) {
        shapes[i]->draw();
    }

}

void Group::move(const Point& other)
{
    for (size_t i = 0; i < num_of_shapes; ++i) {
        shapes[i]->move(other);
    }
}
void Group::rotate(double angle)
{
    Point center = get_center();
    for (size_t i = 0; i < num_of_shapes; ++i) {
        shapes[i]->revolve(center, angle);
    }
}

void Group::revolve(const Point& point, double angle)
{
    for (size_t i = 0; i < num_of_shapes; ++i) {
        shapes[i]->revolve(point, angle);
    }
}

Point Group::get_center()
{
    double x = 0;
    double y = 0;

    for (size_t i = 0; i < num_of_shapes; ++i) {
        x += shapes[i]->get_center().getx();
        y += shapes[i]->get_center().gety();
    }

    x /= num_of_shapes;
    y /= num_of_shapes;

    return Point(x, y);
}

}
}
