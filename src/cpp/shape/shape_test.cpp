#include <cmath>
#include "shape.hpp"

using namespace ilrd;
using namespace shape;
Group group;
Triangle t;
Circle c;
Rectangle r;
const Point p(600, 125);

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}



void display(void) {

double x = group.get_center().getx();
    ++x;
    group.add(&t);
    group.add(&c);
    group.add(&r);
    
x = group.get_center().getx();
    ++x;
    glClear(GL_COLOR_BUFFER_BIT);

    group.draw();

    glFlush();
}

void onKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'W': case 'w':
            group.move(Point(0, 10));
            break;
        case 'A': case 'a':
            group.move(Point(-10, 0));
            break;
        case 'S': case 's':
            group.move(Point(0, -10));
            break;
        case 'D': case 'd':
            group.move(Point(10, 0));
            break;
        case 'R': case 'r':
            group.rotate(10);
            break;
        case 'Q': case 'q':
            group.revolve(p, -10);
            break;
    }

    display();
}

int main( int argc, char **argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("SHAPES");

    init();

    glutKeyboardFunc(onKeyboard);
    glutDisplayFunc(display);

    glutMainLoop();
    
    return 0;
}
