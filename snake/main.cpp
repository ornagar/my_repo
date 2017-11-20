
// compile with this: **gdp11 main.cpp -lGL -lGLU -lglut**

#include <iostream>


#include "Snake.hpp"

Snake snake;
std::string title = "score:    ";
int num = 0;

char *Itoa(int src)
{
    char *dest = NULL;
    int counter = 0;
    int copy = src;
    int neg_flag = 0;

    do											/* count number's length	*/
    {
        copy /= 10;
        ++counter;
    }
    while (0 != copy);

    if (NULL == (dest = (char*)malloc(counter + 2)))	/* allocate size of src		*/
    {											/* + null + '-'				*/
        //DBG(perror("error in line __LINE__ while allocating memory");)
        return (NULL);
    }

    if (0 >= src)
    {
        *dest = '-';
        dest += counter + 1;					/* go to end of string		*/
        *dest = '\0';
        src *= -1;
        neg_flag = 1;
    }
    else
    {
        dest += counter;						/* go to end of string		*/
        *dest = '\0';
    }

    while (0 < counter)							/*add last int and move back*/
    {
        --dest;
        *dest = (src % 10) + '0';
        src /= 10;
        --counter;
    }

    if (neg_flag)
    {
        --dest;
    }

    return (dest);
}



void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(8000.0f);
    gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}


void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    snake.display();

    glFlush();
}

void onKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 72: case 'w':
            snake.move_up();
            break;
        case 75: case 'a':
            snake.move_left();
            break;
        case 80: case 's':
            snake.move_down();
            break;
        case 77: case 'd':
            snake.move_right();
            break;
    }

    display();
}


void timer(int t) {
    snake.advance();
    std::cout << "move" << std::endl;
    if (snake.check_if_apple_eaten()) {

        num += 1;
        title = "score: ";
        title += Itoa(num);

        glutSetWindowTitle(title.c_str());
    }
    if (!snake.check_boundries()) {
        glutDestroyWindow(1);
    }
    glutTimerFunc(80, timer, 0);
    glutPostRedisplay();
}

int main( int argc, char **argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("SNAKE");

    init();

    //glutFullScreen();
    glutKeyboardFunc(onKeyboard);
    glutDisplayFunc(display);
    timer(1);

    glutMainLoop();

    return 0;
}
