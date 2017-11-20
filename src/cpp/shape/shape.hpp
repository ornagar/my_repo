#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <GL/glut.h> //GLFloat

namespace ilrd {

namespace shape {

class Point {
public:
    explicit Point(double x=0, double y=0);

    Point& rotate(const Point& axis,double angle);

    double getx() const { return m_x; }
    double gety() const { return m_y; }

    void setx(double _x) { m_x = _x; }
    void sety(double _y) { m_y = _y; }
    
    void addx(double _x) { m_x += _x; }
    void addy(double _y) { m_y += _y; }

private:
    double m_x;
    double m_y;
};

class Shape {
public:
    virtual ~Shape() = 0;

    virtual void draw() const = 0;
    virtual void move(const Point& other) = 0;
    virtual void rotate(double angle) = 0;
    virtual void revolve(const Point& point, double angle) = 0;

    virtual Point get_center() = 0;
};

inline Shape::~Shape() {}

class Triangle : public Shape
{
public:
    explicit Triangle();

    void draw() const override;
    void move(const Point& other) override;
    void rotate(double angle) override;
    void revolve(const Point& point, double angle) override;

    Point get_center();
    void set_center();

private:
    Point m_a;
    Point m_b;
    Point m_c;
    Point m_center;
};

class Circle : public Shape
{
public:
    explicit Circle(double radius = 30, double center = 0);

    void draw() const override;
    void move(const Point& other) override;
    void rotate(double angle) override;
    void revolve(const Point& point, double angle) override;

    Point get_center() { return m_center; }

private:
    double m_radius;
    Point m_center;
};


class Rectangle : public Shape
{
public:
    inline explicit Rectangle();

    void draw() const override;
    void move(const Point& other) override;
    void rotate(double angle) override;
    void revolve(const Point& point, double angle) override;

    Point get_center();
    void set_center();
private:
    Point m_a;
    Point m_b;
    Point m_c;
    Point m_d;
    Point m_center;
};


class Group : public Shape
{
public:
    explicit Group();

    void add(Shape* shape);
    void draw() const override;
    void move(const Point& other) override;
    void rotate(double angle) override;
    void revolve(const Point& point, double angle) override;

    Point get_center();

private:
    Shape* shapes[15];
    size_t num_of_shapes;
};


inline Point::Point(double x, double y): m_x(x), m_y(y) {}
inline Triangle::Triangle(): m_a(300, 300), m_b(300, 380), m_c(380,300),
                                                              m_center(326, 326) {}
inline Circle::Circle(double radius, double center): m_radius(radius),
                                                           m_center(200, 200) {}
inline Rectangle::Rectangle(): m_a(50, 100), m_b(50, 150), m_c(200, 150),
                                                   m_d(200, 100), m_center(125, 125) {}
inline Group::Group(): num_of_shapes(0) {}

} //namespace shapes
} // namespace ilrd

#endif // SHAPE_HPP_
